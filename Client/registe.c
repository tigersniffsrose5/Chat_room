#include "client.h"


void registe()
{
    int x,y;
    int key1 = 0;
    WINDOW *aboutWin;                    //声明一个新的窗口
    char str1[30];
    char str2[30];

    clear();
    touchwin(stdscr);                    //激活stdrc窗口
    wrefresh(stdscr);                    //将窗口显示出来
    aboutWin = newwin(13, 40, 8, 48);
    Wind(aboutWin, 0, 0, 12, 39);

    wattron(aboutWin, A_REVERSE);
    mvwaddstr(aboutWin, 2, 10, RegisteMenu[0]);
    wattroff(aboutWin, A_REVERSE);
    mvwaddstr(aboutWin, 6, 10, RegisteMenu[1]);

    mvwaddstr(aboutWin, 10, 10, RegisteMenu[2]);
    touchwin(aboutWin);                
    wrefresh(aboutWin);
    
    curs_set(1);        
    move(60,14);
    while (1) {

        key1 = getch();

        if ( key1 == KEY_UP || key1 == KEY_DOWN ) {
            SelectSubMenu(key1);
        }

        else if ( key1 == ENTER ) {
        
            nl();
            echo();

            switch( ActSm ) {

            case 0:
                getyx(aboutWin,y,x);
                printw("%d %d", x, y);
                //move(60,14);
                //scanw("%s", str1);
            }
        }

    }
}
