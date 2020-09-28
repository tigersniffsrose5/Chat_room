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




