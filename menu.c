#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <string.h>

#define ESC 27
#define ENTER '\r'
#define TAB '\t'
#define Backspace 8
#define SPACE 32
#define UpRow 0
#define DownRow 23
#define LeftCol 0
#define RightCol 79
#define MAINI 5
#define SBI1 2
#define SBI2 3
#define SBI3 3
#define SBI4 4
#define SBI5 3

void Initial(void);
void BkScreen(void);
void DrawMain(void);
void DrawSub(void);
void SelectMenu(void);
void SelectMainMenu(void);
void SelectMSubMenu(void);
void QuitProg(void);
void Wind(WINDOW *, int, int, int, int);
void Process(int, char *);

int ActMm = 0;
int key = 0;
int bSubOpen = 0;
char *MainMenu[MAINI] = { "file", "Menu 1", "Menu 2", "Menu 3", "Menu 4" };
int SubNum[MAINI] = { SBI1, SBI2, SBI3, SBI4, SBI5 };
int SubWid[MAINI] = { 6, 10, 10, 10, 10 };
int SubCol[MAINI] = { 4, 16, 28, 40, 52 };
int ActSm[MAINI] = { 0, 0, 0, 0, 0 };
char *SubMenu[MAINI][10] {
    { "About", "Exit" },
    { "Menu 1-1", "Menu 1-2", "Menu 1-3" },
    { "Menu 2-1", "Menu 2-2", "Menu 2-3" },
    { "Menu 3-1", "Menu 3-2", "Menu 3-3" },
    { "Menu 4-1", "Menu 4-2", "Menu 4-3" },
};

int main()
{
    Initial();
    clear();
    refresh();
    BkScreen();
    DrawMain();
    SelectMenu();
}

void Initial(void)
{
    initscr();
    cbreak();
    nonl();
    noecho();
    keypad(stdscr, TRUE);
    refresh();
}

void BkScreen(void)
{
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

    Wind(stdscr, UpRow, LeftCol, DownRow, RightCol);

    for ( int i = 0; i < 23; i++ ) {
        mvwaddstr(stdscr, 8+i, 12, strArr[i]);
    }
}

void DrawMain(void)
{
    int i;

    for ( i = 0; i < MAINI; i++ ) {
        mvaddstr(UpRow+1, SubCol[i], MainMenu[i]);
    }

    attron(A_REVERSE);
    mvaddstr(UpRow+1, SubCol[ActMm], MainMenu[ActMm]);
    attroff(A_REVERSE);
    move(UpRow+1, SubCol[ActMm]);

}

void SelectMenu(void)
{
    while (1) {
        key = getch();

        if ( key == KEY_LEFT || key == KEY_RIGHT ) {
            SelectMainMenu();
        }

        else if (( key == KEY_UP || key == KEY_DOWN ) && ( bSubOpen == 1 )) {
            SelectMSubMenu();
        }

        else if ( key == ENTER ) {
            if ( bSubOpen == 1 ) {
                switch ( ActMm ) { 
                
                case 0:
                    switch ( ActSm[ActMm] ) {
                    case 0:
                        Process(0, " ");
                        break;
                    case 1:
                        QuitProg();
                        break;
                    default:
                        break;
                    }
                    break;
                
                case 1:
                    switch ( ActSm[ActMm] ) {
                    case 0:
                        Process(1, "Process Menu 1-1");
                        break;
                    case 1:
                        Process(1, "Process Menu 1-2");
                        break;
                    case 2:
                        Process(1, "Process Menu 1-3");
                        break;
                    default:
                        break;
                    }
                    break;
                 
                case 2:
                    switch ( ActSm[ActMm] ) {
                    case 0:
                        Process(1, "Process Menu 2-1");
                        break;
                    case 1:
                        Process(1, "Process Menu 2-2");
                        break;
                    case 2:
                        Process(1, "Process Menu 2-3");
                        break;
                    default:
                        break;
                    }
                    break;
                 
                 case 3:
                    switch ( ActSm[ActMm] ) {
                    case 0:
                        Process(1, "Process Menu 3-1");
                        break;
                    case 1:
                        Process(1, "Process Menu 3-2");
                        break;
                    case 2:
                        Process(1, "Process Menu 3-3");
                        break;
                    default:
                        break;
                    }
                    break;
                 
                 case 4:
                    switch ( ActSm[ActMm] ) {
                    case 0:
                        Process(1, "Process Menu 4-1");
                        break;
                    case 1:
                        Process(1, "Process Menu 4-2");
                        break;
                    case 2:
                        Process(1, "Process Menu 4-3");
                        break;
                    default:
                        break;
                    }
                    break;
                
                 default:
                    break;
                }
                
                bSubOpen = 0;
                BkScreen();
                DrawMain();
            }

            else {
                bSubOpen = 1;
                DrawSub();
            }
        }
    }
}

void SelectMainMenu(void)
{
    if ( bSubOpen == 0 ) {
        
        mvaddstr(UpRow+1, SubCol[ActMm], MainMenu[ActMm]);

        if ( key == KEY_LEFT ) {
            ActMm = ActMm == 0 ? MAINI-1 : ActMm-1;
        } 

        else {
            ActMm = ActMm == MAINI-1 ? 0 : ActMm+1;
        }

        attron(A_REVERSE);
        mvaddstr(UpRow+1, SubCol[ActMm], MainMenu[ActMm]);
        attroff(A_REVERSE);
        move(UpRow+1, SubCol[ActMm]);
    }

    else {

        if ( key == KEY_LEFT ) {
            ActMm = ActMm == 0 ? MAINI-1 : ActMm-1;
        }

        else {
            ActMm = ActMm == MAINI-1 ? 0 : ActMm+1;
        }

        clear();
        refresh();
        BkScreen();
        DrawMain();
        DrawSub();
    }
}

void SelectMSubMenu(void)
{
    attoff(A_REVERSE);
    mvaddstr(UpRow+3+ActMm[ActMm], SubCol[ActMm]+2, SubMenu[ActMm][ActSm[ActMm]]);
    
    if ( key == KEY_UP ) {
        ActSm[ActMm] = ActSm[ActMm] == 0 ? SubNum[ActMm]-1 : ActSm[ActMm]-1;
    } 

    else {
        ActSm[ActMm] = ActSm[ActMm] == SubNum[ActMm]-1 ? 0 : ActSm[ActMm]+1;
    }

    attron(A_REVERSE);
    mvaddstr(UpRow+3+ActSm[ActMm], SubCol[ActMm]+2, SubMenu[ActMm][ActSm[ActMm]]);
    attroff(A_REVERSE);
    move(UpRow+3+ActSm[ActMm], SubCol[ActMm]+2);
}

void DrawSub(void)
{
    int i;
    Wind(stdscr, UpRow+2, SubCol[ActMm], UpRow+2+SubNum[ActMm]+1, SubCol[ActMm]+SubWid[ActMm]+1);
    for ( i = 0; i < SubNum[ActMm]; i++ ) {
       
        if ( i == ActSm[ActMm] ) {
            attron(A_REVERSE);
            mvaddstr(UpRow+3+ActSm[ActMm], SubCol[ActMm]+2, SubMenu[ActMm[i]]);
            attoff(A_REVERSE);
        }

        else {
            mvaddstr(UpRow+3+i, SubCol[ActMm]+2, SubMenu[ActMm][i]);
        }

    }

    move(UpRow+3+ActSm[ActMm], SubCol[ActMm]+2);

}

void QuitProg(void)
{
    clear();
    refresh();
    endwin();
    exit(0);
}

void Wind(WINDOW *win, int nBeginRow, int nBeginCol, int nEndRow, int nEndCol)
{
    int i;
    
    for ( i = nBeginRow; i <= nEndRow; i++ ) {
        mvwaddch(win, i, nBeginCol, '|');
        mvwaddch(win, i, nEndCol, '|');
    }

    for ( i = nBeginCol; i <= nEndCol; i++ ) {
        mvwaddch(win, nBeginRow, i, '-');
        mvwaddch(win, nEndRow, i, '-');
    }

}

void Process(int flag, chat *str)
{
    WINDOW *aboutWin;
    clear();

}
