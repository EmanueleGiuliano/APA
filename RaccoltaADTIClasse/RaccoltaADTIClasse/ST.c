//
//  ST.c
//  RaccoltaADTIClasse
//
//  Created by apple on 09/01/17.
//  Copyright © 2017 emag. All rights reserved.
//


#include "ST.h"





struct symboltable{
    List *table;int N;int M;
};

//la getIndex puo sempre essere sostiuita da una funzione di hash, sarà poi necessario eliminare la select e gestire le collisioni con il metodo più consono al problema, se invece si vuole realizzare una tabella di simboli come vettore ordinato sarà necessario modificare la insert in modo opportuno.
//NB la get index va modificata ogni volta a seconda del tipo di chiave dell item e la gestione dei duplicati va modificata in base al problema


int getIndex(Key k){
    int tmp=0;
    tmp=(int)k;
    return tmp;
}

ST STinit(int maxN){
    ST x=malloc(sizeof(struct symboltable));
    for(int i=0;i<maxN;i++){
        x->table[i]=LISTinit();
    }
    x->N=0;
    x->M=maxN;
    return x;
}
void STfree(ST st){
    for(int i=0;i<st->M;i++){
        LISTfree(st->table[i]);
    }
    free(st);
}
int STcount(ST st){
    return st->N;
}
int STinsert(ST st, Item val){
    int i=getIndex(KEYget(val));
    LISTinsertHead(val, st->table[i]);
    return i;
}
void STsearch(ST st, Key k, List *cpy){//restituisce la lista degli item con chiave k
    Link x=NULL;
    x=LISTgetNodeHead(st->table[getIndex(k)]);
    while(x!=NULL){
        LISTinsertTail(NODEgetItem(x), (*cpy));
    }
}
void STdelete(ST st, Key k){
    LISTfree(st->table[getIndex(k)]);
    st->table[getIndex(k)]=LISTinit();
}
void STselect(ST st, int r, List *cpy){
    Link x=NULL;
    for(int i=0;i<st->N;i++){
        if(!LISTempty(st->table[i]) && r--==0){
            x=LISTgetNodeHead(st->table[i]);
            while(x!=NULL){
                LISTinsertTail(NODEgetItem(x), (*cpy));
                LISTmoveNext(st->table[i], x);
            }
        }
    }
}
void STdisplay(ST st){
    for(int i=0;i<st->N;i++){
        LISTdisplay(st->table[i]);
    }
}
void STretrieve(ST st,int index, List *x){
    //ciclo di copia della lista, da implementare in caso serva
}

int STsearchIndex(ST st, Key k){
    int index=getIndex(k);
    if(!LISTempty(st->table[index])){
        return index;
    }
    else{
        return -1;
    }
}
