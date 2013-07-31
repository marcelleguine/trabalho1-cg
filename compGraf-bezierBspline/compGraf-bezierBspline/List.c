//
//  List.c
//  compGraf-bezierBspline
//
//  Created by Carolina Zamith e Marcelle Guine on 31/07/13.
//  Copyright (c) 2013 Carolina Zamith e Marcelle Guine. All rights reserved.
//

#include <stdlib.h>
#include "List.h"

struct list * listNew(float x, float y)
{
    struct list * l = (struct list *)malloc(sizeof(struct list));
    l->x = x;
    l->y = y;
    l->prev = 0;
    l->next = 0;
    return l;
}

void listFree(struct list * l)
{
    while (l)
    {
        struct list * tmp = l->next;
        free(l);
        l = tmp;
    }
}

void listAdd(struct list * l, float x, float y)
{
	struct list * n = 0;
    while (l->next)
        l = l->next;
    
	n = listNew(x, y);
    n->prev = l;
    l->next = n;
}

int listCount(struct list * l)
{
    int i = 0;
    while (l)
    {
        l = l->next;
        i++;
    }
    return i;
}

struct list * listRemove(struct list * l)
{
    struct list * n = l->next;
    struct list * p = l->prev;
    
    free(l);
    
    if (n)
        n->prev = p;
    if (p)
        p->next = n;
    
    return n;
}

struct list * listRemoveAt(struct list * l, int d)
{
    if (!d)
        return listRemove(l);
    
    listRemove(listGet(l, d));
    return l;
}

struct list * listGet(struct list * l, int d)
{
    while (l && d)
    {
        l = l->next;
        d--;
    }
    return l;
}