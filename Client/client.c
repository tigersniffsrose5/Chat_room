#include "client.h"

int conn_fd;
int ActSm = 0;
int my_mutex;
int mutex_t;
char *RegisteMenu[3] = { "*****请输入昵称*****", "*****请输入密码*****", "****按任意键继续****" };
char user_name[30];    
int bSubOpen;
int bSubOpen_friend;
int bSubOpen_group;
int x;
Message_box *friend_request;
User *friend_list;
Message_box *friend_chat;
Message_box *group_list;
Message_box *group_chat;
