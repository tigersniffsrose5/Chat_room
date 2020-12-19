#include "client.h"

void addgroup()
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

    bSubOpen = 0;                        //没在主函数界面，切换标志位 

    echo();
    curs_set(1);
    keypad(stdscr, TRUE);
    
    mvprintw(13, 58, "*请输入要加入的群聊名*");
    move(15,66);
    scanw("%s", name);    

    noecho();
    curs_set(0);
    
    mvprintw(17, 58,"*****按任意键继续*****");
    wrefresh(aboutWin);
    getch();

    root = cJSON_CreateObject();
    item = cJSON_CreateNumber(9);
    cJSON_AddItemToObject(root, "type", item);
    item = cJSON_CreateString(user_name);
    cJSON_AddItemToObject(root,"user_name",item);
    item = cJSON_CreateString(name);
    cJSON_AddItemToObject(root,"group_name",item);
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
