//
//  List.h
//  RaccoltaADTIClasse
//
//  Created by apple on 28/12/16.
//  Copyright © 2016 emag. All rights reserved.
//

/*
 |...............................................|
 |  ADT di prima classe Lista concatenata doppia |
 |...............................................|
 |
 |NB: Le funzioni che usano il tipo link e che operano direttamente sui nodi vanno eliminate ed il tipo link
 |reso invisibile ai client in caso si utilizzi questo modulo in contemporanea con adt che abbiano bisogno a
 |loro volta di definire un tipo link-->Alternativa, chiamare in modo diverso i link degli altri adt
 */

#include "Item.h"
#include <stdlib.h>
#ifndef List_h
#define List_h

typedef struct node *Link,node_t;//definisce i tipi puntatore a nodo e nodo della lista

typedef struct list *List;

List LISTinit();
void LISTinsertTail(Item x,List l);//inserzione in coda
void LISTinsertHead(Item x,List l);//inserzione in testa
void LISTextract(Key kx, List l,Item *val);//estrae il primo item con una certa chiave
void LISTextractHead(List l,Item *val);//estrae in testa alla lista
void LISTextractTail(List l,Item *val);//estrae in coda alla lista
void LISTgetItem(Key kx, List l,Item *val);//restituisce il primo item con una certa chiave
void LISTdisplay(List l);
void LISTdeleteNode(Item x, List l);
void LISTdeleteNodeK(Key kx, List l);
void LISTshowNode(Key kx,List l);
void LISTreadF(FILE *fp,List l);//legge un file e carica la lista
void LISTprintF(FILE *fp,List l);//stampa una lista su file
void LISTsetItem(Key oldKey, Key newKey,List l);//cambia la chiave di un item di un determinato nodo
void LISTsort(List l);//ordina la lista con insertionSort
List LISTreverse(List l);//crea una lista invertita
int  LISTempty(List l);
Item LISTgetTail(List l);//returna un riferimento all item contenuto nel nodo della lista, non serve fare item init ma l item non sara proprietà del client
Item LISTgetHead(List l);
void LISTcpyHead(List l, Item *cpy);
Link LISTmoveNext(List l, Link x);
Link LISTmovePrev(List l, Link x);
Link LISTgetNodeHead(List l);
Item NODEgetItem(Link x);
Link NODEnewNode(Link next, Link prev);
void NODEfree(Link x);
void LISTfree(List l);
#endif /* List_h */
