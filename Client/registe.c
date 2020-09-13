#include "client.h"


void registe()
{
    WINDOW *aboutWin;                    //声明一个新的窗口
    int sex, key, n = 0, flag;
    char name[30];
    char password[30];
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
    mvaddstr(19,64, Sex[0]);
    attroff(A_REVERSE);
    mvaddstr(19,67, "||");
    mvaddstr(19,70, Sex[1]);
    
    while ( 1 ) {
        
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
    item = cJSON_CreateString("R");
    cJSON_AddItemToObject(root, "type", item);
    item = cJSON_CreateString(name);
    cJSON_AddItemToObject(root,"name",item);
    item = cJSON_CreateBool(sex);
    cJSON_AddItemToObject(root ,"sex" ,item);
    item = cJSON_CreateString(password);
    cJSON_AddItemToObject(root,"password",item);
    char *out = cJSON_Print(root);

    if ( send(conn_fd, out, 1024, 0) < 0 ) {
        my_err("send", __LINE__);
    }    

    cJSON_Delete(root);
    free(out);

    delwin(aboutWin);
    clear();
    DrawMain();

}
