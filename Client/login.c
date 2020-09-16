#include "client.h"

void login()
{
   WINDOW *aboutWin;
   int ret, recv_len, flag;
   char name[30];
   char password[30];
   char message[MSG_LEN];
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

    mvprintw(12, 58, RegisteMenu[0]);
    move(13,65);
    scanw("%s", name);
    mvprintw(16, 58, RegisteMenu[1]);
    move(17,65);
    noecho();
    scanw("%s", password);
    
    curs_set(0);
    keypad(stdscr, TRUE);
    
    mvprintw(20,58,RegisteMenu[2]);
    getch();

    root = cJSON_CreateObject();
    item = cJSON_CreateNumber(1);
    cJSON_AddItemToObject(root, "type", item);
    item = cJSON_CreateString(name);
    cJSON_AddItemToObject(root,"name",item);
    item = cJSON_CreateString(password);
    cJSON_AddItemToObject(root,"password",item);
    char *out = cJSON_Print(root);

    if ( send(conn_fd, out, MSG_LEN, 0) < 0 ) {
        my_err("send", __LINE__);
    }

    cJSON_Delete(root);
    free(out);

    recv_len = 0;
    while ( recv_len < MSG_LEN ) {

        ret = 0;

        if ( (ret = recv(conn_fd, message+recv_len, MSG_LEN-recv_len, 0)) <= 0 ) {
            my_err("recv", __LINE__);
        }

        recv_len += ret;

    }

    root = cJSON_Parse(message);
    item = cJSON_GetObjectItem(root, "res");
    flag = item->valueint;
    cJSON_Delete(root);

    clear();
    touchwin(stdscr);                    //激活stdrc窗口
    wrefresh(stdscr);                    //将窗口显示出来
    aboutWin = newwin(16, 40, 8, 48);
    Wind(aboutWin, 0, 0, 15, 39);
    touchwin(aboutWin);
    wrefresh(aboutWin);


    if ( flag == 3 ) {
    
        mvprintw(14, 58, "******登录成功******");
    
    }

    else if ( flag == 1 ) {
        
        mvprintw(14, 58, "******登录失败******");
        mvprintw(18, 58, "*****用户已登录*****");
    
    }

    else if ( flag == 2 ) {
        
        mvprintw(14, 58, "******登录失败******");
        mvprintw(18, 58, "******密码错误******");

    }

    mvprintw(22,58,RegisteMenu[2]);
    getch();

    delwin(aboutWin);
    clear();
    DrawMain();

}

char *pas(char *s)
{
    char ch;
    int i = 0;

    strcpy(s, "");
    
    while ( 1 ) {
		
        ch = getch1();
        
        if ( ch == 13 )
            break;
        
        s[i] = ch;
        
        if ( s[i] == 127 ) {
            
            printw("\b \b");
            
            i = i-2;
            if ( i < 0 ) {
                i = 0;
                continue;
            }

        }

        else 
            printw("*");
        
        i++;

    }
    
    s[i] = '\0';
    return s;

}

int getch1(void)
{
     struct termios tm, tm_old;
     int fd = 0, ch;

     if (tcgetattr(fd, &tm) < 0) {
          return -1;
     }

     tm_old = tm;
     cfmakeraw(&tm);
     if (tcsetattr(fd, TCSANOW, &tm) < 0) {
          return -1;
     }

     ch = getch();
     if (tcsetattr(fd, TCSANOW, &tm_old) < 0) {
         return -1;
     }

     return ch;
}
