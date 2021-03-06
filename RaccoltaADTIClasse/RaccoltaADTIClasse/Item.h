//
//  Item.h
//  RaccoltaADTIClasse
//
//  Created by apple on 28/12/16.
//  Copyright © 2016 emag. All rights reserved.
//
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#ifndef Item_h
#define Item_h
#define MAXC 21

typedef struct item *Item;

typedef float Key;

//FUNZIONI GENERICHE NECESSARIE AD OGNI ITEM

float KEYcompare(Key k1, Key k2);
Key KEYscan();
Key KEYget(Item x);
void KEYset(Item x, Key k);


Item ITEMinit();
void ITEMfree(Item x);
void ITEMread(FILE* fp, Item *tmp);
int ITEMcheckvoid(Item x);
void ITEMprint(Item x,FILE *fp);
Item ITEMsetvoid(Item x);
Item ITEMscan(Item x);
void ITEMshow(Item x);
void ITEMdup(Item x, Item *val);//duplica un item (bisogna fornirglielo gia istanziato)
Item* ITEMinitVett(int dim);
Item* ITEMchangeVett(Item v[],int oldDim,int newDim);

//PER LETTURA ALBERI DA FILE
int  ITEMcheckfoglia(Item x);
void ITEMsetfoglia(Item *x);
void ITEMsetNotfoglia(Item *x);

//FUNZIONI SPECIFICHE DELL ITEM CONSIDERATO
float ITEMgetPti(Item x);
char* ITEMgetName(Item x);
void ITEMsetPti(Item x, float pti);
void ITEMsetName(Item x,char* name);

#endif /* Item_h */
