#include "server.h"

void creatgroup(pack *recv)
{
    char user_name[30], group_name[30];
    cJSON *root, *item;
    char SQL[100];
    MYSQL_RES * res;
    MYSQL_ROW row;

    root = cJSON_Parse(recv->json);
    item = cJSON_GetObjectItem(root, "user_name");
    strcpy(user_name,item->valuestring);
    item = cJSON_GetObjectItem(root, "group_name");
    strcpy(group_name,item->valuestring);

    sprintf(SQL, "SELECT * FROM group_info WHERE (group_name = '%s')", group_name);

    if( mysql_real_query(mysql , SQL ,strlen(SQL)) ) {
        printf("mysql_real_query select failure!\n"); 
        exit(0);
    }

    res = mysql_store_result(mysql);
    row = mysql_fetch_row(res);

    if ( row ) {
        return;
    }

    else {

        memset(SQL, 0, sizeof(SQL));
        sprintf(SQL,"INSERT INTO group_info VALUES ('%s', '%s')", group_name, user_name);

        if( mysql_real_query(mysql , SQL , strlen(SQL)) ) {

            printf("mysql_real_query insert failure!\n");
            exit(0);

        }

    }

}
