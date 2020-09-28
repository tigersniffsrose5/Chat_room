#include "client.h"

int main()
{
    pthread_t thid;
    struct sockaddr_in addr;
    
    conn_fd = socket(AF_INET, SOCK_STREAM, 0);

    if ( conn_fd < 0 ) 
        myerr("socket",__LINE__);
    
    memset(&addr, 0, sizeof(struct sockaddr_in));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    
    if ( connect(conn_fd, (struct sockaddr *)&addr, sizeof(struct sockaddr)) < 0 )
        myerr("connect", __LINE__);

    if ( loginmenu() == 0 ) {
        close(conn_fd);
        return 0;
    }

}


