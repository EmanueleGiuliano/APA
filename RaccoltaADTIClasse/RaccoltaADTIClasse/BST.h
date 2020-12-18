//
//  BST.h
//  RaccoltaADTIClasse
//
//  Created by apple on 04/01/17.
//  Copyright © 2017 emag. All rights reserved.
//

#ifndef BST_h
#define BST_h
/*
 |...............................................|
 |  ADT di prima classe albero binario di ricerca|
 |include anche Interval BST e Order-StatisticBST|
 |...............................................|
 */
#include "Item.h"
typedef struct  binarysearchtree *BST;
BST BSTinit();
int BSTcount(BST t);
void BSTdisplay(BST t);
int BSTempty(BST t);
void BSTmin(BST t, Item *x);
void BSTmax(BST t, Item *x);
void BSTinsert_leaf(BST t,Item x);
void BSTinsert_root(BST t,Item x);
void BSTsearch(BST t,Key kx,Item *x);
int BSTdelete(BST t,Key kx);
void BSTselect(BST t,int i,Item *x);//restituisce l item con la k esima chiave piu piccola
void BSTsortinorder(BST t,Item v[],int dimVett);
void BSTsortpreorder(BST t,Item v[],int dimVett);
void BSTsortpostorder(BST t,Item v[],int dimVett);
void BSTsucc(BST t,Key kx, Item *x);
void BSTpred(BST t,Key kx, Item *x);
void BSTreadF(FILE *fp,BST *t);//legge un file e costruisce un bst
void BSTprintF(FILE *fp,BST t);//stampa il bst con struttura ad albero
//per IBST cambiare la search con item al posto che con chiave(gli item sono intervalli e non han chiave)
#endif /* BST_h */
