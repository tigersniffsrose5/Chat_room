#include "server.h"

void group_chat(pack *recv)
{
    int fd;
    char name1[30], name2[30], Time[30], chat_message[100];
    char SQL[100];
    MYSQL_RES *res;
    MYSQL_ROW row;
    cJSON *root, *item;

    root = cJSON_Parse(recv->json);
    item = cJSON_GetObjectItem(root, "user_name");
    strcpy(name1,item->valuestring);
    
    printf("user_name:%s\n", name1);
    item = cJSON_GetObjectItem(root, "friend_name");
    strcpy(name2,item->valuestring);
    item = cJSON_GetObjectItem(root, "time");
    strcpy(Time,item->valuestring);
    item = cJSON_GetObjectItem(root, "group_chat_message");
    strcpy(chat_message,item->valuestring);
    cJSON_Delete(root);

    root = cJSON_CreateObject();
    item = cJSON_CreateNumber(5);
    cJSON_AddItemToObject(root, "type", item);
    item = cJSON_CreateString(name1);
    cJSON_AddItemToObject(root,"user_name",item);
    item = cJSON_CreateString(name2);
    cJSON_AddItemToObject(root,"friend_name",item);
    item = cJSON_CreateString(Time);
    cJSON_AddItemToObject(root,"time",item);
    item = cJSON_CreateString(chat_message);
    cJSON_AddItemToObject(root,"group_chat_message",item);
    char *out = cJSON_Print(root);

    sprintf(SQL,"SELECT user_name FROM group_info WHERE group_name = '%s'",name2);

    if( mysql_real_query(mysql , SQL , strlen(SQL)) ) {

        printf("mysql_real_query select failure!\n");
        exit(0);

    }

    res = mysql_store_result(mysql);

    while ( row = mysql_fetch_row(res) ) {

        if ( (strcmp(row[0], name1) == 0) )
            continue;

        fd = search(node_t, row[0]);

        printf("row[0]:%s\n", row[0]);

        if ( fd != 0 ) {
            if( send(fd , out, MSG_LEN, 0) < 0 ) {
                myerr("send", __LINE__);
            }
        }

        else {
            add_downline_message(&downline_message_t, row[0], out); 
        }

    }

    mysql_free_result(res);    
    cJSON_Delete(root);
    free(out);

}
