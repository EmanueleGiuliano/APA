//
//  HeapPQ.c
//  Esercitazione11es2
//
//  Created by apple on 16/01/17.
//  Copyright © 2017 emag. All rights reserved.
//

#include "HeapPQ.h"

struct pq { Heap queue; int dim;};

PQ PQinit(int dim){
    PQ p=malloc(sizeof(struct pq));
    p->queue=HEAPinit(dim);
    p->dim=dim;
    return p;
}


int PQempty(PQ x){
    if(HEAPsize(x->queue)>0){
        return 0;
    }
    return 1;
}














void PQinsert(Item x,PQ q){//inserisce e riordina coi criteri dell heap
    HEAPfill(q->queue,x);
    HEAPbuild(q->queue);
}








void PQextract(PQ q, Item *val){//estrae il nodo con priorità piu alta, ovvero in questo caso quello con punteggio piu basso
    if(HEAPswapEl(q->queue, 0, HEAPsize(q->queue)-1)){
        HEAPgetEl(q->queue, HEAPsize(q->queue)-1, val);
        HEAPdeleteLastEl(q->queue);
        HEAPbuild(q->queue);
    }
}







void PQshowFirst(PQ q){
    if(HEAPsize(q->queue)>0){
        Item tmp=ITEMinit();
        HEAPgetEl(q->queue,0,&tmp);
        ITEMshow(tmp);
        ITEMfree(tmp);
    }
    else{
        printf("Non ci sono elementi in coda");
    }
}

void PQget(PQ q, Item *x){
    HEAPgetEl(q->queue,0,x);
}





void PQdisplay(PQ q){
    HEAPdisplay(q->queue);
}




void PQdeleteFirst(PQ q){//elimina l item con priorita piu alta
    if(HEAPswapEl(q->queue, 0, HEAPsize(q->queue)-1)){
        HEAPdeleteLastEl(q->queue);
        HEAPbuild(q->queue);
    }
    return;
}

void PQdeleteMin(PQ q){//elimina l item con priorità piu bassa
    HEAPdeleteLastEl(q->queue);
    return;
}

void PQdelete(Key kx, PQ q){//elimina un item dalla coda data la sua priorita
    HEAPswapEl(q->queue, HEAPfindPos(q->queue, kx), HEAPsize(q->queue)-1);
    HEAPdeleteLastEl(q->queue);
    HEAPbuild(q->queue);
    return;
}







void PQchange(Item x, PQ q, Key newPrio){//a questa funzione va passato l item con priorita gia modificata, essa va solo a cancellare quello vechio e reinserire nella posizione corretta
    int pos=HEAPfindPos(q->queue, KEYget(x));
    HEAPsetItemKey(q->queue, pos, newPrio);
    return;
}

void PQreadF(FILE *fp, PQ q){
    HEAPreadF(fp, &(q->queue));
}






void PQprintF(FILE *fp, PQ q){
    HEAPprintF(fp, q->queue);
}








void PQfree(PQ q){
    HEAPfree(q->queue);
    free(q);
}