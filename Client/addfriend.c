#include "client.h"

void addfriend()
{
    
    WINDOW *aboutWin;
    char name[30];
    cJSON *root;
    cJSON *item;

    aboutWin = newwin(8, 24, 15, 95);
    Wind(aboutWin, 0, 0, 7, 23);
    touchwin(aboutWin);                
    wrefresh(aboutWin);

    echo();
    curs_set(1);
    keypad(stdscr, FALSE);

    mvwaddstr(aboutWin, 2, 1, "*请输入待添加的好友名*");
    wrefresh(aboutWin);
    move(18,105);
    scanw("%s", name);

    while ( strcmp(name, user_name) == 0 ) {

        move(18,105);
        clrtoeol();         //清除输入行的内容

        mvwaddstr(aboutWin, 2, 1, "**不能添加自己请重输**");
        wrefresh(aboutWin);
        move(18,105);
        scanw("%s", name);

    }

    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);

    mvwprintw(aboutWin, 5, 1,"*****按任意键继续*****");
    wrefresh(aboutWin);
    getch();

    delwin(aboutWin);

    move(18,105);
    clrtoeol();         //清除输入行的内容

    touchwin(stdscr);                
    wrefresh(stdscr);

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

}


void add_friend(const char *message)
{
    WINDOW *aboutWin;
    int res, n = 0, key, ans;
    char name[30], Res[2][4] = {"是", "否"};

    aboutWin = newwin(8, 24, 15, 95);
    Wind(aboutWin, 0, 0, 7, 23);
    touchwin(aboutWin);                
    wrefresh(aboutWin);

    cJSON *root = cJSON_Parse(message);
    cJSON *item = cJSON_GetObjectItem(root ,"res");
    res = item->valueint;
    
    if ( res >= 3 ) {
    
        cJSON *item = cJSON_GetObjectItem(root ,"name");
        strcpy(name, item->valuestring);
    
    }

    if ( res == 3 ) {

        mvwaddstr(aboutWin, 2, 1, "*此用户想添加你为好友*");
        wrefresh(aboutWin);
        mvwaddstr(aboutWin, 3, 10, name);
        wrefresh(aboutWin);

        mvwaddstr(aboutWin, 5, 1, "*******是否同意*******");
        attron(A_REVERSE);
        mvwaddstr(aboutWin, 6, 8, Res[0]);
        attroff(A_REVERSE);
        mvwaddstr(aboutWin, 6, 11, "||");
        mvwaddstr(aboutWin, 6, 14, Res[1]);
        wrefresh(aboutWin);
        
        while ( 1 ) {

            key = getch();

            if ( key == KEY_LEFT || key == KEY_RIGHT ) {

                mvwaddstr(aboutWin, 6, 8+n*6, Res[n]);
                wrefresh(aboutWin);

                if ( key == KEY_LEFT ) {
                    n = n == 0 ? 1 : 0;
                }

                else {
                    n = n == 1 ? 0 : 1;
                }

                attron(A_REVERSE);
                mvwaddstr(aboutWin, 6, 8+n*6, Res[n]);
                attroff(A_REVERSE);
                wrefresh(aboutWin);
            
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
        cJSON_AddItemToObject(root,"user_name",item);
        item = cJSON_CreateString(name);
        cJSON_AddItemToObject(root,"friend_name",item);
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

        mvwaddstr(aboutWin, 2, 1, "*****此用户不存在*****");
        mvwprintw(aboutWin, 5, 1, "*****按任意键继续*****");
        wrefresh(aboutWin);
        getch();

    }

    else if ( res == 2 ) {

        mvwaddstr(aboutWin, 2, 1, "*此用户已经是你的好友*");
        mvwprintw(aboutWin, 5, 1, "*****按任意键继续*****");
        wrefresh(aboutWin);
        getch();    

    }

    else if ( res == 4 ) {

        mvwaddstr(aboutWin, 2, 1, "*此用户同意了你的请求*");
        mvwaddstr(aboutWin, 3, 10, name);
        mvwprintw(aboutWin, 5, 1, "*****按任意键继续*****");
        wrefresh(aboutWin);
        getch();

    }

    else if ( res == 5 ) {

        mvwaddstr(aboutWin, 2, 1, "*此用户拒绝了你的请求*");
        mvwaddstr(aboutWin, 3, 10, name);
        mvwprintw(aboutWin, 5, 1, "*****按任意键继续*****");
        wrefresh(aboutWin);
        getch();

    }

    delwin(aboutWin);
   
    touchwin(stdscr);                
    wrefresh(stdscr);

}
