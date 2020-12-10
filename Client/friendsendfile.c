#include "client.h"

void friendsendfile(const char *friend_name)
{
    char strArr[4][100];
    char str[2][15] = {"确认发送", "下次再发"};
    char filename[100];
    int key, n;

    bSubOpen = 0;                  //功能主界面标志位

    clear();
    Wind(stdscr, 8, 32, 20, 101);

    strcpy(strArr[0], "********************************************************************");
    strcpy(strArr[1], "*                           send file to                           *");
    sprintf(strArr[2], "*                                %s                               *", friend_name);
    strcpy(strArr[3], "********************************************************************");

    mvaddstr(9, 5+LeftCol, strArr[0]);
    mvaddstr(10, 5+LeftCol, strArr[1]);
    mvaddstr(11, 5+LeftCol, strArr[2]);
    mvaddstr(12, 5+LeftCol, strArr[3]);
    mvaddstr(14, 23+LeftCol, "输入要发送的文件所在路径和文件名");

    echo();
    curs_set(1);   
    keypad(stdscr, TRUE);

    move(16, 15+LeftCol);
    scanw("%s", filename);

    noecho();
    curs_set(0);

    attron(A_REVERSE);
    mvaddstr(18, 30+LeftCol, str[0]);
    attroff(A_REVERSE);
    mvaddstr(18, 42+LeftCol, str[1]);

    n = 0;
    while (1) {

        key = getch();

        if ( key == KEY_LEFT || key == KEY_RIGHT ) {

            mvaddstr(18, 30+LeftCol+12*n, str[n]);

            if ( key == KEY_LEFT ) {
                n = n == 0 ? 1 : 0;
            }

            else {
                n = n == 1 ? 0 : 1;
            }

            attron(A_REVERSE);
            mvaddstr(18, 30+LeftCol+12*n, str[n]);
            attroff(A_REVERSE);

        }

        else if ( key == ENTER ) {

            if ( n == 0 )
                friend_sendfile(filename, friend_name);
                
            break;

        }

    }

}


void friend_sendfile(const char *filename, const char *friend_name)
{
    char buf[650], code_out[900], code_end[5];      //~4/3 x input
    char *out;
    int fd, size;

    base64_encodestate state_in;

    if( (fd = open(filename ,O_RDONLY)) == -1 ) {

        Wind(stdscr, 22, 32, 28, 101);

        mvprintw(24, 28+LeftCol, "文件不存在或无读取权限");
        mvprintw(26, 30+LeftCol, "按任意键返回主界面");
        getch();

        return;
    }

    while ( 1 ) {
    
        memset(buf ,0,sizeof(buf));
        size = read(fd, buf, sizeof(buf)-2);    //减2为了凑24的倍数，因为base64编码每次读三个字节
    
        base64_init_encodestate(&state_in);
        memset(code_out ,0,sizeof(code_out));
        base64_encode_block(buf, size, code_out, &state_in);

        if ( state_in.step != step_A ) {        //step_A代表刚好转成base64时不需要补位,将文件最后的字节加到末尾
            
            memset(code_end ,0,sizeof(code_end));
            base64_encode_blockend(code_end, &state_in);
            strcat(code_out, code_end);
        
        }

        cJSON *root = cJSON_CreateObject();
        cJSON *item = cJSON_CreateNumber(7);
        cJSON_AddItemToObject(root, "type", item);
        item = cJSON_CreateString(friend_name);
        cJSON_AddItemToObject(root, "friend_name", item);
        item = cJSON_CreateString(basename((char*)filename));
        cJSON_AddItemToObject(root, "filename", item);
        item = cJSON_CreateNumber(size);
        cJSON_AddItemToObject(root, "size", item);
        item = cJSON_CreateString(code_out);
        cJSON_AddItemToObject(root, "con", item);
        out = cJSON_Print(root);
        cJSON_Delete(root);
       
        if ( send(conn_fd, out, MSG_LEN, 0) < 0 ) {
            myerr("send", __LINE__);
        }

        if ( size < (int)sizeof(buf)-2 )
            break;

        free(out);

    }

    close(fd);

}

void friend_recvfile(const char *message)
{
    char code_out[650] ,buf[900];
    char filename[100] = "Recvfile/";
    int size;

    base64_decodestate state_in;
    
    memset(buf, 0, sizeof(buf));
    
    cJSON *root = cJSON_Parse(message);
    cJSON *item = cJSON_GetObjectItem(root, "filename");
    strcat(filename, item->valuestring);
    
    int fd = open(filename, O_WRONLY|O_CREAT|O_APPEND, 0777);
    
    if ( fd == -1 ) {
        myerr("open", __LINE__);
    }

    item = cJSON_GetObjectItem(root, "con");
    strcat(buf, item->valuestring);
    item = cJSON_GetObjectItem(root, "size");
    size = item->valueint;
    base64_init_decodestate(&state_in);
    base64_decode_block(buf, strlen(buf), code_out, &state_in);
    
    if( write(fd, code_out, size) != size ) {
        myerr("write", __LINE__);
    }

    if( size < 650-2 ) {
        sprintf(file_message, "收到一个文件,已保存至./Recvfile/%s", basename(filename));
    }

    close(fd);

}
