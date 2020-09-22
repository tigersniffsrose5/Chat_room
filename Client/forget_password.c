#include "client.h"

void forget_password()
{
    WINDOW *aboutWin;
    int ret, recv_len, flag = 0, code;
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
    mvprintw(16, 58, "****请输入验证码****");
    move(17,66);
    scanw("%d", &code);

    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);
    
    mvprintw(20,58,RegisteMenu[2]);
    getch();

    root = cJSON_CreateObject();
    item = cJSON_CreateNumber(2);
    cJSON_AddItemToObject(root, "type", item);
    item = cJSON_CreateString(name);
    cJSON_AddItemToObject(root,"name",item);
    item = cJSON_CreateNumber(code);
    cJSON_AddItemToObject(root,"code",item);
    item = cJSON_CreateNumber(flag);
    cJSON_AddItemToObject(root,"flag",item);
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

        curs_set(1);
        keypad(stdscr, FALSE);

        mvprintw(12, 58, "****验证身份成功****");
        mvprintw(16, 58, "****请输入新密码****");
        move(17,65);
        scanw("%s", password);

        curs_set(0);
        keypad(stdscr, TRUE);

        mvprintw(20,58,RegisteMenu[2]);
        getch();

        flag = 4;

        root = cJSON_CreateObject();
        item = cJSON_CreateNumber(2);
        cJSON_AddItemToObject(root, "type", item);
        item = cJSON_CreateString(name);
        cJSON_AddItemToObject(root,"name",item);
        item = cJSON_CreateNumber(code);
        cJSON_AddItemToObject(root,"code",item);
        item = cJSON_CreateNumber(flag);
        cJSON_AddItemToObject(root,"flag",item);
        item = cJSON_CreateString(password);
        cJSON_AddItemToObject(root,"password",item);
        char *out = cJSON_Print(root);
        
        if ( send(conn_fd, out, MSG_LEN, 0) < 0 ) {
            my_err("send", __LINE__);
        }

        cJSON_Delete(root);
        free(out);

        clear();
        touchwin(stdscr);                    //激活stdrc窗口
        wrefresh(stdscr);                    //将窗口显示出来
        aboutWin = newwin(16, 40, 8, 48);
        Wind(aboutWin, 0, 0, 15, 39);
        touchwin(aboutWin);
        wrefresh(aboutWin);

        mvprintw(12, 58, "****修改密码成功****");
        mvprintw(16, 58, "***请保存好新密码***");
 
    }

    else if ( flag == 1 ) {

        mvprintw(12, 58, "****验证身份失败****");
        mvprintw(16, 58, "*****没有此用户*****");
    
    }

    else if ( flag == 2 ) {
        
        mvprintw(12, 58, "****验证身份失败****");
        mvprintw(16, 58, "*****验证码错误*****");
    
    }

    mvprintw(20,58,RegisteMenu[2]);
    getch();

    delwin(aboutWin);
    clear();
    DrawMain();

}


