//
//  Stack.c
//  RaccoltaADTIClasse
//
//  Created by apple on 30/12/16.
//  Copyright © 2016 emag. All rights reserved.
//

#include "Stack.h"




struct stack{
    List stack;
};




Stack STACKinit(){
    Stack tmp=malloc(sizeof(struct stack));
    tmp->stack=LISTinit();
    return tmp;
}




int  STACKempty(Stack x){
    if(LISTempty(x->stack)){
        return 1;
    }
    return 0;
}
void STACKpush(Item x, Stack q){
    LISTinsertHead(x, q->stack);
}

void STACKpop(Stack q, Item *val){
    LISTextractHead(q->stack, val);
}



Item STACKget(Stack q){
    return LISTgetHead(q->stack);
}//ritorna un riferimento all item nello stack ma non una nuova istanza



void STACKdisplay(Stack q){
    LISTdisplay(q->stack);
}



void STACKsetItem(Key oldKey, Key newKey,Stack q){
    LISTsetItem(oldKey, newKey, q->stack);
}//cambia la chiave di un item di un determinato nodo


void STACKdelete(Item x, Stack q){
    LISTdeleteNode(x, q->stack);
}



void STACKfree(Stack q){
    LISTfree(q->stack);
    free(q);
}

void STACKreadF(FILE *fp, Stack q){
    Item tmp=ITEMinit();
    ITEMread(fp,&tmp);
    while(!ITEMcheckvoid(tmp)){
        STACKpush(tmp,q);
        ITEMread(fp,&tmp);
    }
    ITEMfree(tmp);

}



void STACKprintF(FILE *fp, Stack q){
    LISTdisplay(q->stack);
}