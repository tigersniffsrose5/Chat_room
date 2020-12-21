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
int friend_x;
int group_x;
char file_message[100];
char friendchat_name[30];
char groupchat_name[30];
Message_box *friend_request;
User *friend_list;
Message_box *friend_chat;
char group_list[20][20];
Message_box *group_chat;
