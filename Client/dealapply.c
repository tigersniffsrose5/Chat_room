#include "client.h"

void dealapply()
{
    WINDOW *aboutWin;
    int hang = 12;
    int i, l, key;
    char str[10][30];
    char str_name[10][30];
    Message_box *head = friend_request;

    clear();
    touchwin(stdscr);                    //激活stdrc窗口
    wrefresh(stdscr);                    //将窗口显示出来
    aboutWin = newwin(16, 40, 8, 48);
    Wind(aboutWin, 0, 0, 15, 39);
    touchwin(aboutWin);                
    wrefresh(aboutWin);

    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);

    bSubOpen = 0;                        //没在主函数界面，切换标志位 

    mvaddstr(10, 58, "****好友申请列表****");

    i = 0;
    while ( head != NULL ) {
        strcpy(str[i], head->recv_name);
        strcpy(str_name[i], head->recv_name);
        strcat(str[i], "的申请信息");
        mvaddstr(hang, 61, str[i]);
        hang += 2;
        i++;
        head = head->next; 
    }

    strcpy(str[i], "*****返回*****");
    mvaddstr(hang, 61, str[i]);
    
    attron(A_REVERSE);  
    mvaddstr(12, 61, str[0]);  
    attroff(A_REVERSE);

    l = 0;
    while ( 1 ) {

        mvprintw(12, 87, "|");
        key = getch();

        if ( key == KEY_UP || key == KEY_DOWN ) {

            mvaddstr(12+2*l, 61, str[l]);
            
            if ( key == KEY_UP ) {
                l = l == 0 ? l+i : l-1; 
            }

            else {
                l = l == i ? 0 : l+1;
            }

            attron(A_REVERSE);  
            mvaddstr(12+2*l, 61, str[l]);  
            attroff(A_REVERSE);

        }

        else if ( key == ENTER ) {
            break;    
        }
    }

    if ( l != i ) {
        
        head = friend_request;

        while ( head != NULL ) {
            if ( strcmp(head->recv_name, str_name[l]) == 0 ) {
                add_friend(head->message);
            }
            head = head->next;
        }

        delet(&friend_request, str_name[l]);

    }

    delwin(aboutWin);

    clear();
    functionmenu();

}
