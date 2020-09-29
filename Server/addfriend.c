#include "server.h"

void addfriend(pack *recv)
{
    int flag, fd, ans;
    char name1[30], name2[30];
    cJSON *root, *item;

    root = cJSON_Parse(recv->json);
    item = cJSON_GetObjectItem(root , "user_name");
    strcpy(name1,item->valuestring);
    item = cJSON_GetObjectItem(root ,"friend_name");
    strcpy(name2,item->valuestring);
    item = cJSON_GetObjectItem(root , "flag");
    flag = item->valueint;

    if ( flag == 1 ) {

        cJSON_Delete(root);
        root = cJSON_CreateObject();
        item = cJSON_CreateNumber(1);
        cJSON_AddItemToObject(root , "type" , item);

        if ( Account_Perst_IsUserName(name2) == 0 ) {
            item = cJSON_CreateNumber(1);
            cJSON_AddItemToObject(root , "res" , item);
            char *out = cJSON_Print(root);

            if( send(recv->fd , out, MSG_LEN, 0) < 0 ) {
                myerr("send", __LINE__);
            }

            cJSON_Delete(root);
            free(out);

            return;
        }

        if ( (Account_Perst_MatchUser1AndUser2(name1, name2) == 1) || (Account_Perst_MatchUser1AndUser2(name2, name1) == 1) ) {
            item = cJSON_CreateNumber(2);
            cJSON_AddItemToObject(root , "res" , item);
            char *out = cJSON_Print(root);

            if( send(recv->fd , out, MSG_LEN, 0) < 0 ) {
                myerr("send", __LINE__);
            }

            cJSON_Delete(root);
            free(out);

            return;
        } 

        fd = search(head, name2);
        
        item = cJSON_CreateNumber(3);
        cJSON_AddItemToObject(root , "res" , item);
        item = cJSON_CreateString(name1);
        cJSON_AddItemToObject(root , "name" , item);
        char *out = cJSON_Print(root);

        if ( fd != 0 ) {
            if( send(fd , out, MSG_LEN, 0) < 0 ) {
                myerr("send", __LINE__);
            }
        }

        else {
           add_downline_message(&head1, name2, out); 
        }

        cJSON_Delete(root);
        free(out);
    }
    
    else {
    
        item = cJSON_GetObjectItem(root , "ans");
        ans = item->valueint;
        
        cJSON_Delete(root);
        root = cJSON_CreateObject();
        item = cJSON_CreateNumber(1);
        cJSON_AddItemToObject(root , "type" , item);
        item = cJSON_CreateString(name1);
        cJSON_AddItemToObject(root , "name" , item);

        if ( ans == 1 ) {
            Account_Perst_AddFriend(name1, name2);
            item = cJSON_CreateNumber(4);
            cJSON_AddItemToObject(root , "res" , item);
        }

        else {
            item = cJSON_CreateNumber(5);
            cJSON_AddItemToObject(root , "res" , item);
        }

        char *out = cJSON_Print(root);

        fd = search(head, name2);
        if ( fd != 0 ) {
            if( send(fd , out, MSG_LEN, 0) < 0 ) {
                myerr("send", __LINE__);
            }
        }

        else {
            add_downline_message(&head1, name2, out); 
        }

        cJSON_Delete(root);
        free(out);

    }

}

int Account_Perst_MatchUser1AndUser2(const char *name1 , const char *name2)
{
    char SQL[100];
    MYSQL_RES * res;
    MYSQL_ROW row;
    int rtn;

    sprintf(SQL, "SELECT * FROM friend_relationship WHERE (user_name1 = '%s' AND user_name2 = '%s')", name1, name2);

    if( mysql_real_query(mysql , SQL ,strlen(SQL)) ) {
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

void Account_Perst_AddFriend(const char *name1, const char *name2)
{
    char SQL[100];

    sprintf(SQL,"INSERT INTO friend_relationship VALUES ('%s', '%s',)", name1, name2);

    if( mysql_real_query(mysql , SQL , strlen(SQL)) ) {

        printf("mysql_real_query insert failure!\n");
        exit(0);

    }

}
