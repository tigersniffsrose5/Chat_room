#ifndef CLIENT_H
#define CLIENT_H

#include <stdio.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <signal.h>
#include <errno.h>
#include <termios.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>
#include <linux/socket.h>
#include<libgen.h>
#include <curses.h>
#include <locale.h>
#include "Common/cJSON.h"
#include "Common/libb64/include/b64/cdecode.h"
#include "Common/libb64/include/b64/cencode.h"

#define PORT 1212
#define ENTER '\r'
#define UpRow 0         //行起始
#define DownRow 30      //行末尾
#define LeftCol 28      //列起始
#define RightCol 108    //列末尾
#define MSG_LEN 1024

extern int conn_fd;
extern int ActSm;
extern char *RegisteMenu[3];
extern char user_name[30]; 


int login_menu();              //登录界面主函数
void Initial(void);            //登录菜单启动函数
void DrawMain(void);           //画登录菜单                  
int  SelectmainMenu(void);            
void SelectMainMenu(void);     
void QuitProg(void);
void Wind(WINDOW *, int, int, int, int);
void Process(void);
void my_err(const char * err_string, int line);              //自己写的错误提示函数
void registe();                //注册
int login();                   //登录
void forget_password();        //找回密码
void function();               
void function_menu();          //打印功能菜单
void SelectfunctionMenu();     
void SelectfunctionMenu_row();
void SelectfunctionMenu_col();
void log_out();                //注销登录

#endif
