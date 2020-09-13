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
#include "Common/libb64/include/b64/cdecode.h"
#include "Common/libb64/include/b64/cencode.h"
#include <mysql/mysql.h>
#include <sys/epoll.h>
#pragma comment(lib, "libmysql.lib") 

#define PORT 1212
#define MSG_LEN 1024

extern int conn_fd, sock_fd;
extern MYSQL mysql;

void my_err(const char * err_string, int line);
void mysql_init_t();
#endif
