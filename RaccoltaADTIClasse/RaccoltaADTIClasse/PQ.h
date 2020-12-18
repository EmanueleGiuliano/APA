//
//  PQ.h
//  RaccoltaADTIClasse
//
//  Created by apple on 28/12/16.
//  Copyright © 2016 emag. All rights reserved.
//
/*
 |...............................................|
 |  ADT di prima classe coda a priorità          |
 |...............................................|
 */
#include <stdlib.h>
#ifndef PQ_h
#define PQ_h
#include "Item.h"
#include "List.h" 
typedef struct pq *PQ;
PQ PQinit();
int PQempty(PQ x);
void PQinsert(Item x, PQ q);
void PQextractMax(PQ q, Item *val);
void PQshowMax(PQ q);
Item PQgetMax(PQ q);//ritorna un riferimento all item nella coda ma non una nuova istanza
void PQdisplay(PQ q);
void PQchange(Item x, PQ q);
void PQdelete(Item x, PQ q);
void PQfree(PQ q);
void PQreadF(FILE *fp, PQ q);
void PQprintF(FILE *fp, PQ q);
#endif /* PQ_h */