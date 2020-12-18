//
//  Tree.h
//  RaccoltaADTIClasse
//
//  Created by apple on 31/12/16.
//  Copyright © 2016 emag. All rights reserved.
//
/*
 |...............................................|
 |  ADT di prima classe albero                   |
 |...............................................|
 */
#include "Item.h"
#include "ST.h"
#ifndef Tree_h
#define Tree_h

typedef struct  tree *Tree;

Tree TREEinit();
void TREEinsert(Tree t,Item x);
int  TREEdistNodes(Tree t,Key k1, Key k2);
void TREEgetItem(Tree t, Key kx, Item *x);//genera un nuovo item
int  TREEcontaCompleti(Tree t, int L1, int L2);
int  TREEcountNodes(Tree t);
int  TREEheight(Tree t);
void TREEsortinorder(Tree t, Item v[],int dimVett);
void TREEsortpreorder(Tree t, Item v[],int dimVett);
void TREEsortpostorder(Tree t, Item v[],int dimVett);
Tree* TREEgenFromArray(int treeVett[],int dimTreeVett,ST st,int numMaxAlberi);//genera un vettore di alberi da un array di indici combinato con una symboltable
void TREEdisplay(Tree t);
void TREEfree(Tree t);


//PER QUESTE DUE RICORDARSI:
//1.che il file deve contenere l albero stampato in pre order
//2.che bisogna inserire un carattere per identificare le foglie ed andare a modificare la itemread e la itemcheckfoglia
void TREEreadF(FILE *fp,Tree *t);
void TREEprintF(FILE *fp,Tree t);
#endif /* Tree_h */
