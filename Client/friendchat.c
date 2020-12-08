#include "client.h"

void friendchat(const char *friend_name)
{
    int key, n;
    char s[100];
    char s1[100];
    char str[2][15] = {"确认发送", "退出私聊"};
    time_t timep;

    friendchat_menu(friend_name);

    bSubOpen = 0;                  //功能主界面标志位
    bSubOpen_friend = 1;
    
    while ( 1 ) {

        echo();
        curs_set(1);   
        keypad(stdscr, TRUE);

        move(31, 43);
        bzero(s, sizeof(s));
        scanw("%s", s);
        time(&timep);
        
        noecho();
        curs_set(0);

        n = 0;
        while (1) {

            key = getch();

            if ( key == KEY_LEFT || key == KEY_RIGHT ) {

                mvaddstr(33, 68+n*14, str[n]);

                if ( key == KEY_LEFT ) {
                    n = n == 0 ? 1 : 0;
                }

                else {
                    n = n == 1 ? 0 : 1;
                }

                attron(A_REVERSE);
                mvaddstr(33, 68+n*14, str[n]);
                attroff(A_REVERSE);

            }

            else if ( key == ENTER ) {

                if ( n == 0 ) {
                
                   if ( friend_x == 30 ) {
                        clear();
                        friendchat_menu(friend_name);
                    }

                    mvaddstr(friend_x, 27+LeftCol, ctime(&timep));
                    mvprintw(friend_x++, 92, "|");
                    bzero(s1, sizeof(s1));
                    sprintf(s1, "%s:", user_name);
                    mvaddstr(friend_x, 92-Strlen(s), s);
                    mvaddstr(friend_x++, 92-Strlen(s1)-Strlen(s), s1);

                    move(31, 43);
                    clrtoeol();
                    mvprintw(31, 92, "|");
 
                }

                    break;

            }

        }

        if ( n == 1 )
            break;

    }

    bSubOpen_friend = 0;
}

void friendchat_menu(const char *friend_name)
{
    char strArr[4][51];
    char str[2][15] = {"确认发送", "退出私聊"};

    bSubOpen = 0;                  //功能主界面标志位
    bSubOpen_friend = 1;

    clear();
    Wind(stdscr, 3, 42, 34, 92);

    strcpy(strArr[0], "*************************************************");
    strcpy(strArr[1], "*                   chat with                   *");
    sprintf(strArr[2], "*                      %s                      *", friend_name);
    strcpy(strArr[3], "*************************************************");

    mvaddstr(4, 15+LeftCol, strArr[0]);
    mvaddstr(5, 15+LeftCol, strArr[1]);
    mvaddstr(6, 15+LeftCol, strArr[2]);
    mvaddstr(7, 15+LeftCol, strArr[3]);

    friend_x = 8;

    mvaddstr(30, 15+LeftCol, strArr[3]);
    attron(A_REVERSE);
    mvaddstr(33, 68, str[0]);
    attroff(A_REVERSE);
    mvaddstr(33, 82, str[1]);

}

int Strlen(const char *s)
{
    unsigned long i;

    int m, n;

    m = n = 0;
    for ( i = 0; i < strlen(s); i++ ) {
        
        if ( s[i] < 0 ) 
            m++;

        else 
            n++;

    }

    return m/3*2+n;
}
