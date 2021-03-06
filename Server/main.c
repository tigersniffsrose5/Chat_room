#include "server.h"

int main()
{
    int optval, epfd, nfds, i, ret, recv_len, flag;
    socklen_t len;
    struct sockaddr_in cli_addr, serv_addr;
    struct epoll_event ev, events[1000];
    char buf[MSG_LEN];
//    pthread_t thid;
    pack *p;

    mysql_init_t();

    epfd = epoll_create(10000);
    sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    
    if ( sock_fd < 0 ) {
        myerr("socket", __LINE__);
    }

    optval = 1;

    if ( setsockopt(sock_fd, SOL_SOCKET, SO_REUSEADDR, (void *)&optval, sizeof(int)) < 0 ) {  //设置端口释放后立即就可以被再次使用
        myerr("setsockopt", __LINE__);
    }

    ev.data.fd = sock_fd;
    ev.events = EPOLLIN;
    epoll_ctl(epfd, EPOLL_CTL_ADD, sock_fd, &ev);
    
    memset(&serv_addr, 0, sizeof(struct sockaddr_in));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    
    if ( bind(sock_fd, (struct sockaddr *)&serv_addr, sizeof(struct sockaddr_in)) < 0 ) {
        myerr("bind", __LINE__);
    }

    if ( listen(sock_fd, 20) < 0 ) {
        myerr("listen", __LINE__);
    }

    len = sizeof(struct sockaddr_in);
    
    while ( 1 ) {

        nfds = epoll_wait(epfd, events, 10000, -1);
        
        for ( i = 0; i < nfds; i++ ) {
            
            if ( events[i].data.fd == sock_fd ) {
                
                conn_fd = accept(sock_fd, (struct sockaddr *)&cli_addr, &len);
                printf("accept a new client\n");
                ev.data.fd = conn_fd;
                ev.events = EPOLLIN;
                epoll_ctl(epfd, EPOLL_CTL_ADD, conn_fd, &ev);

            }

            else if ( events[i].events & EPOLLIN ) {             //文件描述符可读（包括fd关闭）
                
                flag = 1;
                bzero(&buf, sizeof(buf));
                recv_len = 0;

                while ( recv_len < MSG_LEN ) {
              
                    ret = 0;
                    ret = recv(events[i].data.fd,buf+recv_len,MSG_LEN-recv_len, 0);

                    if ( ret < 0 ) {
                        
                        close(events[i].data.fd);
                        myerr("recv", __LINE__);
                        break;

                    }

                    else if( ret == 0 ) {

                        flag = 0;
                        delet1(&node_t, events[i].data.fd);
                        printf("客户端已关闭\n");
                        ev.data.fd = events[i].data.fd;
                        epoll_ctl(epfd, EPOLL_CTL_DEL, events[i].data.fd, &ev);
                        close(events[i].data.fd);
                        break;
                        
                    }

                    recv_len += ret;

                }
                    
                if ( flag == 0 ) {
                    continue;
                }

                p = (pack *)malloc(sizeof(pack));
                p->fd = events[i].data.fd;
                memcpy(p->json, &buf, sizeof(buf));


                Thread(p);
//                if ( pthread_create(&thid, NULL, Thread, (void *)p) != 0 ) { 
//                    myerr("pthread_create", __LINE__); 
//                } 
//
//                pthread_join(thid, NULL);

            }
        }
    }

    mysql_close(mysql);

    return 0;
}
