#include "server.h"

void mysql_init_t()
{
    mysql = mysql_init(NULL); 
    
    printf("qsj");

    if ( !mysql_real_connect(mysql, "localhost", "root", "qsj122833", "Chat_room", 0, NULL, 0) ) {
        printf("mysql_real_connect failure!\n");
        exit(-1);
    }

    mysql_set_character_set(mysql, "utf8");
    printf("mysql connect success\n");

}
