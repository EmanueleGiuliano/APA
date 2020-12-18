//
//  Item.c
//  RaccoltaADTIClasse
//
//  Created by apple on 28/12/16.
//  Copyright © 2016 emag. All rights reserved.
//

#include "Item.h"

//
//  Item.c
//  Esercitazione9es2
//
//  Created by apple on 17/12/16.
//  Copyright © 2016 emag. All rights reserved.
//

/*
 Com è strutturato questo modulo item:
 
 .Il campo nome contiene semplicemente il nome del partecipante ed è anche la "chiave primaria" che identifica univocamente il partecipante--> di conseguenza non sono consentiti partecipanti con lo stesso nome
 .Il numero di punti iniziale di ogni partecipante è pari a 10 come da consegna
 */

//NB ogni volta che si modifica un item ricordare di mantenere la keycompare che restituisca 0 in caso di ugualglianza tra chiavi, per mantenere la compatibilità con gli altri adt che utlizzano item

//static char buf[50];

struct item{
    char name[51];//nomePartecipante
    float punti;//punteggio
};





float KEYcompare(Key k1, Key k2){
    return(k1-k2);// se maggiore di 0 la chiave k1 e maggiore se =0 sono uguali se <0 la chiave k2 e maggiore
}


void KEYset(Item x, Key k){
    x->punti=k;
}



Key KEYscan(){
    Key tmp;
    scanf("%f",&tmp);
    return tmp;
}





Key KEYget(Item x){
    return x->punti;
}



Item* ITEMinitVett(int dim){
    Item *x=NULL;
    x=malloc(dim*sizeof(Item));//istanzia dim puntatori
    for(int i=0;i<dim;i++){
        x[i]=ITEMinit();
    }
    return x;
}

Item* ITEMchangeVett(Item v[],int oldDim,int newDim){
    v=realloc(v, (oldDim+newDim)*(sizeof(struct item)));
    return v;
}


Item ITEMinit(){
    Item x=malloc(sizeof(struct item));
    x=ITEMsetvoid(x);
    return x;
}






Item ITEMscan(Item x){
    scanf("%s %f",x->name,&(x->punti));
    return x;
}







void ITEMfree(Item x){
    free(x);
}







void ITEMshow(Item x){
    printf("Nome: %s\tpunti: %.2f\n",x->name,x->punti);
}






int ITEMcheckvoid(Item x){
    if(strcmp(x->name,"ZzZ")==0 || x->punti==-1){
        return 1;
    }
    return 0;
}






Item ITEMsetvoid(Item x){
    strcpy(x->name,"ZzZ");
    x->punti=-1;
    return x;
}







void ITEMread(FILE* fp, Item *tmp){//se gli passi stdin come argomento diventa una itemscan
    if(fscanf(fp,"%s %f",(*tmp)->name,&((*tmp)->punti))==EOF){
        *tmp=ITEMsetvoid((*tmp));
    }
    
    
}







void ITEMprint(Item x, FILE *fp){
    fprintf(fp,"%s %.2f\n",x->name,x->punti);
}






float ITEMgetPti(Item x){
    return x->punti;
}




char* ITEMgetName(Item x){
    return x->name;
}







void ITEMsetPti(Item x, float pti){
    x->punti=pti;
}






void ITEMsetName(Item x,char *name){
    strcpy(x->name,name);
}

void ITEMdup(Item x, Item *val){//NB non deve mai fare delle item init, la si usa spesso per evitare problemi di ownership
    
    ITEMsetName(*val, ITEMgetName(x));
    ITEMsetPti(*val, ITEMgetPti(x));
}




int ITEMcheckfoglia(Item x){//si e scelto di mettere un asterisco al fondo del campo nome per dire se e una foglia o meno
    int dim=(int)strlen(x->name);
    if(x->name[dim-1]=='*'){
        return 1;
    }
    return 0;
}



void ITEMsetfoglia(Item *x){
    char *tmp=NULL;
    tmp=strcat((*x)->name,"*");
}
void ITEMsetNotfoglia(Item *x){
    int dim=(int)strlen((*x)->name);
    (*x)->name[dim-1]='\0';
}