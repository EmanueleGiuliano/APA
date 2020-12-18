//
//  main.c
//  Esercitazione06es3
//
//  Created by apple on 18/11/16.
//  Copyright © 2016 emag. All rights reserved.
//

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
typedef  struct punto* lk;
struct punto{
    int x;
    int y;
    lk next;
};
lk new_nodo(int x, int y, lk next);
lk inserisciNodo(lk n,int x,int y);
void stampaLista(lk h);
void liberaLista(lk h);
float calcolaDist(int x,int y);

int main(int argc, const char * argv[]) {
    int x=0,y=0,continua=1;
    lk h=NULL;
    while(continua){
        printf("Inserisci le coordinate di un punto del piano(x,y):\n");
        scanf("%d%d",&x,&y);
        h=inserisciNodo(h,x,y);
        printf("Vuoi continuare a inserire valori? 1->Sì 0->No\n");
        scanf("%d",&continua);
    }
    stampaLista(h);
    liberaLista(h);
    return 0;
}

lk new_nodo(int x, int y, lk next){
    lk n=NULL;
    n=(lk)malloc(sizeof(lk));
    n->next=next;
    n->x=x;
    n->y=y;
    return n;
}
float calcolaDist(int x,int y){
    float ris=0.0;
    ris=sqrtf((float)(x*x)+(float)(y*y));
    return ris;
}
lk inserisciNodo(lk h,int x,int y){
    lk j=NULL,p=NULL;
    if(h==NULL || calcolaDist(x, y)<calcolaDist(h->x, h->y)){//primo nodo della lista o inserimento in testa se serve
        return new_nodo(x, y, h);
    }
    else{
        //continuo a cercare fino a che non trovo un nodo che ha distanza dall'origine maggiore
        for (j=h->next, p=h;j!=NULL && calcolaDist(x,y)>calcolaDist(j->x,j->y);p=j, j=j->next);
        p->next=new_nodo(x, y, j);
    }
    return h;
}
void stampaLista(lk h){
    lk x=NULL;
    for(x=h;x!=NULL;x=x->next){
        printf("%d %d\n",x->x,x->y);
    }
}

void liberaLista(lk h){
    lk x=NULL;
    for(x=h->next;x!=NULL;x=x->next){
        free(x);
    }
    free(h);
}