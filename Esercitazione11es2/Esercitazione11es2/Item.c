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
    char codice[51];
    int priorita;//chiave
};





int KEYcompare(Key k1, Key k2){
    return(k1-k2);// se maggiore di 0 la chiave k1 e maggiore se =0 sono uguali se <0 la chiave k2 e maggiore
}


void KEYset(Item x, Key k){
    x->priorita=k;
}



Key KEYscan(){
    Key tmp;
    scanf("%d",&tmp);
    return tmp;
}





Key KEYget(Item x){
    return x->priorita;
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
    scanf("%s %d",x->codice,&(x->priorita));
    return x;
}







void ITEMfree(Item x){
    free(x);
}







void ITEMshow(Item x){
    printf("Codice: %s\tpriorita': %d\n",x->codice,x->priorita);
}






int ITEMcheckvoid(Item x){
    if(strcmp(x->codice,"ZzZ")==0 || x->priorita==-1){
        return 1;
    }
    return 0;
}






Item ITEMsetvoid(Item x){
    strcpy(x->codice,"ZzZ");
    x->priorita=-1;
    return x;
}







void ITEMread(FILE* fp, Item *tmp){//se gli passi stdin come argomento diventa una itemscan
    if(fscanf(fp,"%s %d",(*tmp)->codice,&((*tmp)->priorita))==EOF){
        *tmp=ITEMsetvoid((*tmp));
    }
    
    
}







void ITEMprint(Item x, FILE *fp){
    fprintf(fp,"%s %d\n",x->codice,x->priorita);
}






int ITEMgetPrio(Item x){
    return x->priorita;
}




char* ITEMgetCod(Item x){
    return x->codice;
}







void ITEMsetPrio(Item x, int prio){
    x->priorita=prio;
}






void ITEMsetCod(Item x,char *cod){
    strcpy(x->codice,cod);
}

void ITEMdup(Item x, Item *val){//NB non deve mai fare delle item init, la si usa spesso per evitare problemi di ownership
    ITEMsetPrio(*val, ITEMgetPrio(x));
    ITEMsetCod(*val, ITEMgetCod(x));
}




int ITEMcheckfoglia(Item x){//si e scelto di mettere un asterisco al fondo del campo nome per dire se e una foglia o meno
    int dim=(int)strlen(x->codice);
    if(x->codice[dim-1]=='*'){
        return 1;
    }
    return 0;
}



void ITEMsetfoglia(Item *x){
    char *tmp=NULL;
    tmp=strcat((*x)->codice,"*");
}
void ITEMsetNotfoglia(Item *x){
    int dim=(int)strlen((*x)->codice);
    (*x)->codice[dim-1]='\0';
}