#include <curses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    int ch, i;
    WINDOW *alertWindow;
    char strArr[23][200];
    
    strcpy(strArr[0], "                                                                                                                        ");
    strcpy(strArr[1], "                                                                                                                        ");
    strcpy(strArr[2], "           @@@@@@@@@  @            @@@@@@@@   @@@@@@@@                    @@                                            ");
    strcpy(strArr[3], "          @@@@@@@@@@@@@            @@@@@@@    @@@@@@@@                   @@@                    @@@@@@@@@@@@@@@@@       ");
    strcpy(strArr[4], "        @@@@@@    @@@@@              @@@@       @@@@                     @@@                    @@@@@@@@@@@@@@@@@       ");
    strcpy(strArr[5], "       @@@@@@       @@@              @@@         @@@                    @@@@@                   @@@    @@@    @@@       ");
    strcpy(strArr[6], "       @@@@@         @@              @@@         @@@                    @@@@@                   @@     @@@     @@       ");
    strcpy(strArr[7], "      @@@@@          @@              @@@         @@@                   @@@@@@@                  @@     @@@      @       ");
    strcpy(strArr[8], "      @@@@@           @              @@@         @@@                   @@@@@@@                         @@@              ");
    strcpy(strArr[9], "      @@@@                           @@@         @@@                  @@@@@@@@@                        @@@              ");
    strcpy(strArr[10], "     @@@@@                           @@@         @@@                  @@@  @@@@                        @@@              ");
    strcpy(strArr[11], "     @@@@@                           @@@@@@@@@@@@@@@                  @@@  @@@@@                       @@@              ");
    strcpy(strArr[12], "     @@@@@                           @@@@@@@@@@@@@@@                 @@@    @@@@                       @@@              ");
    strcpy(strArr[13], "     @@@@@                           @@@         @@@                 @@@@@@@@@@@                       @@@              ");
    strcpy(strArr[14], "      @@@@                           @@@         @@@                @@@@@@@@@@@@@                      @@@              ");
    strcpy(strArr[15], "      @@@@@                          @@@         @@@                @@@      @@@@                      @@@              ");
    strcpy(strArr[16], "      @@@@@@          @              @@@         @@@               @@@@      @@@@@                     @@@              ");
    strcpy(strArr[17], "        @@@@@@      @@@              @@@@       @@@@              @@@@        @@@@@                    @@@              ");
    strcpy(strArr[18], "         @@@@@@@@@@@@@             @@@@@@@     @@@@@@@           @@@@@        @@@@@@                  @@@@@             ");
    strcpy(strArr[19], "          @@@@@@@@@@@              @@@@@@@@   @@@@@@@@           @@@@@       @@@@@@@@               @@@@@@@@@           ");
    strcpy(strArr[20], "             @@@@@                                                                                  @@@@@@@@@           ");
    strcpy(strArr[21], "                                                                                                                        ");
    strcpy(strArr[22], "                                                                                                                        ");
    
    initscr();
    noecho();
    keypad(stdscr,TRUE);
    refresh();
    box(stdscr,'|', '-');

    for ( i = 0; i < 22; i++ ) {
        mvwaddstr(stdscr, 8+i, 8, strArr[i]);
    }

    alertWindow = newwin(8,40,6,20);

    while ( (ch = getch()) != 'q' ) {
        box(alertWindow, '|', '-');
        mvwaddstr(alertWindow, 2, 8, "This is a pop up window");
        mvwaddstr(alertWindow, 4, 8, "Press any key to continue");
        wattron(alertWindow, A_REVERSE);
        mvwaddstr(alertWindow, 6, 18, "OK");
        //wattroff(alertWindow,A_REVERSE);
        touchwin(alertWindow);
        wrefresh(alertWindow);
        getch();
        touchwin(stdscr);
        wrefresh(stdscr);
    }

    delwin(alertWindow);
    endwin();
}
