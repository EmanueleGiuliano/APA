//
//  List.c
//  RaccoltaADTIClasse
//
//  Created by apple on 28/12/16.
//  Copyright © 2016 emag. All rights reserved.
//

#include "List.h"


/*
 |...............................................|
 |  ADT di prima classe Lista concatenata doppia |
 |si e scelta una lista che utilizza nodi        |
 |sentinella,per cui quando si guarda al codice è|
 |bene ricordarsi questa scelta                  |
 |...............................................|
 */



//STRUTTURE DATI NASCOSTE AL CLIENT






struct list{//wrapper che contiene solamente il puntatore alla testa e alla coda
    Link head;
    Link tail;
};

struct node{
    Item val;
    Link next;
    Link prev;
};








//PROCEDURE E FUNZIONI DELL ADT




Link NODEnewNode(Link next, Link prev){//mi restituisce un link al nodo dopo averlo allocato
    Link n=malloc(sizeof(struct node));
    n->val=ITEMinit();
    n->val=ITEMsetvoid(n->val);//inserisco un item nullo provvisoriamente nel nodo
    n->next=next;
    n->prev=prev;
    return n;
}





List LISTinit(){//crea una lista vuota con un due nodi sentinella per testa e coda
    List x=malloc(sizeof(struct list));
    x->head=NODEnewNode(NULL, NULL);
    x->tail=NODEnewNode(NULL, NULL);
    x->head->next=x->tail;
    x->tail->prev=x->head;
    return x;
}





void LISTinsertTail(Item x,List l){
    Link n=NODEnewNode(l->tail, l->tail->prev);//inserisce tra il penultimo e la sentinella
    l->tail->prev->next=n;
    l->tail->prev=n;
    ITEMdup(x,&(l->tail->prev->val));//copia l item nell item del nodo istanziato
}//inserzione in coda





void LISTinsertHead(Item x,List l){//si usa l item dup perche si è deciso che il nodo ha una composizione stretta con il suo item per cui si copiano i valori da x all item istanziato dal nodo della lista
    Link n=NODEnewNode(l->head->next, l->head);//inserisce tra il primo e la sentinella
    l->head->next->prev=n;
    l->head->next=n;
    ITEMdup(x,&(l->head->next->val));//copia l item nell item del nodo istanziato
}//inserzione in testa




void LISTextract(Key kx, List l,Item *val){// si è scelto di non utilizzare la return per risolvere un problema sull ownership dell item
    
    Link x=NULL,p=NULL;
    
    if(KEYcompare(kx, KEYget(l->head->next->val))==0){
        ITEMdup(x->val,val);
        return;
    }
    
    if(KEYcompare(kx, KEYget(l->tail->prev->val))==0){
        ITEMdup(x->val,val);
        return;
    }
    
    //se non e ne in coda ne in testa sono costretto a ciclare
    
    for(x=l->head->next->next, p=l->head->next;!ITEMcheckvoid(x->val) && KEYcompare(kx, KEYget(x->val))!=0;p=x,x=x->next);
    
    if(ITEMcheckvoid(x->val)){//ho ciclato fino al nodo sentinella(che vale void)
        printf("\t\tElemento non trovato!\n");
    }
    ITEMdup(x->val,val);
    //bypass
    p->next=x->next;
    x->next->prev=p;
    //liberazione memoria
    ITEMfree(x->val);//libera l item di proprietà del nodo
    free(x);//libera il nodo
    
    
    
}//estrae il primo item con una certa chiave






void LISTextractHead(List l, Item *val){
    Link x=NULL;
    if(!ITEMcheckvoid(l->head->next->val)){
        x=l->head->next;
        //bypass
        x->next->prev=l->head;
        l->head->next=x->next;
        //copia il valore del nodo
        //*val=x->val;
        //libera la memoria
        ITEMdup(x->val,val);
        ITEMfree(x->val);
        free(x);
    }
    else{
        printf("\tLista vuota!");
        *val = l->head->val;//returna un item void(la sentinella)
    }
}//estrae in testa alla lista










void LISTextractTail(List l, Item *val){//anche qui sara il client a fornire l item che dovra contenere il valore del nodo
    Link x=NULL;
    if(!ITEMcheckvoid(l->tail->prev->val)){
        x=l->tail->prev;
        //bypass
        x->prev->next=l->tail;
        l->tail->prev=x->prev;
        //copia il valore del nodo
        //*val=x->val;
        //libera la memoria
        ITEMdup(x->val,val);
        ITEMfree(x->val);
        free(x);
    }
    else{
        printf("\tLista vuota!");
        *val = l->head->val;//returna un item void(la sentinella)
    }
}//estrae in coda alla lista










void LISTdisplay(List l){
    Link x=NULL;
    for(x=l->head->next;!ITEMcheckvoid(x->val);x=x->next){
        ITEMshow(x->val);
    }
}














void LISTdeleteNode(Item x, List l){
    Link z=NULL;
    for(z=l->head->next;!ITEMcheckvoid(z->val) && KEYcompare(KEYget(z->val), KEYget(x))!=0;z=z->next);
    if(ITEMcheckvoid(z->val)){
        printf("\t\tElemento non trovato\n");
    }
    else{
        //bypass
        z->prev->next=z->next;
        z->next->prev=z->prev;
        //libera memoria
        ITEMfree(z->val);
        free(z);
        printf("\t\t Elemento eliminato con successo\n");
    }
}














void LISTshowNode(Key kx,List l){
    Link x=NULL;
    for(x=l->head->next;!ITEMcheckvoid(x->val) && KEYcompare(KEYget(x->val), kx)!=0;x=x->next);
    if(ITEMcheckvoid(x->val)){
        printf("\t\tElemento non trovato\n");
    }
    else{
        ITEMshow(x->val);
    }
}











void LISTreadF(FILE *fp,List l){
    Item tmp=ITEMinit();
    ITEMread(fp,&tmp);
    while(!ITEMcheckvoid(tmp)){
        LISTinsertTail(tmp, l);
        ITEMread(fp,&tmp);
    }
    ITEMfree(tmp);
}//legge un file e carica la lista










void LISTprintF(FILE *fp,List l){
    Link x=NULL;
    for(x=l->head->next;!ITEMcheckvoid(x->val);x=x->next){
        ITEMprint(x->val, fp);
    }
}//stampa una lista su file









void LISTsetItem(Key oldKey, Key newKey,List l){
    Link x=NULL;
    for(x=l->head->next;!ITEMcheckvoid(x->val) && KEYcompare(KEYget(x->val), oldKey)!=0;x=x->next);
    if(ITEMcheckvoid(x->val)){
        printf("\t\tElemento non trovato\n");
    }
    else{
        KEYset(x->val,newKey);
    }
}//cambia la chiave di un item di un determinato nodo



/*
void LISTsort(List l){
    Link x=NULL,z=NULL,s=NULL,headList=NULL;//z==t,s==u
    headList=l->head->next;//salta la sentinella
    if(ITEMcheckvoid(headList->val)){
        printf("\t\tLista vuota\n");
    }
    else{
        for(z=headList->next, headList->next->prev=NULL,headList->next=NULL;z!=NULL;z=s){
            s=z->next;
            if(KEYcompare(KEYget(headList->val), KEYget(z->val))>0){
                //reinserisco la testa tra z e il resto della lista
                headList->next=s;
                headList->prev=z;
                z->next=headList;
                s->prev=headList;
                headList=z;
                //riaggiorna i link con la sentinella
                l->head->next=headList;
                headList->prev=l->head->next;
            }
              for(x=headList;!ITEMcheckvoid(x->next->val) && KEYcompare(KEYget(x->next->val),KEYget(z->val))>0;x=x->next);
            //inserimento tra x->next ed x
            z->next=x->next;
            
        }
    }

}//ordina la lista con insertionSort*/







List LISTreverse(List l){
    Item u;
    Link x=NULL;
    List tmp=NULL;
    tmp=LISTinit();
    for(x=l->tail->prev;!ITEMcheckvoid(x->val);x=x->prev){
        LISTextractTail(l, &u);//estrae in coda ad l ed inserisce in coda a tmp
        LISTinsertTail(u, tmp);
    }
    return tmp;
}//crea una lista invertita









int LISTempty(List l){
    if(l->head->next==l->tail){
        return 1;
    }
    return 0;
}








void LISTgetItem(Key kx, List l, Item *val){
    Link x=NULL;
    for(x=l->head->next;!ITEMcheckvoid(x->val) && KEYcompare(KEYget(x->val), kx)!=0;x=x->next);
    if(ITEMcheckvoid(x->val)){
        printf("\t\tElemento non trovato\n");
    }
    ITEMdup(x->val,val);
    return;
}





Item LISTgetTail(List l){//in caso sia vuota restituisce ITEMSETVOID
    return l->tail->prev->val;
}






Item LISTgetHead(List l){
    return l->head->next->val;
}

void LISTcpyHead(List l, Item *cpy){
    if(!LISTempty(l)){
        ITEMdup(l->head->next->val,cpy);
    }
}




Link LISTmoveNext(List l,Link x){
    if(!ITEMcheckvoid(x->val)){
        return x->next;
    }
    
    return NULL;//returna null se è arrivato alla sentinella
}



Link LISTgetNodeHead(List l){
    return l->head->next;
}



Link LISTmovePrev(List l, Link x){
    if(!ITEMcheckvoid(x->val)){
        return x->prev;
    }
    
    return NULL;
}

Item NODEgetItem(Link x){
    return x->val;
}

void NODEfree(Link x){
    //bypass
    x->prev->next=x->next;
    x->next->prev=x->prev;
    //liberazione
    ITEMfree(x->val);
    free(x);
}

void LISTdeleteNodeK(Key kx, List l){
    Link z=NULL;
    for(z=l->head->next;!ITEMcheckvoid(z->val) && KEYcompare(KEYget(z->val), kx)!=0;z=z->next);
    if(ITEMcheckvoid(z->val)){
        printf("\t\tElemento non trovato\n");
    }
    else{
        //bypass
        z->prev->next=z->next;
        z->next->prev=z->prev;
        //libera memoria
        ITEMfree(z->val);
        free(z);
        printf("\t\t Elemento eliminato con successo\n");
    }
}

void LISTfree(List l){
    Link x=NULL,s=NULL;
    for(x=l->head, s=l->head->next;s!=NULL;x=s ,s=s->next){
        ITEMfree(x->val);
        free(x);
    }
}