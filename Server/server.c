#include "server.h"

int conn_fd, sock_fd;
MYSQL *mysql;
node *node_t;
downline_message *downline_message_t;
