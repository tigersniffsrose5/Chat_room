#include "server.h"

void forgetpassword(pack *recv)
{
    char name[30], password[30];
    int code, uid, flag;
    cJSON *root, *item;

    root = cJSON_Parse(recv->json);
    item = cJSON_GetObjectItem(root, "name");
    strcpy(name,item->valuestring);
    item = cJSON_GetObjectItem(root, "code");
    code = item->valueint;
    item = cJSON_GetObjectItem(root, "flag");
    flag = item->valueint;

    if ( flag == 4 ) {
        
        item = cJSON_GetObjectItem(root, "password");
        strcpy(password,item->valuestring);    
        
        cJSON_Delete(root);

        Account_Perst_ChangePassword(name, password);
        
        return;
    }

    cJSON_Delete(root);
    
    root = cJSON_CreateObject();
    uid = Account_Perst_IsUserName(name); 

    if ( uid == 0 ) {

        item = cJSON_CreateNumber(1);
        cJSON_AddItemToObject(root, "res", item);

        char *out = cJSON_Print(root);

        if( send(recv->fd , out, MSG_LEN, 0) < 0 ) {
            myerr("send", __LINE__);
        }

        cJSON_Delete(root);
        free(out);

        return;

    }

    if ( uid != code ) {

        item = cJSON_CreateNumber(2);
        cJSON_AddItemToObject(root, "res", item);

        char *out = cJSON_Print(root);

        if( send(recv->fd , out, MSG_LEN, 0) < 0 ) {
            myerr("send", __LINE__);
        }

        cJSON_Delete(root);
        free(out);

        return;

    }

    item = cJSON_CreateNumber(3);
    cJSON_AddItemToObject(root, "res", item);
    char *out = cJSON_Print(root);

    if( send(recv->fd , out, MSG_LEN, 0) < 0 ) {
        myerr("send", __LINE__);
    }

    cJSON_Delete(root);
    free(out);
    
}

void Account_Perst_ChangePassword(const char *name, const char *password)
{
    char SQL[100];

    sprintf(SQL,"UPDATE user_info SET password = md5('%s') WHERE name = '%s'", password, name);

    if( mysql_real_query(mysql , SQL , strlen(SQL)) ) {

        printf("mysql_real_query update failure!\n");
        exit(0);

    }

}

int recv1(int fd, char *buf, int len, int flags)
{
    return recv(fd, buf, len, flags);
}
