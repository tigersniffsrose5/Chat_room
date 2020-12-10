#include "server.h"

void friend_sendfile(pack *recv)
{
    int fd;
    cJSON *root, *item;

    root = cJSON_Parse(recv->json);
    item = cJSON_GetObjectItem(root, "friend_name");

    fd = search(node_t, item->valuestring);

    if ( fd != 0 ) {
       
        if( send(fd , recv->json, MSG_LEN, 0) < 0 ) {
            myerr("send", __LINE__);
        }

    }

    cJSON_Delete(root);

}
