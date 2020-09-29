#include "server.h"

void logout(pack *recv)    
{
    char name[30];
    cJSON *root, *item;

    root = cJSON_Parse(recv->json);
    item = cJSON_GetObjectItem(root , "name");
    strcpy(name,item->valuestring);

    cJSON_Delete(root);
    
    delet(&head, name);

    root = cJSON_CreateObject();
    item = cJSON_CreateNumber(0);
    cJSON_AddItemToObject(root , "type" , item);
    char *out = cJSON_Print(root);

    if( send(recv->fd , out, MSG_LEN, 0) < 0 ) {
        myerr("send", __LINE__);
    }

    cJSON_Delete(root);
    free(out);

}
