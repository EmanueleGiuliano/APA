//
//  PQ.c
//  Esercitazione9es2
//
//  Created by apple on 17/12/16.
//  Copyright © 2016 emag. All rights reserved.
//

#include "PQ.h"

/*
 NB:
 
 L'head è sempre l elemento piu vecchio che hai inserito, in qualunque tipo di coda, fifo o priority first, gli inserimenti in una coda normale avvengono in coda e le estrazioni in testa
 
 i nodi a priorità più alta stanno sempre in testa, sempre per un concetto di politica fifo, è una fifo con priorità, ovvero il primo che arriva sarà il primo ad essere estratto, cosi da non violare il concetto di coda, ma aggiungendo il concetto di priorità i nodi a priorità piu alta verranno fatti scivolare verso la testa,scavalcando chi ha priorità minore, mentre gli altri rimarranno in coda, di conseguenza avrò gruppi di nodi a uguale priorità gestiti con fifo.
     La coda sarà l ultimo nodo inserito !!E!! con priorità più bassa.
 
 In questo particolare caso ho adattato la coda all esercizio di modo che la priorità sia piu alta piu basso è il punteggio, per questo al posto della keycompare si usa la itemcompare che compara i punteggi e restituisce qual è il maggiore, si fanno scivolare verso il fondo gli item con punteggio piu alto perche hanno priorità minore.
 
 Gli scontri saranno sempre tra il nodo head e il suo successore, ogni volta il perdente dello scontro subirà una modifica del punteggio e di conseguenza una modifica della priorità, il client dovra occuparsi di eliminarlo dalla coda in caso il punteggio sia zero, 
     (gli basterà chiamare una extractmax)
     altrimenti chiamerà una pqchange e questo modulo si occupera di far scivolare l item in questione verso la testa
 */




typedef struct PQnode *Link;

struct PQnode{ Item val; Link next; };



 struct PQ { Link head; Link tail; };

static struct PQ  pq;//Implementazione come quasi adt/non adt, non si possono istanziare un numero arbitrario di liste


int PQempty(){
    if(pq.head==NULL){return 1;}
    return 0;
}





Link NEWnode(Item x,Link next){//crea un nuovo pqueuenode
    Link z=NULL;
    z=malloc(sizeof(struct PQnode));
    z->val=x;
    z->next=next;
    return z;
}









void PQinsert(Item x){
    Link z=NULL,p=NULL;
    if(pq.head==NULL|| KEYcompare(KEYget(x),KEYget(pq.head->val))<0){//i punteggi < della testa diventano essi stessi la testa
        pq.head=NEWnode(x,pq.head);
        return;
    }
    for(z=pq.head->next, p=pq.head;z!=NULL && KEYcompare(KEYget(x),KEYget(z->val))>0;p=z,z=z->next);//cicla fino al punto in cui deve inserire il nodo(eventualmente fino alla coda)
    p->next=NEWnode(x,z);
    if(z==NULL){pq.tail=p->next;}
}








Item PQextractMax(){//estrae il nodo con priorità piu alta, ovvero in questo caso quello con punteggio piu basso
    Item tmp;
    Link z=NULL;
    tmp=pq.head->val;
    if(PQempty()){
        printf("\t!Non ci sono piu elementi\n");
        return ITEMsetvoid();
    }
    z=pq.head->next;
    tmp=pq.head->val;
    free(pq.head);
    pq.head=z;
    //printf("Extract MAX sta restituendo: %s %.2f\n",pq.head->val.name,pq.head->val.punti);
    return tmp;
}







Item PQshowMax(){
    return pq.head->val;
}







void PQdisplay(){
    Link p;
    printf("Partecipanti in coda:\n");
    for(p=pq.head;p!=NULL;p=p->next){
        printf("\tNome: %s\tpunti: %f\n",p->val.name,p->val.punti);
    }
}







void PQdelete(Item x){//elimina un item dalla coda
    Link z,p;
    if(PQempty()){
        printf("Coda vuota!\n");
        return;
    }
    for(z=pq.head, p=NULL; z!=NULL && KEYcompare(KEYget(z->val),KEYget(x))!=0 ; p=z, z=z->next);
    if(z!=NULL){
        if (z==pq.head) {//bypass nodo z e liberazione nodo
            pq.head = z->next;
        }
        else {
            p->next = z->next;
        }
        free(z);
    }
    return;
}







void PQchange(Item x){//a questa funzione va passato l item con priorita gia modificata, essa va solo a cancellare quello vechio e reinserire nella posizione corretta
        PQdelete(x);
        PQinsert(x);
    return;
}