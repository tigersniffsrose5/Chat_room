#ifndef SERVER_H
#define SERVER_H

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
#include <mysql/mysql.h>
#include <sys/epoll.h>
#pragma comment(lib, "libmysql.lib") 

#define PORT 1212
#define MSG_LEN 1024

extern int conn_fd, sock_fd;
extern MYSQL *mysql;

typedef struct {
    int fd;
    char json[MSG_LEN];
}pack;


void my_err(const char * err_string, int line);
void mysql_init_t();
void Thread(void *arg);                                                            //服务端工作线程
int Account_Perst_IsUserName(const char *name);                                    //数据库检查是否重名 
void Account_Perst_AddUser(const char *name, int sex, const char *password);       //数据库添加新用户
void registe(pack *recv);                                                          //注册
void login(pack *recv);                                                            //登录
int Account_Perst_MatchUserAndPassword(int uid , const char * password);           //检查密码对错

#endif
