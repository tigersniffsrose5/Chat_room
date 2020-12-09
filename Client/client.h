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

typedef struct message_box{
    char recv_name[30];
    char message[MSG_LEN];
    struct message_box *next;
}Message_box;

typedef struct user{
    char name[30];
    char sta[10];
    struct user *next;
}User;


extern int conn_fd;
extern int ActSm;
extern int my_mutex;                                //登录界面等待工作线程退出
extern int mutex_t;                                 //等待列表界面操作退出
extern char *RegisteMenu[3];
extern char user_name[30]; 
extern int bSubOpen;                                //判断是否在功能界面
extern int bSubOpen_friend;                         //判断是否在私聊界面
extern int bSubOpen_group;                          //判断是否在群聊界面
extern int x;                                       //功能界面提示信息打印行
extern int friend_x;                                //私聊界面信息打印行 
extern int group_x;                                 //群聊界面信息打印行
extern Message_box *friend_request;
extern User *friend_list;
extern Message_box *friend_chat;
extern Message_box *group_list;
extern Message_box *group_chat;


int loginmenu();               //登录界面主函数
void Initial(void);            //登录菜单启动函数
void DrawMain(void);           //画登录菜单                  
int  SelectmainMenu(void);            
void SelectMainMenu(void);     
void QuitProg(void);
void Wind(WINDOW *, int, int, int, int);
void Process(void);
void myerr(const char * err_string, int line);              //自己写的错误提示函数
void registe();                                             //注册
int login();                                                //登录
void forgetpassword();                                      //找回密码
void Thread();
void function();                                            
void functionmenu();                                        //打印功能菜单
void SelectfunctionMenu();                                 
void SelectfunctionMenurow();
void SelectfunctionMenucol();
void add(Message_box **Head, const char *message_t);        //单链表添加函数
void delet(Message_box **Head, const char *name);           //单链表删除函数
void fre(Message_box **Head);                               //单链表free函数
void fre1(User **Head);
void logout();                                              //注销登录
void addfriend();                                           //添加好友
void add_friend(const char *message);     
void dealapply();                                           //处理好友申请 
void choosefriend();                                        //选择好友
void friendlist();                                          //获取好友列表
void friendlistrecv(const char *message);                   
void friendfunction(const char *friend_name);               //好友功能界面 
void friendchat(const char *friend_name);                   //私聊
void friendchat_menu(const char *friend_name);              //私聊界面
int Strlen(const char *s);                                  //自己写的strlen，为了读汉字,linux下汉字占3字节，但是打印出来占两个字符
void friendchatrecv(const char *message);

#endif
