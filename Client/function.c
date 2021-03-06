#include "client.h"

char *Function_menu[2][3] = {
    "|选择好友|", "|选择群聊|", "|处理申请|",
    "|添加好友|", "|群聊管理|", "|注销登录|"
};
int KEY = 0;
int row = 0;     //行
int col = 0;     //列
int ans;

void function()
{
    Initial();                                              //初始化函数
    clear();
    refresh();
    curs_set(0);                                            //隐藏光标，0隐藏 1正常 2高亮显示
    functionmenu();                                             
    SelectfunctionMenu();                                           

}

void functionmenu()
{
    char strArr[4][51];

    bSubOpen = 1;                  //功能主界面标志位

    Wind(stdscr, 3, 42, 34, 93);

    strcpy(strArr[0], "**************************************************");
    strcpy(strArr[1], "*                   Welcome to                   *");
    strcpy(strArr[2], "*                    ChatRoom                    *");
    strcpy(strArr[3], "**************************************************");

    mvaddstr(4, 15+LeftCol, strArr[0]);
    mvaddstr(5, 15+LeftCol, strArr[1]);
    mvaddstr(6, 15+LeftCol, strArr[2]);
    mvaddstr(7, 15+LeftCol, strArr[3]);

    for ( int i = 0; i < 2; i++ ) {
        for ( int j = 0; j < 3; j++ ) {
            mvaddstr(10+2*i, 47+j*16, Function_menu[i][j]);
        }
    }

    attron(A_REVERSE);  
    mvaddstr(10+2*row, 47+col*16, Function_menu[row][col]);
    attroff(A_REVERSE);

    mvaddstr(15, 15+LeftCol, strArr[3]);
    
    x = 16;

    if ( strlen(file_message) != 0 ) {
        
        mvaddstr(x, 15+LeftCol, file_message);
        __sync_fetch_and_add(&x, 1);
        memset(file_message, 0, sizeof(file_message));

    }

    if ( friend_request != NULL ) { 
        mvaddstr(x, 15+LeftCol, "你有未处理的好友申请信息");
        __sync_fetch_and_add(&x, 1);
    }
    
    if ( friend_chat != NULL ) { 
        mvaddstr(x, 15+LeftCol, "你有未处理的好友聊天信息");
        __sync_fetch_and_add(&x, 1);
    }

    if ( group_chat != NULL ) { 
        mvaddstr(x, 15+LeftCol, "你有未处理的群聊信息");
        __sync_fetch_and_add(&x, 1);
    }

}

void SelectfunctionMenu()
{

    while ( 1 ) {

        KEY = getch();

        if ( KEY == KEY_UP || KEY == KEY_DOWN ) {
            SelectfunctionMenurow();
        }

        else if ( KEY == KEY_LEFT || KEY == KEY_RIGHT ) {
            SelectfunctionMenucol();
        }

        else if ( KEY == ENTER ) {

            if ( row == 0 )
                ans = 1+col;
            else 
                ans = 4+col;

            switch ( ans ) { 

            case 1:
                mutex_t = 0;
                friendlist();    
                while ( mutex_t != 1 )                      //等待从服务器获取数据
                    continue;
                choosefriend();
                break;

            case 2:
                mutex_t = 0;
                grouplist();    
                while ( mutex_t != 1 )                      //等待从服务器获取数据
                    continue;
                choosegroup();
                break;

            case 3:
                dealapply();
                break;

            case 4:
                addfriend();
                break;
            
            case 5:
                group();
                break;
            
            case 6:
                logout();
                row = col = 0;
                bSubOpen = 0;
                fre(&friend_request);
                fre(&friend_chat);
                fre(&group_chat);
                return;

            }
        }
    }

}

void SelectfunctionMenurow()
{
    mvaddstr(10+2*row, 47+col*16, Function_menu[row][col]);
    
    if ( KEY == KEY_UP ) {
        row = row == 0 ? 1 : 0;
    }

    else  {
        row = row == 1 ? 0 : 1;
    }

    attron(A_REVERSE);  
    mvaddstr(10+2*row, 47+col*16, Function_menu[row][col]);
    attroff(A_REVERSE);

}

void SelectfunctionMenucol()
{    

    mvaddstr(10+2*row, 47+col*16, Function_menu[row][col]);

    if ( KEY == KEY_LEFT ) {
        col = col == 0 ? col+2 : col-1;
    }

    else  {
        col = col == 2 ? 0 : col+1;
    }

    attron(A_REVERSE);  
    mvaddstr(10+2*row, 47+col*16, Function_menu[row][col]);
    attroff(A_REVERSE);

}
