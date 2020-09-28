#include "server.h"

void login(pack *recv)
{
    char name[30], password[30];
    int uid;
    cJSON *root, *item;

    root = cJSON_Parse(recv->json);
    item = cJSON_GetObjectItem(root , "name");
    strcpy(name,item->valuestring);
    item = cJSON_GetObjectItem(root , "password");
    strcpy(password , item->valuestring);
    cJSON_Delete(root);

    root = cJSON_CreateObject();
    uid = Account_Perst_IsUserName(name); 

    if ( uid == 0 ) {
        
        item = cJSON_CreateNumber(0);
        cJSON_AddItemToObject(root , "res" , item);
        char *out = cJSON_Print(root);
        
        if( send(recv->fd , out, MSG_LEN, 0) < 0){
            myerr("send", __LINE__);
        }
        
        cJSON_Delete(root);
        free(out);
        
        return;

    }
    
    if ( Account_Perst_MatchUserAndPassword(name ,password) == 0 ) {
 
        item = cJSON_CreateNumber(1);
        cJSON_AddItemToObject(root , "res" , item);
        char *out = cJSON_Print(root);
        
        if( send(recv->fd , out, MSG_LEN, 0) < 0){
            myerr("send", __LINE__);
        }
        
        cJSON_Delete(root);
        free(out);

        return;

    }

    if ( search(head, name) ) {
        
        item = cJSON_CreateNumber(2);
        cJSON_AddItemToObject(root , "res" , item);
        char *out = cJSON_Print(root);

        if( send(recv->fd , out, MSG_LEN, 0) < 0){
            myerr("send", __LINE__);
        }

        cJSON_Delete(root);
        free(out);

        return;

    }

    add(&head, recv->fd, name);

    item = cJSON_CreateNumber(3);
    cJSON_AddItemToObject(root , "res" , item);
    char *out = cJSON_Print(root);

    if( send(recv->fd , out, MSG_LEN, 0) < 0){
        myerr("send", __LINE__);
    }

    cJSON_Delete(root);
    free(out);

}

int Account_Perst_MatchUserAndPassword(const char *name , const char *password)
{
    char SQL[100];
    MYSQL_RES * res;
    MYSQL_ROW row;
    int rtn;

    sprintf(SQL, "SELECT * FROM user_info WHERE (name = '%s' AND password = md5('%s'))", name, password);

    if(mysql_real_query(mysql , SQL ,strlen(SQL))){
        printf("mysql_real_query select failure!\n"); 
        exit(0);
    }

    res = mysql_store_result(mysql);
    row = mysql_fetch_row(res);
    
    if ( row ) {
        
        rtn = 1;
    }
    
    else {

        rtn = 0;
    } 

    mysql_free_result(res);
    return rtn;

}
