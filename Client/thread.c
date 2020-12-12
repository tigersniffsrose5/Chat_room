#include "client.h"

void Thread()
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
        item = cJSON_GetObjectItem(root, "type");
        
        switch ( item->valueint ) {
            case 0:
                my_mutex = 1;
                cJSON_Delete(root);
                return;
            case 1:
                add(&friend_request, message);
                if ( bSubOpen == 1 ) {
                    usleep(1000);
                    mvprintw(x, 15+LeftCol, "收到新的好友申请信息");
                    __sync_fetch_and_add(&x, 1);
                    refresh();
                }
                break;
            case 2:
                friendlistrecv(message);
                break;
            case 3:
                friendchatrecv(message);
                break;
            case 7:
                friend_recvfile(message);
                break;
        }

    }
}
