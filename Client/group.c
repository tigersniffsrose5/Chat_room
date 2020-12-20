#include "client.h"

void group()
{
    WINDOW *aboutWin;
    int l, key;    
    char *str[2] = {"******创建群聊******", "******加入群聊******"};

    clear();
    touchwin(stdscr);                    //激活stdrc窗口
    wrefresh(stdscr);                    //将窗口显示出来
    aboutWin = newwin(16, 40, 8, 48);
    Wind(aboutWin, 0, 0, 15, 39);
    touchwin(aboutWin);
    wrefresh(aboutWin);

    bSubOpen = 0;

    noecho();
    curs_set(0);    
    keypad(stdscr, TRUE);

    attron(A_REVERSE);  
    mvaddstr(12, 58, str[0]);  
    attroff(A_REVERSE);
    mvaddstr(16, 58, str[1]);  
    
    l = 0;
    while ( 1 ) {

        key = getch();

        if ( key == KEY_UP || key == KEY_DOWN ) {

            mvaddstr(12+4*l, 58, str[l]);

            if ( key == KEY_UP ) {
                l = l == 0 ? 1 : 0;
            }

            else {
                l = l == 0 ? 1 : 0;
            }

            attron(A_REVERSE);
            mvaddstr(12+4*l, 58, str[l]);
            attroff(A_REVERSE);

        }

        else if ( key == ENTER ) {

            if ( l == 0 ) {
                creatgroup();                
                break;
            }

            else {
                addgroup();
                break;
            }

        }
    }

    clear();
    functionmenu();

}
