#include "server.h"

int conn_fd, sock_fd;
MYSQL *mysql;
node *head;
downline_message *head1;
