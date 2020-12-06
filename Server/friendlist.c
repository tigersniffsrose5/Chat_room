#include "server.h"

void friendlist(pack *recv)
{
    char name[30], SQL[100];
    cJSON *root, *item;
    MYSQL_RES *res;
    MYSQL_ROW row;
    char status[2][10] =  {"online", "downline"};
    
    root = cJSON_Parse(recv->json);
    item = cJSON_GetObjectItem(root, "user_name");
    strcpy(name,item->valuestring);
    cJSON_Delete(root);

    root = cJSON_CreateObject();
    cJSON *array_user = cJSON_CreateArray();
    item = cJSON_CreateNumber(2);
    cJSON_AddItemToObject(root, "type", item);


    sprintf(SQL,"SELECT user_name1 FROM friend_relationship WHERE user_name2 = '%s'",name);

    if( mysql_real_query(mysql , SQL , strlen(SQL)) ) {

        printf("mysql_real_query select failure!\n");
        exit(0);

    }

    res = mysql_store_result(mysql);
    
    while ( row = mysql_fetch_row(res) ) {
        
        cJSON *obj_user = cJSON_CreateObject();

		item = cJSON_CreateString(row[0]);
		cJSON_AddItemToObject(obj_user,"name",item);

        if ( search(node_t, row[0]) != 0 ) {
        
            item = cJSON_CreateString(status[0]);
            cJSON_AddItemToObject(obj_user,"sta",item);

        }

        else {

            item = cJSON_CreateString(status[1]);
            cJSON_AddItemToObject(obj_user,"sta",item);

        }

        cJSON_AddItemToArray(array_user,obj_user);
    }

    mysql_free_result(res);

    sprintf(SQL,"SELECT user_name2 FROM friend_relationship WHERE user_name1 = '%s'",name);

    if( mysql_real_query(mysql , SQL , strlen(SQL)) ) {

        printf("mysql_real_query select failure!\n");
        exit(0);

    }

    res = mysql_store_result(mysql);
    
    while ( row = mysql_fetch_row(res) ) {

        cJSON *obj_user = cJSON_CreateObject();

		item = cJSON_CreateString(row[0]);
		cJSON_AddItemToObject(obj_user,"name",item);

        if ( search(node_t, row[0]) != 0 ) {
        
            item = cJSON_CreateString(status[0]);
            cJSON_AddItemToObject(obj_user,"sta",item);

        }

        else {

            item = cJSON_CreateString(status[1]);
            cJSON_AddItemToObject(obj_user,"sta",item);

        }
    
        cJSON_AddItemToArray(array_user,obj_user);
    }

    mysql_free_result(res);

    cJSON_AddItemToObject(root,"user",array_user);
    
    char *out = cJSON_Print(root);

        if( send(recv->fd, out, MSG_LEN, 0) < 0 ) {
        myerr("send", __LINE__);
    }

    cJSON_Delete(root);
    free(out);
}
