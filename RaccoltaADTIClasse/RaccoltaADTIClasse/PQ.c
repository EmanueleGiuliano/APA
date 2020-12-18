//
//  PQ.c
//  RaccoltaADTIClasse
//
//  Created by apple on 28/12/16.
//  Copyright © 2016 emag. All rights reserved.
//
/*COMMENTI:
 Si è scelta un implementazione che sfrutta l'adt lista ordinata, semplicemente per poter risparimiare codice e sfruttare il codice gia presente nell altra libreria
 
 La priorità in questo caso è data dal punteggio(piu basso piu la priorità e alta), per molte altre situazioni sarà necessario un item ad hoc che abbia un campo priorità modificabile e gestibile dal programma client(client anche di questa libreria), e la chiave di questo item sarà la priorità, per cui questa libreria non dovrà essere modificata lavorando proprio sul tipo KEY che si riferisce all item
 
 NB: l unica modifica da fare sarebbe nel controllo della PQinsert che ora come ora inserisce in testa se la chiave e piu bassa(siccome la chiave e il punteggio) mentre in una normale coda a priorità con item ad hoc dovrebbe inserire in testa tanto piu alta e la chiave(per cui basta sostituire il < nella keycomapre con un > )
*/
#include "PQ.h"
//typedef struct PQnode *Link;

//struct PQnode{ Item val; Link next; };



struct pq { List queue; };

PQ PQinit(){
    PQ p=malloc(sizeof(struct pq));
    p->queue=LISTinit();
    return p;
}


int PQempty(PQ x){
    if(LISTempty(x->queue)){return 1;}
    return 0;
}





/*Link NEWnode(Item x,Link next){//crea un nuovo pqueuenode
    Link z=NULL;
    
    return z;
}*/









void PQinsert(Item x,PQ q){//inserzione in base alla priorità(chiave piu bassa->priorità piu alta)
    Link z=NULL,p=NULL;
    if(LISTempty(q->queue)|| KEYcompare(KEYget(x),KEYget(LISTgetHead(q->queue)))<0){//i punteggi < della testa diventano essi stessi la testa
        LISTinsertHead(x, q->queue);
        return;
    }
    
    for(p=LISTgetNodeHead(q->queue),z=LISTmoveNext(q->queue, p);z!=NULL && KEYcompare(KEYget(x),KEYget(NODEgetItem(z)))>0;p=z,z=LISTmoveNext(q->queue, z));//cicla fino al punto in cui deve inserire il nodo(eventualmente fino alla coda)
    //inserisce tra p e z
    NODEnewNode(z, p);
    if(z==NULL){
        LISTinsertTail(x, q->queue);
    }
}








void PQextractMax(PQ q, Item *val){//estrae il nodo con priorità piu alta, ovvero in questo caso quello con punteggio piu basso
    LISTextractHead(q->queue, val);
}







void PQshowMax(PQ q){
    ITEMshow(LISTgetHead(q->queue));
}

Item PQgetMax(PQ q){
    return LISTgetHead(q->queue);
}





void PQdisplay(PQ q){
    LISTdisplay(q->queue);
}







void PQdelete(Item x, PQ q){//elimina un item dalla coda
    LISTdeleteNode(x, q->queue);
    return;
}







void PQchange(Item x, PQ q){//a questa funzione va passato l item con priorita gia modificata, essa va solo a cancellare quello vechio e reinserire nella posizione corretta
    PQdelete(x,q);
    PQinsert(x,q);
    return;
}

void PQreadF(FILE *fp, PQ q){
    Item tmp=ITEMinit();
    Link x=NULL;
    x=LISTgetNodeHead(q->queue);
    ITEMread(fp,&tmp);
    while(!ITEMcheckvoid(tmp)){
        PQinsert(tmp,q);
        ITEMread(fp,&tmp);
    }
    ITEMfree(tmp);
}






void PQprintF(FILE *fp, PQ q){
    LISTprintF(fp, q->queue);
}








void PQfree(PQ q){
    LISTfree(q->queue);
    free(q);
}