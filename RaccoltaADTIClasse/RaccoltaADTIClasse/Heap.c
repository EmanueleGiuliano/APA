//
//  Heap.c
//  RaccoltaADTIClasse
//
//  Created by apple on 09/01/17.
//  Copyright © 2017 emag. All rights reserved.
//

#include "Heap.h"

struct heap {
    Item *A;
    int heapsize;
};

Heap HEAPinit(int dim){
    Heap h;
    h = malloc(sizeof(*h));
    h->A = ITEMinitVett(dim);
    h->heapsize = 0;
    return h;
}



//...........................FUNZIONI DI UTILITA' INTERNE ALL ADT................................

//FUNZIONI DI MOVIMENTO ALL INTERNO DELL HEAP
int LEFT(int i) {
    return (i*2 + 1);
}
int RIGHT(int i) {
    return (i*2 + 2);
}
int PARENT(int i) {
    return ((i-1)/2);
}


void Swap(Heap h, int index1, int index2){
    Item tmp=ITEMinit();
    ITEMdup(h->A[index1],&tmp);
    ITEMdup(h->A[index2],&(h->A[index1]));
    ITEMdup(tmp,&(h->A[index2]));
    ITEMfree(tmp);
}

void HEAPify(Heap h, int i) {
    int l, r, largest;
    l = LEFT(i);
    r = RIGHT(i);
    if ((l < h->heapsize) && (KEYcompare(KEYget(h->A[l]),KEYget(h->A[i]))>0)){
        largest = l;
    }
    else{
        largest = i;
    }
    if ((r<h->heapsize)&& (KEYcompare(KEYget(h->A[r]),KEYget(h->A[l]))>0)){
        largest = r;
    }
    if (largest != i) {
        Swap(h, i,largest);
        HEAPify(h, largest);
    }
    return;
}



//..................................................................................................


void HEAPbuild (Heap h) {
    int i;
    for (i=(h->heapsize)/2-1; i >= 0; i--){
        HEAPify(h, i);
    }
    return;
}


void HEAPfill(Heap h, Item x){
    int i;
    i  = h->heapsize++;
    ITEMdup(x, &(h->A[i]));
    return;
}



void HEAPsort(Heap h) {
    int i, j;
    HEAPbuild(h);
    j = h->heapsize;
    for (i = h->heapsize-1; i > 0; i--) {
        Swap (h,0,i);
        h->heapsize--;
        HEAPify(h,0);
    }
    h->heapsize = j;
    return;
}



void HEAPdisplay(Heap h){
    for(int i=0;i<h->heapsize;i++){
        ITEMshow(h->A[i]);
    }
}









void HEAPreadF(FILE *fp,Heap *h){
    int i=0;
    Item lettura=ITEMinit();
    ITEMread(fp,&lettura);
    while(!ITEMcheckvoid(lettura) && i<(*h)->heapsize){
        ITEMdup(lettura,&((*h)->A[i]));
        i++;
    }
    HEAPbuild((*h));
    ITEMfree(lettura);
}//legge degli item e costruisce un heap


void HEAPprintFR(FILE *fp, Item x[], int i,int tabulazione,int maxD){
    if(i>=maxD){
        return;
    }
    for(int k=0;k<tabulazione;k++){
        fprintf(fp,"\t");
    }
    if(LEFT(i)>=maxD && RIGHT(i)>=maxD){
        ITEMsetfoglia(&(x[i]));
    }
    ITEMprint(x[i],fp);
    HEAPprintFR(fp,x,LEFT(i),tabulazione+1,maxD);
    HEAPprintFR(fp,x,RIGHT(i),tabulazione+1,maxD);
    
}
void HEAPprintF(FILE *fp,Heap h){
    HEAPprintFR(fp,h->A,0,0,h->heapsize);
}//stampa l heap su file come un albero binario



