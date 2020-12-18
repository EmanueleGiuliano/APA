//
//  main.c
//  Esercitazione8es1
//
//  Created by apple on 08/12/16.
//  Copyright © 2016 emag. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define DBG 6
#define DBG2 4

int disp_rip(int pos,int *val,int *solParziale,int *solFinale,int n,int k,int count,int *sequenzaIniziale);
int bilanciata(int *sol,int dim);
int numeroMosse(int *sequenzaOriginale,int *nuovaSequenza,int dim);
int main(int argc, const char * argv[]) {
    
    int dimSequenza=0,dist_val[2]={0,1},occorrenzeFrecce[2]={0,0},*sequenza=NULL,*solParziale=NULL,*solFinale=NULL,contatore=0;
    printf("Quanti valori ha la tua sequenza? ");
    scanf("%d",&dimSequenza);
    sequenza=malloc(dimSequenza*sizeof(int));
    solParziale=malloc(dimSequenza*sizeof(int));
    solFinale=malloc(dimSequenza*sizeof(int));
    printf("Inserisci la sequenza:\n");
    for(int i=0;i<dimSequenza;i++){
        scanf("%d",&sequenza[i]);
    }
    printf("\nLa tua sequenza e': ");
    for(int i=0;i<dimSequenza;i++){
        printf("%d",sequenza[i]);
        solParziale[i]=0;solFinale[i]=0;
        if(sequenza[i]==0){occorrenzeFrecce[0]++;}
        if(sequenza[i]==1){occorrenzeFrecce[1]++;}
    }
    printf("\n");
    
    if(!bilanciata(sequenza, dimSequenza)){
        if(occorrenzeFrecce[0]==0){
            sequenza[0]=0;
        }
        if(occorrenzeFrecce[1]==0){
            sequenza[0]=1;
        }
        if((dimSequenza%2)!=0){
            printf("Sequenza non bilanciabile\n");
        }
        else{
            contatore = disp_rip(0, dist_val, solParziale, solFinale, 2, dimSequenza, 0, sequenza);
        }
        if(contatore>0){
            printf("Sequenza bilanciata(con minor numero di mosse possibili): ");
            for(int k=0;k<dimSequenza;k++){
                printf("%d",solFinale[k]);
            }
            printf("\n");
        }
        else{
            printf("Non sono riuscito a bilanciare la sequenza.\n");
        }
     }
     else{
     printf("La tua sequenza è gia bilanciata.\n");
     }
    
    return 0;
}


int numeroMosse(int *sequenzaOriginale,int *nuovaSequenza,int dim){
    int nm=0;
    for(int i=0;i<dim;i++){
        if(sequenzaOriginale[i]!=nuovaSequenza[i]){
            nm++;
        }
    }
    return nm;
}

int bilanciata(int *sol,int dim){
    int i=0,k=1,occorrenze[2]={0,0};
    
#ifndef DBG
    printf("Stampa di debug:sol parziale --> ");
    for(int k=0;k<dim;k++)
        printf("%d",sol[k]);
    printf("\n");
#endif
    occorrenze[sol[i]]++;
    while(k<dim){
    while(sol[k]==sol[i] && k<dim){
        occorrenze[sol[k]]++;
        k++;i++;
    }
        if(k<dim){
            occorrenze[sol[k]]++;
            k++;i++;
        }
    while(sol[k]==sol[i] && k<dim){
        occorrenze[sol[k]]++;
        k++;i++;
    }
    if(occorrenze[0]!=occorrenze[1]){
#ifndef DBG
        printf("Non bilanciata\n");
#endif
        return 0;
    }
    occorrenze[0]=0;
    occorrenze[1]=0;
    if(k<dim){
        occorrenze[sol[k]]++;
    }
        k++;i++;
    }
    return 1;
}




int disp_rip(int pos,int *val,int *solParziale,int *solFinale,int n,int k,int count,int *sequenzaIniziale){
    int i;
    if (pos >= k) {
        if(bilanciata(solParziale,k)){
            if(numeroMosse(solParziale,sequenzaIniziale,n)<numeroMosse(solFinale,sequenzaIniziale,n)){
                for(int i=0;i<k;i++){
                    solFinale[i]=solParziale[i];
                }
#ifndef DBG2
                printf("Stampa di debug: nuova soluzione finale --> ");
                for(int u=0;u<k;u++)
                    printf("%d",solFinale[u]);
                printf("\n");
#endif
                return count+1;//ho trovato una soluzione bilanciata in piu
            }
        }
        return count;
    }
    for (i = 0; i < n; i++) {
        solParziale[pos] = val[i];
        count = disp_rip(pos+1, val, solParziale,solFinale, n, k, count,sequenzaIniziale);
    }
    return count;
}











