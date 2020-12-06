#include "server.h"

void Thread(void *arg)
{
    pack *p = (pack *)arg;
    cJSON *root, *item;
    int choice;

    root = cJSON_Parse(p->json);
    item = cJSON_GetObjectItem(root, "type");
    choice =  item->valueint;
    cJSON_Delete(root);

    void (* work[])(pack *) = { registe, login, forgetpassword, logout, addfriend, friendlist };
    
    if ( choice >= 0 && choice < 15 ) {
        work[choice](p);
    }

}
