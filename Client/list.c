#include "client.h"

void add(Message_box **Head, const char *message_t)
{

    cJSON *root = cJSON_Parse(message_t);
    cJSON *item = cJSON_GetObjectItem(root, "friend_name");
    
    Message_box *p = (Message_box *)malloc(sizeof(Message_box));
    Message_box *last = *Head;

    strcpy(p->recv_name, item->valuestring);
    strcpy(p->message, message_t);
    p->next = NULL;

    if ( last ) {
        while ( last->next ) {
            last = last->next;
        }
        last->next = p;
    }

    else {
        *Head = p;
    }
}

void delet(Message_box **Head, const char *name)
{
    Message_box *p = *Head, *q;

    for ( q = NULL; p; q = p, p = p->next ) {
        if ( strcmp(p->recv_name, name) == 0 ) {
            if ( q ) {
                q->next = p->next;
            }
            else {
                *Head = p->next;
            }
            free(p);
            break;
        }
    }
}   

//void delet1(Message_box **Head, int fd_t)
//{
//    Message_box *p = *Head, *q;
//
//    for ( q = NULL ; p ; q = p, p = p->next ) {
//        if ( p->fd == fd_t ) {
//            if ( q ) {
//                q->next = p->next;
//            }
//            else {
//                *Head = p->next;
//            }
//            free(p);
//            break;
//        }
//    }
//}
//
//int search(Message_box *Head, const char *message_t)
//{
//    Message_box *p = Head, *q;
//
//    for ( q = NULL; p; q = p, p = p->next ) {
//        if ( strcmp(p->messagee, message) == 0 ) {
//            return p->fd;
//        }
//    }
//
//    return 0;
//}
//
//
void fre(Message_box **Head)
{
    Message_box *p = *Head, *q;

    while ( p ) {
        q = p;
        p = p->next;
        free(q);
    }

    *Head = NULL;
}

void fre1(User **Head)
{
    User *p = *Head, *q;

    while ( p ) {
        q = p;
        p = p->next;
        free(q);
    }

    *Head = NULL;
}
