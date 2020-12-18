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
int  HEAPsize(Heap h);
int  HEAPswapEl(Heap h,int pos1, int pos2);//attenzione, con questo comando si perde la struttura di heap(returna 0 se non e riuscito a swappare)
void HEAPgetEl(Heap h, int pos, Item *x);
void HEAPdeleteLastEl(Heap h);
void HEAPfree(Heap h);
int  HEAPfindPos(Heap h,Key kx);//restituisce la posizione di un elemento con data chiave all interno dell heap -1 se non presente
//NB per eliminare un elemento in particolare usi la find pos la swap el e la delete last, poi riapplichi heapbuild e sei a posto
void HEAPsetItemKey(Heap h,int pos,Key k);//cambia la chiave di un item preservando la struttura di heap
#endif /* Heap_h */
