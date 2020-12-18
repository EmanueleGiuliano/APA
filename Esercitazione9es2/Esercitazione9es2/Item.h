//
//  Item.h
//  Esercitazione9es2
//
//  Created by apple on 17/12/16.
//  Copyright © 2016 emag. All rights reserved.
//

#include <string.h>
#include <stdio.h>

#ifndef Item_h
#define Item_h
#define MAXC 21

typedef struct item {
    char name[MAXC];//nomePartecipante
    float punti;//punteggio
} Item;
typedef float Key;

float KEYcompare(Key k1, Key k2);
Key KEYscan();
Key KEYget(Item x);
Item ITEMscan();
Item ITEMread(FILE* fp);
void ITEMshow(Item x);
int ITEMcheckvoid(Item x);
void ITEMprint(Item x,FILE *fp);
Item ITEMsetvoid();
float ITEMgetPti(Item x);
char* ITEMgetName(Item *x);
void ITEMsetPti(Item *x, float pti);
void ITEMsetName(Item *x,char* name);
#endif /* Item_h */
