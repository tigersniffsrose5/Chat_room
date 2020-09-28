#include "server.h"

void add_downline_message(downline_message **Head, const char *nam, const char *buf)
{
    downline_message *p = (downline_message*)malloc(sizeof(downline_message));
    downline_message *last = *Head;

    strcpy(p->name, nam);
    strcpy(p->message, buf);
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

void delet_downline_message(downline_message **Head, const char *nam)
{
    downline_message *p = *Head, *q;

    for ( q = NULL ; p ; q = p, p = p->next ) {
        if ( strcmp(p->name, nam) == 0 ) {
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

