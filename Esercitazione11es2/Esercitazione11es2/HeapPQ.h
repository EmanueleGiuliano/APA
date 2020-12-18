//
//  HeapPQ.h
//  Esercitazione11es2
//
//  Created by apple on 16/01/17.
//  Copyright © 2017 emag. All rights reserved.
//

#ifndef HeapPQ_h
#define HeapPQ_h
/*
 |...............................................|
 |  ADT di prima classe PQ con heap              |
 |...............................................|
 */
#include <stdio.h>
#include "Heap.h"
typedef struct pq *PQ;
PQ PQinit(int dim);
int PQempty(PQ x);
void PQinsert(Item x, PQ q);
void PQextract(PQ q, Item *val);
void PQshowFirst(PQ q);
void PQget(PQ q,Item *x);//riempie con un item void in caso non ci siano elementi in coda
void PQdisplay(PQ q);
void PQchange(Item x, PQ q, Key newPrio);
void PQdeleteFirst(PQ q);
void PQfree(PQ q);
void PQreadF(FILE *fp, PQ q);
void PQprintF(FILE *fp, PQ q);
#endif /* HeapPQ_h */
