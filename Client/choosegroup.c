#include "client.h"

void choosegroup()
{
    WINDOW *aboutWin;
    int hang = 12;
    int i, l, key, nums;
    char num[3];
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

    mvaddstr(10, 58, "******群聊列表******");

    i = 0;
    while ( strcmp(group_list[i], "") != 0 ) {
        
        mvaddstr(hang, 64, group_list[i]);
        
        nums = 0;
        p = group_chat;

        while ( p != NULL ) {
            if ( strcmp(p->recv_name, group_list[i]) == 0 )
                nums++;
            p = p->next;
        }

        sprintf(num, "%d", nums);
        mvaddstr(hang, 66+(strlen(group_list[i])-0), num);
        hang += 2;
        i++;
    
    }

    strcpy(group_list[i], "**返回**");
    mvaddstr(hang, 64, group_list[i]);
    
    attron(A_REVERSE);  
    mvaddstr(12, 64, group_list[0]);  
    attroff(A_REVERSE);

    l = 0;
    while ( 1 ) {

        mvprintw(12, 87, "|");
        key = getch();

        if ( key == KEY_UP || key == KEY_DOWN ) {

            mvaddstr(12+2*l, 64, group_list[l]);
            
            if ( key == KEY_UP ) {
                l = l == 0 ? i : l-1; 
            }

            else {
                l = l == i ? 0 : l+1;
            }

            attron(A_REVERSE);  
            mvaddstr(12+2*l, 64, group_list[l]);  
            attroff(A_REVERSE);

        }

        else if ( key == ENTER ) {
       
            if ( l == i )
                break;
            
            else {
//                groupchat(group_list[l]);
                break;
            } 
        
        }
    }
  
    clear();
    functionmenu();

}

