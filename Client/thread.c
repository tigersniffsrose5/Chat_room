#include "client.h"

void thread()
{
    int ret, recv_len;
    char message[MSG_LEN];
    cJSON *root;
    cJSON *item;
    while ( 1 ) {

        recv_len = 0;
        while ( recv_len < MSG_LEN ) {

            ret = 0;

            if ( (ret = recv(conn_fd, message+recv_len, MSG_LEN-recv_len, 0)) <= 0 ) {
                myerr("recv", __LINE__);
            }

            recv_len += ret;

        }
        root = cJSON_Parse(message);
        item = cJSON_GetObjectItem(root ,"type");

        switch ( item->valuestring[0] ) {
            case 0:
                my_mutex = 1;
                return;
            case 1:
                break;
        }

    }
}
