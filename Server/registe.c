#include "server.h"

void registe(pack *recv)
{
    char name[30], password[30];
    int sex, uid;
    cJSON *root, *item;

    root = cJSON_Parse(recv->json);
    item = cJSON_GetObjectItem(root , "name");
    strcpy(name,item->valuestring);
    item = cJSON_GetObjectItem(root ,"sex");
    sex = item->valueint;
    item = cJSON_GetObjectItem(root , "password");
    strcpy(password , item->valuestring);
    cJSON_Delete(root);

    root = cJSON_CreateObject();
    uid = Account_Perst_IsUserName(name); 

    if ( uid ) {
        
        item = cJSON_CreateBool(0);
        cJSON_AddItemToObject(root , "res" , item);
        char *out = cJSON_Print(root);
        
        if ( send(recv->fd , out, MSG_LEN, 0) < 0 ) {
            my_err("send", __LINE__);
        }
        
        cJSON_Delete(root);
        free(out);
        
        return;

    }

    Account_Perst_AddUser(name, sex, password);

    item = cJSON_CreateBool(1);
    cJSON_AddItemToObject(root, "res", item);
    item = cJSON_CreateNumber(uid);
    cJSON_AddItemToObject(root, "uid", item);
    char *out = cJSON_Print(root);

    if( send(recv->fd , out, MSG_LEN, 0) < 0){
        my_err("send", __LINE__);
    }

    cJSON_Delete(root);
    free(out);

}


int Account_Perst_IsUserName(const char *name)
{    
    char SQL[100];
    MYSQL_RES *res;
    MYSQL_ROW row;
    int rtn = 0;
    
    sprintf(SQL,"SELECT uid FROM user_info  WHERE name = '%s'",name);
    
    if( mysql_real_query(mysql , SQL , strlen(SQL)) ){

        printf("mysql_real_query select failure!\n"); 
        exit(0);  
    
    }

    res = mysql_store_result(mysql);
    row = mysql_fetch_row(res);
    
    if ( row ) {
    
        rtn = atoi(row[0]);
    
    }

    mysql_free_result(res);
    
    return rtn;

}


void Account_Perst_AddUser(const char *name, int sex, const char *password)
{
    char SQL[100];
    
    sprintf(SQL,"INSERT INTO user_info VALUES (NULL, '%s', '%d', md5('%s'))", name, sex, password);
    
    if( mysql_real_query(mysql , SQL , strlen(SQL)) ) {
        
        printf("mysql_real_query insert failure!\n");
        exit(0);
    
    }

}
