#include "client.h"


char *pas(char *s)
{
    char ch;
    int i = 0;

    strcpy(s, "");
    
    while ( 1 ) {
		ch = getch1();
        if ( ch == 13 )
            break;
        
        s[i] = ch;
        if ( s[i] == 127 ) {
            printf("\b \b");
            i = i-2;
            if ( i < 0 ) {
                i = 0;
                continue;
            }
        }
        else 
            printf("*");
        i++;
    }
    s[i] = '\0';
    return s;
}

int getch1(void)
{
     struct termios tm, tm_old;
     int fd = 0, ch;

     if (tcgetattr(fd, &tm) < 0) {
          return -1;
     }

     tm_old = tm;
     cfmakeraw(&tm);
     if (tcsetattr(fd, TCSANOW, &tm) < 0) {
          return -1;
     }

     ch = getchar();
     if (tcsetattr(fd, TCSANOW, &tm_old) < 0) {
         return -1;
     }

     return ch;
}
