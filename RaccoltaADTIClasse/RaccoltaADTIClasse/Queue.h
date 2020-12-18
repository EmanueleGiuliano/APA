//
//  Queue.h
//  RaccoltaADTIClasse
//
//  Created by apple on 30/12/16.
//  Copyright © 2016 emag. All rights reserved.
//
/*
 |...............................................|
 |  ADT di prima classe coda                     |
 |...............................................|
 */
#include "Item.h"
#include "List.h"
#ifndef Queue_h
#define Queue_h
typedef struct queue *Queue;
Queue QUEUEinit();
int  QUEUEempty(Queue x);
void QUEUEenqueue(Item x, Queue q);
void QUEUEdequeue(Queue q, Item *val);
Item QUEUEget(Queue q);//ritorna un riferimento all item nella coda ma non una nuova istanza
void QUEUEdisplay(Queue q);
void QUEUEsetItem(Key oldKey, Key newKey,Queue q);//cambia la chiave di un item di un determinato nodo
void QUEUEdelete(Item x, Queue q);
void QUEUEfree(Queue q);
void QUEUEreadF(FILE *fp, Queue q);
void QUEUEprintF(FILE *fp, Queue q);

#endif /* Queue_h */
