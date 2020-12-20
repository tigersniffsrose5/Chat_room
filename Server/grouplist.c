#include "server.h"

void grouplist(pack *recv)
{
    char name[30], SQL[100];
    cJSON *root, *item;
    MYSQL_RES *res;
    MYSQL_ROW row;
    
    root = cJSON_Parse(recv->json);
    item = cJSON_GetObjectItem(root, "user_name");
    strcpy(name,item->valuestring);
    cJSON_Delete(root);

    root = cJSON_CreateObject();
    cJSON *array_group = cJSON_CreateArray();
    item = cJSON_CreateNumber(4);
    cJSON_AddItemToObject(root, "type", item);


    sprintf(SQL,"SELECT group_name FROM group_info WHERE user_name = '%s'",name);

    if( mysql_real_query(mysql , SQL , strlen(SQL)) ) {

        printf("mysql_real_query select failure!\n");
        exit(0);

    }

    res = mysql_store_result(mysql);
    
    while ( row = mysql_fetch_row(res) ) {
        
        cJSON *obj_user = cJSON_CreateObject();

		item = cJSON_CreateString(row[0]);
		cJSON_AddItemToObject(obj_user,"group_name",item);

        cJSON_AddItemToArray(array_group,obj_user);
    }

    mysql_free_result(res);

    cJSON_AddItemToObject(root,"group",array_group);
    
    char *out = cJSON_Print(root);

        if( send(recv->fd, out, MSG_LEN, 0) < 0 ) {
        myerr("send", __LINE__);
    }

    cJSON_Delete(root);
    free(out);

}
