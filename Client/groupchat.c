#include "client.h"

void groupchat(const char *group_name)
{
    int key, n;
    char s[100];
    char s1[100];
    char str[2][15] = {"确认发送", "退出群聊"};
    time_t timep;
    cJSON *root;
    cJSON *item;
    Message_box *head = group_chat;

    memset(groupchat_name, 0, sizeof(groupchat_name));
    strcpy(groupchat_name, group_name);

    groupchat_menu(group_name);

    bSubOpen = 0;                  //功能主界面标志位
    bSubOpen_group = 1;

    while ( head != NULL ) {
        
        if ( strcmp(head->recv_name, group_name) == 0 ) {
            
            groupchatrecv(head->message);
            head = head->next;
            delet(&group_chat, group_name);

        }

        else {

            head = head->next;
        
        }

    }

    while ( 1 ) {

        echo();
        curs_set(1);   
        keypad(stdscr, TRUE);

        move(31, 43);
        bzero(s, sizeof(s));
        scanw("%s", s);
        time(&timep);
        
        noecho();
        curs_set(0);

        n = 0;
        while (1) {

            key = getch();

            if ( key == KEY_LEFT || key == KEY_RIGHT ) {

                mvaddstr(33, 68+n*14, str[n]);

                if ( key == KEY_LEFT ) {
                    n = n == 0 ? 1 : 0;
                }

                else {
                    n = n == 1 ? 0 : 1;
                }

                attron(A_REVERSE);
                mvaddstr(33, 68+n*14, str[n]);
                attroff(A_REVERSE);

            }

            else if ( key == ENTER ) {

                if ( n == 0 ) {
                
                   if ( group_x == 30 ) {
                        clear();
                        groupchat_menu(group_name);
                    }

                    mvaddstr(group_x, 27+LeftCol, ctime(&timep));
                    mvprintw(group_x, 92, "|");
                    __sync_fetch_and_add(&group_x, 1);
                    bzero(s1, sizeof(s1));
                    sprintf(s1, "%s:%s", user_name, s);
                    mvaddstr(group_x, 92-Strlen(s1), s1);
                    __sync_fetch_and_add(&group_x, 1);
                    
                    root = cJSON_CreateObject();
                    item = cJSON_CreateNumber(11);
                    cJSON_AddItemToObject(root, "type", item);
                    item = cJSON_CreateString(user_name);
                    cJSON_AddItemToObject(root,"user_name",item);
                    item = cJSON_CreateString(group_name);
                    cJSON_AddItemToObject(root,"friend_name",item);             
                    item = cJSON_CreateString(ctime(&timep));
                    cJSON_AddItemToObject(root,"time",item);
                    item = cJSON_CreateString(s1);
                    cJSON_AddItemToObject(root,"group_chat_message",item);
                    char *out = cJSON_Print(root);

                    if ( send(conn_fd, out, MSG_LEN, 0) < 0 ) {
                        myerr("send", __LINE__);
                    }

                    cJSON_Delete(root);
                    free(out);                

                    move(31, 43);
                    clrtoeol();
                    mvprintw(31, 92, "|");
 
                }

                    break;

            }

        }

        if ( n == 1 )
            break;

    }

    bSubOpen_group = 0;
}

void groupchatrecv(const char *message)
{
    char name1[30], name2[30], Time[30], chat_message[100];
    cJSON *root, *item;

    root = cJSON_Parse(message);
    item = cJSON_GetObjectItem(root, "user_name");
    strcpy(name1,item->valuestring);
    item = cJSON_GetObjectItem(root, "friend_name");
    strcpy(name2,item->valuestring);
    item = cJSON_GetObjectItem(root, "time");
    strcpy(Time,item->valuestring);
    item = cJSON_GetObjectItem(root, "group_chat_message");
    strcpy(chat_message,item->valuestring);
    cJSON_Delete(root);

    if ( bSubOpen == 1 ) {
        
        mvprintw(x, 15+LeftCol, "收到新的群聊信息");
        __sync_fetch_and_add(&x, 1);
        refresh();
        add(&group_chat, message);
    
    }

    else if ( bSubOpen_group == 1 && strcmp(groupchat_name, name2) == 0 ) {
        
        if ( group_x == 30 ) {
            clear();
            groupchat_menu(name2);
        }

        mvaddstr(group_x, 27+LeftCol, Time);
        mvprintw(group_x, 92, "|");
        __sync_fetch_and_add(&group_x, 1);
        mvaddstr(group_x, 15+LeftCol, chat_message);
        __sync_fetch_and_add(&group_x, 1);
        move(31, 43);
        refresh();
            
    }

    else {

        add(&group_chat, message);

    }

}

void groupchat_menu(const char *group_name)
{
    char strArr[4][51];
    char str[2][15] = {"确认发送", "退出群聊"};

    bSubOpen = 0;                  //功能主界面标志位
    bSubOpen_group = 1;

    clear();
    Wind(stdscr, 3, 42, 34, 92);

    strcpy(strArr[0], "*************************************************");
    strcpy(strArr[1], "*                   chat in                     *");
    sprintf(strArr[2], "*                     %s                       *", group_name);
    strcpy(strArr[3], "*************************************************");

    mvaddstr(4, 15+LeftCol, strArr[0]);
    mvaddstr(5, 15+LeftCol, strArr[1]);
    mvaddstr(6, 15+LeftCol, strArr[2]);
    mvaddstr(7, 15+LeftCol, strArr[3]);

    group_x = 8;

    mvaddstr(30, 15+LeftCol, strArr[3]);
    attron(A_REVERSE);
    mvaddstr(33, 68, str[0]);
    attroff(A_REVERSE);
    mvaddstr(33, 82, str[1]);

}
