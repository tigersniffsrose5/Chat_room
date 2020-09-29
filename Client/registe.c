#include "client.h"


void registe()
{
    WINDOW *aboutWin;                    //声明一个新的窗口
    int sex, key, n = 0, ret, recv_len, flag, id;
    char name[30];
    char password[30];
    char message[MSG_LEN];
    char Sex[2][4] = {"男","女"};
    cJSON *root;
    cJSON *item;


    clear();
    touchwin(stdscr);                    //激活stdrc窗口
    wrefresh(stdscr);                    //将窗口显示出来
    aboutWin = newwin(16, 40, 8, 48);
    Wind(aboutWin, 0, 0, 15, 39);
    touchwin(aboutWin);                
    wrefresh(aboutWin);

    echo();
    curs_set(1);
    keypad(stdscr, FALSE);

    mvprintw(10, 58, RegisteMenu[0]);
    move(11,65);
    scanw("%s", name);
    mvprintw(14, 58, RegisteMenu[1]);
    move(15,65);
    scanw("%s", password);
    
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);

    mvprintw(18, 58, "*****请选择性别*****");
    attron(A_REVERSE);
    mvaddstr(19, 64, Sex[0]);
    attroff(A_REVERSE);
    mvaddstr(19, 67, "||");
    mvaddstr(19, 70, Sex[1]);

    while ( 1 ) {
        
        mvprintw(19, 87, "|");
        key = getch();

        if ( key == KEY_LEFT || key == KEY_RIGHT ) {
            
            mvaddstr(19, 64+n*6, Sex[n]);
            
            if ( key == KEY_LEFT ) {
                n = n == 0 ? 1 : 0;
            }

            else {
                n = n == 1 ? 0 : 1;
            }

            attron(A_REVERSE);
            mvaddstr(19,64+n*6,Sex[n]);
            attroff(A_REVERSE);

        }

        else if ( key == ENTER ) {
            
            if ( n == 0 ) {
                sex = 1;
            }

            else { 
                sex = 0;
            }
            
            break;

        }
    }

    mvprintw(22,58,RegisteMenu[2]);
    getch();

    root = cJSON_CreateObject();
    item = cJSON_CreateNumber(0);
    cJSON_AddItemToObject(root, "type", item);
    item = cJSON_CreateString(name);
    cJSON_AddItemToObject(root,"name",item);
    item = cJSON_CreateBool(sex);
    cJSON_AddItemToObject(root ,"sex" ,item);
    item = cJSON_CreateString(password);
    cJSON_AddItemToObject(root,"password",item);
    char *out = cJSON_Print(root);

    if ( send(conn_fd, out, MSG_LEN, 0) < 0 ) {
        myerr("send", __LINE__);
    }    

    cJSON_Delete(root);
    free(out);
    
    recv_len = 0;
    while ( recv_len < MSG_LEN ) {
        
        ret = 0;
        
        if ( (ret = recv(conn_fd, message+recv_len, MSG_LEN-recv_len, 0)) <= 0 ) {
            myerr("recv", __LINE__);
        }

        recv_len += ret;

    }

    root = cJSON_Parse(message);
    item = cJSON_GetObjectItem(root, "res");
    flag = item->valueint;

    if ( flag == 1 ) {
        item = cJSON_GetObjectItem(root, "uid");
        id = item->valueint;
    }

    cJSON_Delete(root);

    clear();
    touchwin(stdscr);                    //激活stdrc窗口
    wrefresh(stdscr);                    //将窗口显示出来
    aboutWin = newwin(16, 40, 8, 48);
    Wind(aboutWin, 0, 0, 15, 39);
    touchwin(aboutWin);                
    wrefresh(aboutWin);


    if ( flag == 1 ) {
        mvprintw(12, 58, "******注册成功******");
        mvprintw(16, 58, "***这是你的验证码***");
        move(17, 67);
        printw("%d", id);
    }

    else {
        mvprintw(12, 58, "******注册失败******");
        mvprintw(16, 58, "*****用户已注册*****");
    }

    
    mvprintw(20,58,RegisteMenu[2]);
    getch();
    
    delwin(aboutWin);
    clear();
    DrawMain();

}
