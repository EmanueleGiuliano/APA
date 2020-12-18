//
//  Queue.c
//  RaccoltaADTIClasse
//
//  Created by apple on 30/12/16.
//  Copyright © 2016 emag. All rights reserved.
//

#include "Queue.h"


struct queue{
    List queue;
};

Queue QUEUEinit(){
    Queue tmp=malloc(sizeof(struct queue));
    tmp->queue=LISTinit();
    return tmp;
}


int  QUEUEempty(Queue x){
    if(LISTempty(x->queue)){
        return 1;
    }
    return 0;
}



void QUEUEenqueue(Item x, Queue q){
    LISTinsertTail(x, q->queue);
}

void QUEUEdequeue(Queue q, Item *val){
    LISTextractHead(q->queue, val);
}

Item QUEUEget(Queue q){
    return LISTgetHead(q->queue);
}//ritorna un riferimento all item nella coda ma non una nuova istanza


void QUEUEdisplay(Queue q){
    LISTdisplay(q->queue);
}


void QUEUEsetItem(Key oldKey, Key newKey,Queue q){
    LISTsetItem(oldKey, newKey, q->queue);
}//cambia la chiave di un item di un determinato nodo


void QUEUEdelete(Item x, Queue q){
    LISTdeleteNode(x, q->queue);
}


void QUEUEfree(Queue q){
    LISTfree(q->queue);
}



void QUEUEreadF(FILE *fp, Queue q){
    LISTreadF(fp, q->queue);
}


void QUEUEprintF(FILE *fp, Queue q){
    LISTprintF(fp, q->queue);
}