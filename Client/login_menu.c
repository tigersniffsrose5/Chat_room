#include "client.h"

int qsj = 1;            //登录菜单判断是否退出的标志
int ActMm = 0;          //代表当前主菜单激活的号码
int key = 0;            //用户从键盘输如的选择
char *MainMenu[5] = { "********退出********", "********登录********", "********注册********", "******找回密码******", "********更多********" };     //登录菜单


int login_menu()
{

    setlocale(LC_ALL,"");
    Initial();                                              //初始化函数      
    clear();              
    refresh();            
    curs_set(0);                                            //隐藏光标，0隐藏 1正常 2高亮显示
    DrawMain();                                             //在屏幕上画出主菜单
    SelectMenu();                                           //对用户的操作进行相应的处理
    
    return 0;
}

void Initial(void)
{
    
    initscr();                //初始化终端，启动curses模式
    cbreak();                 //将系统输入的字符立刻读取 
    nonl();                   //使enter键不被识别为'\n'
    noecho();                 //关闭回显开关，使用户输入的不会被显示在屏幕上                         
    keypad(stdscr, TRUE);     //处理方向键
    refresh();                //刷新

}



void DrawMain(void)           //画主菜单                  
{
 
    int i;
    char strArr[4][51];

    strcpy(strArr[0], "**************************************************");
    strcpy(strArr[1], "*                   Welcome to                   *");
    strcpy(strArr[2], "*                    ChatRoom                    *");
    strcpy(strArr[3], "**************************************************");
    
    Wind(stdscr, UpRow, LeftCol, DownRow, RightCol);        //主界面边框

    mvaddstr(3, 15+LeftCol, strArr[0]);
    mvaddstr(4, 15+LeftCol, strArr[1]);
    mvaddstr(5, 15+LeftCol, strArr[2]);
    mvaddstr(6, 15+LeftCol, strArr[3]);


    for ( i = 0; i < 5; i++ ) {
        mvaddstr(10+i*4, 30+LeftCol, MainMenu[i]);     //打印主菜单
    }

    attron(A_REVERSE);  
    mvaddstr(10+ActMm*4, 30+LeftCol, MainMenu[ActMm]);     //将主菜单以反显的方式显示
    attroff(A_REVERSE);

}

void SelectMenu(void)         //处理用户按键，调用相应的功能函数    
{
    
    while ( qsj != 0 ) {

        key = getch();

        if ( key == KEY_UP || key == KEY_DOWN ) {
            SelectMainMenu();
        }

        else if ( key == ENTER ) {
            
            switch ( ActMm ) { 

            case 0:
                QuitProg();
                qsj = 0;
                break;

            case 1:
                break;
            
            case 2:
                break;
            
            case 3:
                break;

            case 4:
                break;

            default:
                break;
            
            }
        }
    }
}

void SelectMainMenu(void)
{
    mvaddstr(10+ActMm*4, 30+LeftCol, MainMenu[ActMm]); 

    if ( key == KEY_UP ) {
        ActMm = ActMm == 0 ? ActMm+4 : ActMm-1;
    } 

    else {
        ActMm = ActMm == 4 ? 0 : ActMm+1;
    }

    attron(A_REVERSE);
    mvaddstr(10+ActMm*4, 30+LeftCol, MainMenu[ActMm]);
    attroff(A_REVERSE);
}
 
void QuitProg(void)      //退出函数
{
    clear();
    refresh();
    endwin();
}

void Wind(WINDOW *win, int nBeginRow, int nBeginCol, int nEndRow, int nEndCol)   //构造边框函数
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

void Process(char *str1, char *str2)        //显示内容不同的对话框
{
    WINDOW *aboutWin;                    //声明一个新的窗口
    clear();
    touchwin(stdscr);                    //激活stdrc窗口
    wrefresh(stdscr);                    
    aboutWin = newwin(13, 40, 8, 48);
    Wind(aboutWin, 0, 0, 12, 39);

    mvwaddstr(aboutWin, 2, 10, str1);
    mvwaddstr(aboutWin, 6, 10, str2);

    wattron(aboutWin, A_REVERSE);
    mvwaddstr(aboutWin, 9, 6, "Press any key to continue...");
    wattroff(aboutWin, A_REVERSE);
    touchwin(aboutWin);
    wrefresh(aboutWin);
    getch();
    delwin(aboutWin);
    clear();
    DrawMain();
}
