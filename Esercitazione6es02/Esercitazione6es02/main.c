//
//  main.c
//  Esercitazione6es02
//
//  Created by apple on 17/11/16.
//  Copyright © 2016 emag. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef struct nodo* lk;
struct nodo {//la rappresentazione scelta utilizza due puntatori sapendo che l albero è binario
    char *val;//chiave
    lk next;//figli
};
lk splitStringa(char *str, char sep);
void stampaStringa(lk head);
int main(int argc, const char * argv[]) {
    char buffer[256],sepa;
    printf("Inserisci una stringa da dividere in campi separandoli con un carattere a tua scelta(esempio-> ./: ) \n");
    scanf("%s %c",buffer,&sepa);
    /*fflush(stdin);
    printf("Inserisci il carattere separatore\n");
    scanf("%c",&sepa);*/
    stampaStringa(splitStringa(buffer,sepa));
    return 0;
}
lk new_nodo(int dimVal) {
    lk n =(lk) malloc(1*sizeof(struct nodo));
    n->val= malloc(dimVal*sizeof(char));
    n->next = NULL;
    return n;
};
lk splitStringa(char *str, char sep){
    int dimStr=0,i=0,u=0;
    dimStr=0;
    i=0;
    u=0;
    lk h;
    char *sottoStr;
    while(str[i]!=sep){
        dimStr++;
        i++;
    }
    h=new_nodo(dimStr);
    while(str[u]!=sep){
        h->val[u]=str[u];
        u++;
    }
    u=0;
    //creo la sottostringa
    sottoStr= malloc((strlen(str)-dimStr)*sizeof(char));
    for(int k=(i+1);k<strlen(str);k++){
        sottoStr[u]=str[k];
        u++;
    }
    if((i+1)<strlen(str)){
        h->next=splitStringa(sottoStr, sep);
    }
    free(sottoStr);//nella risalita verranno deallocate tutte le sottostringhe create
    return h;
}

void stampaStringa(lk h){
    if(h==NULL){//terminazione ricorsione
        return;
    }
    printf("Parola: %s \n",h->val);
    stampaStringa(h->next);
    free(h);
    return;
}