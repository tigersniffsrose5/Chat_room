#include "client.h"

void log_out()
{
    cJSON *root = cJSON_CreateObject();
    cJSON *item = cJSON_CreateNumber(3);
    cJSON_AddItemToObject(root ,"type",item);
    item = cJSON_CreateString(user_name);
    cJSON_AddItemToObject(root , "name" ,item);
    char *out = cJSON_Print(root);

    if ( send(conn_fd, out, MSG_LEN, 0) < 0 ) {
        my_err("send", __LINE__);
    }

    cJSON_Delete(root);
    free(out);

}
