#include "client.h"

void choosefriend()
{
    WINDOW *aboutWin;
    int hang = 12;
    int i, l, key, nums;
    char str_name[10][30];
    char str_sta[10][30];
    char num[3];
    User *head = friend_list;
    Message_box *p;

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

    mvaddstr(10, 58, "******好友列表******");

    i = 0;
    while ( head != NULL ) {
        strcpy(str_name[i], head->name);
        strcpy(str_sta[i], head->sta);
        mvaddstr(hang, 61, str_name[i]);
        mvaddstr(hang, 62+(strlen(head->name)-0), str_sta[i]);
        
        nums = 0;
        p = friend_chat;

        while ( p != NULL ) {
            if ( strcmp(p->recv_name, head->name) == 0 )
                nums++;
            p = p->next;
        }

        sprintf(num, "%d", nums);
        mvaddstr(hang, 63+(strlen(head->name)-0)+(strlen(head->sta)), num);
        hang += 2;
        i++;
        head = head->next; 
    }

    strcpy(str_name[i], "*****返回*****");
    mvaddstr(hang, 61, str_name[i]);
    
    attron(A_REVERSE);  
    mvaddstr(12, 61, str_name[0]);  
    attroff(A_REVERSE);

    l = 0;
    while ( 1 ) {

        mvprintw(12, 87, "|");
        key = getch();

        if ( key == KEY_UP || key == KEY_DOWN ) {

            mvaddstr(12+2*l, 61, str_name[l]);
            
            if ( key == KEY_UP ) {
                l = l == 0 ? i : l-1; 
            }

            else {
                l = l == i ? 0 : l+1;
            }

            attron(A_REVERSE);  
            mvaddstr(12+2*l, 61, str_name[l]);  
            attroff(A_REVERSE);

        }

        else if ( key == ENTER ) {
       
            if ( l == i )
                break;
            
            else {
                friendfunction(str_name[l]);
                break;
            } 
        
        }
    }
  
    clear();
    functionmenu();

}

