//
//  Heap.h
//  RaccoltaADTIClasse
//
//  Created by apple on 09/01/17.
//  Copyright © 2017 emag. All rights reserved.
//

#ifndef Heap_h
#define Heap_h
#include "Item.h"
#include <stdio.h>
/*
 |...............................................|
 |  ADT di prima classe heap                     |
 |...............................................|
 */
//HEAP implementato come vettore

typedef struct heap *Heap;

Heap HEAPinit(int dim);
void HEAPfill(Heap h, Item x);
void HEAPsort(Heap h);
void HEAPdisplay(Heap h);
void HEAPbuild(Heap h);
void HEAPreadF(FILE *fp,Heap *h);//legge degli item e costruisce un heap
void HEAPprintF(FILE *fp,Heap h);//stampa l heap su file come un albero binario
#endif /* Heap_h */
