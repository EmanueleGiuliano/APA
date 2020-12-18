//
//  Stack.h
//  RaccoltaADTIClasse
//
//  Created by apple on 30/12/16.
//  Copyright © 2016 emag. All rights reserved.
//
/*
 |...............................................|
 |  ADT di prima classe pila                     |
 |...............................................|
 */
#include "Item.h"
#include "List.h"
#ifndef Stack_h
#define Stack_h
typedef struct stack *Stack;
Stack STACKinit();
int  STACKempty(Stack x);
void STACKpush(Item x, Stack q);
void STACKpop(Stack q, Item *val);
Item STACKget(Stack q);//ritorna un riferimento all item nella coda ma non una nuova istanza
void STACKdisplay(Stack q);
void STACKsetItem(Key oldKey, Key newKey,Stack q);//cambia la chiave di un item di un determinato nodo
void STACKdelete(Item x, Stack q);
void STACKfree(Stack q);
void STACKreadF(FILE *fp, Stack q);
void STACKprintF(FILE *fp, Stack q);

#endif /* Stack_h */
