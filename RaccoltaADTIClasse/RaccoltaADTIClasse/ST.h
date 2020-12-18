//
//  ST.h
//  RaccoltaADTIClasse
//
//  Created by apple on 09/01/17.
//  Copyright © 2017 emag. All rights reserved.
//
#include "Item.h"
#include "List.h"
#ifndef ST_h
#define ST_h
/*
 |...............................................|
 |  ADT di prima classe tabella di simboli       |
 |  implementata come tabella ad accesso diretto |
 |...............................................|
 */
//NB chiavi duplicate memorizzate allo stesso indice con una lista
typedef struct symboltable *ST;
ST STinit(int maxN);
void STfree(ST st);
int STcount(ST st);
int STinsert(ST st, Item val);//inserisce e restituisce la posizione nella tabella 
void STsearch(ST st, Key k, List *cpy);//carica un item esterno/Lista/elemento generico con i valori di un elemento cercato della tabella se presente
void STdelete(ST st, Key k);
void STselect(ST st, int r, List *cpy);// seleziona un item con un certo rango
void STdisplay(ST st);
void STretrieve(ST st,int index, List *x);//utile per i grafi, dato l indice nella tabella copia l item nell item dato(solito motivo di ownership),(In questa particolare tabella a chiavi non univoche restituisce una lista di item ma non e utilizzabile in un grafo)
int STsearchIndex(ST st, Key k);//se trova l elemento nella tabella restituisce la sua posizione se no returna -1
#endif /* ST_h */
