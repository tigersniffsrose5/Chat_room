#include "client.h"

void friendfunction(const char *friend_name)
{
    WINDOW *aboutWin;
    int key, l;
    char str[3][20] = {"**发消息**", "**发文件**", "***返回***"};

    aboutWin = newwin(11, 22, 11, 93);
    Wind(aboutWin, 0, 0, 10, 21);
    touchwin(aboutWin);
    wrefresh(aboutWin);

    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);

    bSubOpen = 0;                        //没在主函数界面，切换标志位 

    mvprintw(13, 96, "****选择功能****");
    mvprintw(15, 99, str[0]);
    mvprintw(17, 99, str[1]);
    mvprintw(19, 99, str[2]);
    wrefresh(aboutWin);

    attron(A_REVERSE);  
    mvprintw(15, 99, str[0]);  
    attroff(A_REVERSE);

    l = 0;
    while ( 1 ) {

        key = getch();

        if ( key == KEY_UP || key == KEY_DOWN ) {

            mvprintw(15+2*l, 99, str[l]);

            if ( key == KEY_UP ) {
                l = l == 0 ? 2 : l-1; 
            }

            else {
                l = l == 2 ? 0 : l+1;
            }

            attron(A_REVERSE);  
            mvprintw(15+2*l, 99, str[l]);  
            attroff(A_REVERSE);

        }

        else if ( key == ENTER ) {

            if ( l == 0 ) { 
                friendchat(friend_name);
                break;
            }
            
            else if ( l == 2 )
                break;
        }
    }

    wclear(aboutWin);
    wrefresh(aboutWin);

    delwin(aboutWin);
    wrefresh(stdscr);
}
