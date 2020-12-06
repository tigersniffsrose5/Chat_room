#include "client.h"

void friendlist()
{
    cJSON *root;
    cJSON *item;

    root = cJSON_CreateObject();
    item = cJSON_CreateNumber(5);
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

void friendlistrecv(const char *message)
{
    
    User *p, *last;

    while ( friend_list ) {
        p = friend_list;
        friend_list = friend_list->next;
        free(p);
    }

    friend_list = NULL;

    cJSON *root = cJSON_Parse(message);
    cJSON *user_t = cJSON_GetObjectItem(root, "user");

    if ( user_t != NULL ) {
        
        cJSON *user_list = user_t->child;
        
        while ( user_list != NULL ) {
        
            p = (User *)malloc(sizeof(User));
            last = friend_list;

            strcpy(p->name, cJSON_GetObjectItem(user_list , "name")->valuestring);
            strcpy(p->sta, cJSON_GetObjectItem(user_list , "sta")->valuestring);
            p->next = NULL;

            if ( last ) {
                while ( last->next ) {
                    last = last->next;
                }
                last->next = p;
            }

            else {
                friend_list = p;
            }
            
            user_list = user_list->next;

        }

    }

    choosefriend();
}
