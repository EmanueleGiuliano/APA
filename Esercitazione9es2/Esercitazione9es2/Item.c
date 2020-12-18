//
//  Item.c
//  Esercitazione9es2
//
//  Created by apple on 17/12/16.
//  Copyright © 2016 emag. All rights reserved.
//

#include "Item.h"

/*
    Com è strutturato questo modulo item:
 
 .Il campo nome contiene semplicemente il nome del partecipante ed è anche la "chiave primaria" che identifica univocamente il partecipante--> di conseguenza non sono consentiti partecipanti con lo stesso nome
 .Il numero di punti iniziale di ogni partecipante è pari a 10 come da consegna
 */

static char buf[50];

float KEYcompare(Key k1, Key k2){
    return(k1-k2);// se maggiore di 0 la chiave k1 e maggiore se =0 sono uguali se <0 la chiave k2 e maggiore
}

Key KEYscan(){
    Key tmp;
    scanf("%f",&tmp);
    return tmp;
}

Key KEYget(Item x){
    return x.punti;
}

Item ITEMscan(){
    Item x;
    scanf("%s %f",x.name,&(x.punti));
    return x;
}

void ITEMshow(Item x){
    printf("Nome: %s/tpunti: %.2f\n",x.name,x.punti);
}



int ITEMcheckvoid(Item x){
    if(strcmp(x.name,"ZzZ")==0 || x.punti==-1){
        return 1;
    }
    return 0;
}

Item ITEMsetvoid(){
    Item x;
    strcpy(x.name,"ZzZ");
    x.punti=-1;
    return x;
}

Item ITEMread(FILE* fp){//se gli passi stdin come argomento diventa una itemscan
    Item tmp;
    if(fscanf(fp,"%s %f",tmp.name,&(tmp.punti))==EOF){
        tmp=ITEMsetvoid();
    }
    
    return tmp;
    
}

void ITEMprint(Item x, FILE *fp){
    fprintf(fp,"%s %.2f\n",x.name,x.punti);
}

float ITEMgetPti(Item x){
    return x.punti;
}
char* ITEMgetName(Item *x){
    return x->name;
}
void ITEMsetPti(Item *x, float pti){
    x->punti=pti;
}
void ITEMsetName(Item *x,char *name){
    strcpy(x->name,name);
}



