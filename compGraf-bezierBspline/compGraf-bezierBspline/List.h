//
//  List.h
//  compGraf-bezierBspline
//
//  Created by Marcelle Guine on 31/07/13.
//  Copyright (c) 2013 Marcelle Guine. All rights reserved.
//

#ifndef Curves_List_h
#define Curves_List_h

struct list
{
    float x;
    float y;
    struct list * next;
    struct list * prev;
};

struct list * listNew(float x, float y);
void listFree(struct list * list);
void listAdd(struct list * l, float x, float y);
int listCount(struct list * l);
struct list * listRemove(struct list * l);
struct list * listRemoveAt(struct list * l, int d);
struct list * listGet(struct list * l, int d);

#endif
