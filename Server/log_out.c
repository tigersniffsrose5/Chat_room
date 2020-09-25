#include "server.h"

void log_out(pack *recv)    
{
    char name[30];
    cJSON *root, *item;

    root = cJSON_Parse(recv->json);
    item = cJSON_GetObjectItem(root , "name");
    strcpy(name,item->valuestring);

    cJSON_Delete(root);
    
    delet(&head, name);

}
