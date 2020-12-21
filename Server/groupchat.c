#include "server.h"

void group_chat(pack *recv)
{
    int fd;
    char name1[30], name2[30], Time[30], chat_message[100];
    cJSON *root, *item;

    root = cJSON_Parse(recv->json);
    item = cJSON_GetObjectItem(root, "user_name");
    strcpy(name1,item->valuestring);
    item = cJSON_GetObjectItem(root, "group_name");
    strcpy(name2,item->valuestring);
    item = cJSON_GetObjectItem(root, "time");
    strcpy(Time,item->valuestring);
    item = cJSON_GetObjectItem(root, "group_chat_message");
    strcpy(chat_message,item->valuestring);
    cJSON_Delete(root);


    fd = search(node_t, name2);

    root = cJSON_CreateObject();
    item = cJSON_CreateNumber(5);
    cJSON_AddItemToObject(root, "type", item);
    item = cJSON_CreateString(name2);
    cJSON_AddItemToObject(root,"user_name",item);
    item = cJSON_CreateString(name1);
    cJSON_AddItemToObject(root,"group_name",item);
    item = cJSON_CreateString(Time);
    cJSON_AddItemToObject(root,"time",item);
    item = cJSON_CreateString(chat_message);
    cJSON_AddItemToObject(root,"group_chat_message",item);
    char *out = cJSON_Print(root);


    if ( fd != 0 ) {
        if( send(fd , out, MSG_LEN, 0) < 0 ) {
            myerr("send", __LINE__);
        }
    }
//
//    else {
//        add_downline_message(&downline_message_t, name2, out); 
//    }
//
    cJSON_Delete(root);
    free(out);

}
