#include "client.h"

void grouplist()
{
    cJSON *root;
    cJSON *item;

    root = cJSON_CreateObject();
    item = cJSON_CreateNumber(10);
    cJSON_AddItemToObject(root, "type", item);
    item = cJSON_CreateString(user_name);
    cJSON_AddItemToObject(root,"user_name",item);
    char *out = cJSON_Print(root);

    if ( send(conn_fd, out, MSG_LEN, 0) < 0 ) {
        myerr("send", __LINE__);
    }

    cJSON_Delete(root);
    free(out);

}

void grouplistrecv(const char *message)
{
    int i;

    memset(group_list, 0, sizeof(group_list));

    cJSON *root = cJSON_Parse(message);
    cJSON *group_t = cJSON_GetObjectItem(root, "group");

    i = 0;
    if ( group_t != NULL ) {
        
        cJSON *Group_list = group_t->child;
        
        while ( Group_list != NULL ) {
        
            strcpy(group_list[i++], cJSON_GetObjectItem(Group_list , "group_name")->valuestring);

            Group_list = Group_list->next;

        }

    }

    mutex_t = 1;
}
