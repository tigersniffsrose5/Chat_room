#include "client.h"

int conn_fd;
int ActSm = 0;
int my_mutex;
char *RegisteMenu[3] = { "*****请输入昵称*****", "*****请输入密码*****", "****按任意键继续****" };
char user_name[30];    


