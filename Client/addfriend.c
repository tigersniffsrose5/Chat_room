#include "client.h"

void addfriend()
{
    
    WINDOW *aboutWin;
    char name[30];
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
    
    mvprintw(13, 58, "*请输入待添加的好友名*");
    move(15,66);
    scanw("%s", name);    

    while ( strcmp(name, user_name) == 0 ) {

        move(15,66);
        clrtoeol();         //清除输入行的内容

        mvprintw(13, 58, "**不能添加自己请重输**");
        mvprintw(15, 87, "|");
        wrefresh(aboutWin);
        move(15,66);
        scanw("%s", name);    

    }

    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);
    
    mvprintw(17, 58,"*****按任意键继续*****");
    wrefresh(aboutWin);
    getch();

    root = cJSON_CreateObject();
    item = cJSON_CreateNumber(4);
    cJSON_AddItemToObject(root, "type", item);
    item = cJSON_CreateString(user_name);
    cJSON_AddItemToObject(root,"user_name",item);
    item = cJSON_CreateString(name);
    cJSON_AddItemToObject(root,"friend_name",item);
    item = cJSON_CreateNumber(1);
    cJSON_AddItemToObject(root, "flag", item);
    char *out = cJSON_Print(root);
    
    if ( send(conn_fd, out, MSG_LEN, 0) < 0 ) {
        myerr("send", __LINE__);
    }    

    cJSON_Delete(root);
    free(out);

    delwin(aboutWin);
    clear();
    functionmenu();

}


void add_friend(const char *message)
{
    WINDOW *aboutWin;
    int res, n = 0, key, ans;
    char friend_name[30], Res[2][4] = {"是", "否"};

    clear();
    touchwin(stdscr);                    //激活stdrc窗口
    wrefresh(stdscr);                    //将窗口显示出来
    aboutWin = newwin(16, 40, 8, 48);
    Wind(aboutWin, 0, 0, 15, 39);
    touchwin(aboutWin);                
    wrefresh(aboutWin);

    noecho();
    curs_set(0);

    bSubOpen = 0;                        //没在主函数界面，切换标志位 

    cJSON *root = cJSON_Parse(message);
    cJSON *item = cJSON_GetObjectItem(root, "res");
    res = item->valueint;
    item = cJSON_GetObjectItem(root, "friend_name");
    strcpy(friend_name, item->valuestring);
    
    cJSON_Delete(root);

    if ( res == 3 ) {

        keypad(stdscr, TRUE);
        mvaddstr(13, 58, "*此用户想添加你为好友*");
        mvaddstr(15, 66, friend_name);
        mvaddstr(17, 58, "*******是否同意*******");
        attron(A_REVERSE);
        mvaddstr(18, 64, Res[0]);
        attroff(A_REVERSE);
        mvaddstr(18, 67, "||");
        mvaddstr(18, 70, Res[1]);
        wrefresh(aboutWin);

        while ( 1 ) {

            mvprintw(18, 87, "|");
            key = getch();
            
            if ( key == KEY_LEFT || key == KEY_RIGHT ) {

                mvaddstr(18, 64+n*6, Res[n]);

                if ( key == KEY_LEFT ) {
                    n = n == 0 ? 1 : 0;
                }

                else {
                    n = n == 1 ? 0 : 1;
                }

                attron(A_REVERSE);
                mvaddstr(18, 64+n*6, Res[n]);
                attroff(A_REVERSE);
            
            }

            else if ( key == ENTER ) {

                if ( n == 0 ) {
                    ans = 1;
                }

                else {
                    ans = 0;
                }

                break;

            }
        }

        root = cJSON_CreateObject();
        item = cJSON_CreateNumber(4);
        cJSON_AddItemToObject(root, "type", item);
        item = cJSON_CreateString(user_name);
        cJSON_AddItemToObject(root, "user_name", item);
        item = cJSON_CreateString(friend_name);
        cJSON_AddItemToObject(root, "friend_name", item);
        item = cJSON_CreateNumber(2);
        cJSON_AddItemToObject(root, "flag", item);
        item = cJSON_CreateNumber(ans);
        cJSON_AddItemToObject(root, "ans", item);
        char *out = cJSON_Print(root);

        if ( send(conn_fd, out, MSG_LEN, 0) < 0 ) {
            myerr("send", __LINE__);
        }    

        cJSON_Delete(root);
        free(out);
    
    }

    else if ( res == 1 ) {

        mvaddstr(13, 58, "*****此用户不存在*****");
        mvaddstr(15, 66, friend_name);
        mvprintw(17, 58, "*****按任意键继续*****");
        getch();

    }

    else if ( res == 2 ) {

        mvaddstr(13, 58, "*此用户已经是你的好友*");
        mvaddstr(15, 66, friend_name);
        mvprintw(17, 58, "*****按任意键继续*****");
        getch();

    }

    else if ( res == 4 ) {

        mvaddstr(13, 58, "*此用户同意了你的请求*");
        mvaddstr(15, 66, friend_name);
        mvprintw(17, 58, "*****按任意键继续*****");
        getch();

    }

    else if ( res == 5 ) {

        mvaddstr(13, 58, "*此用户拒绝了你的请求*");
        mvaddstr(15, 66, friend_name);
        mvprintw(17, 58, "*****按任意键继续*****");
        getch();

    }

    delwin(aboutWin);

}
