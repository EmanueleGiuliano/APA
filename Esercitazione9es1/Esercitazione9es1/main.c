//
//  main.c
//  Esercitazione9es1
//
//  Created by apple on 09/12/16.
//  Copyright © 2016 emag. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct el{
    char nome[21];
    float punteggio;
    float difficolta;
}elemento;

typedef struct comb{
    char nomeCategoria[31];
    int numElementi;
    int minElementi;
    int maxElementi;
    float rapportoDiffPunti;
    elemento *elenco;
}combinazione_elementi;
combinazione_elementi *caricaCategorie(int *numCat,char nomeFile[]);
void combinaElementi(combinazione_elementi *val,combinazione_elementi *sol);
void ricombina(combinazione_elementi val,combinazione_elementi sol);
int comb_r(int pos,elemento *val,elemento *sol,elemento **migliore,int n,int k,int start, int count, float *rapportoDiffPunti,int *dimMigliore);
int rComb_r(int pos,elemento *val,elemento *sol,elemento *migliore,int n,int k,int start, int count, float *rapportoDiffPunti,int *dimMigliore);
int soluzioneValida(combinazione_elementi *soluzione, int diffMax,int numCat);
int cercaPeggiore(combinazione_elementi soluzione[], int numCat);
void stampa(combinazione_elementi soluzione[], int numCat);



int main(int argc, const char * argv[]) {
    int numCat=0,p=-1,cntR=0;
    float difficoltaMax=0.0;
    combinazione_elementi *soluzione,*categoria;
    categoria=caricaCategorie(&numCat,"elementi.txt");
    soluzione=malloc(numCat*sizeof(struct comb));
    printf("Qual è la difficolta massima che vuoi per il tuo programma al corpo libero? ");
    scanf("%f",&difficoltaMax);
    for(int k=0;k<numCat;k++){
        printf("\nCategoria: %s\n",(categoria+k)->nomeCategoria);
        combinaElementi((categoria+k),(soluzione+k));
    }
#ifndef DBG2
    printf("Soluzione con punteggi piu alti:\n");
    for(int i=0;i<numCat;i++){
        for(int k=0;k<soluzione[i].numElementi;k++){
        printf("%s\n",soluzione[i].elenco[k].nome);
        }
    }
#endif
    while(!soluzioneValida(soluzione,difficoltaMax,numCat) && cntR<numCat){
        p=cercaPeggiore(soluzione,numCat);
        ricombina(categoria[p],soluzione[p]);//cerca peggiore cerca la categoria che ha la combinazione di elementi con il rapporto difficolta punteggio piu basso
        cntR++;
    }
    stampa(soluzione,numCat);
    return 0;
}

combinazione_elementi* caricaCategorie(int *numCat,char nomeFile[]){
    int i=0,k=0;
    combinazione_elementi *cat=NULL;
    FILE *fin=NULL;
    fin = fopen(nomeFile,"r");
    fscanf(fin,"%d",numCat);
    cat=malloc((*numCat)*sizeof(struct comb));
    while(i<*numCat){

        fscanf(fin,"%s %d %d %d",cat[i].nomeCategoria,&cat[i].numElementi,&cat[i].minElementi,&cat[i].maxElementi);
#ifndef DBG1
        printf("Nome categoria: %s\n",cat[i].nomeCategoria);
#endif
        cat[i].elenco=malloc((cat[i].numElementi)*sizeof(struct el));
        k=0;
        while(k<cat[i].numElementi){
        fscanf(fin,"%s %f %f",cat[i].elenco[k].nome,&cat[i].elenco[k].punteggio,&cat[i].elenco[k].difficolta);
            k++;
        }
        i++;
    }
    fclose(fin);
    return cat;
}
void combinaElementi(combinazione_elementi *val,combinazione_elementi *sol){
    int k=0,dimMigl=0;
    elemento solTmp[val->numElementi];
    float rapportoDiffPunti=0.0;
    strcpy(sol->nomeCategoria,val->nomeCategoria);
    sol->elenco=malloc(((*val).maxElementi)*sizeof(struct el));
    for(k=(*val).minElementi;k<=(*val).maxElementi;k++){
        //fra tutte queste combinazioni prendo quella col punteggio piu alto
        comb_r(0,(*val).elenco,solTmp,&(sol->elenco),k,(*val).maxElementi,0,0,&rapportoDiffPunti,&dimMigl);
    }
    sol->numElementi=dimMigl;
    sol->rapportoDiffPunti=rapportoDiffPunti;
}
//IDEA MIGLIORE FORSE: calcolo ogni volta il rapporto difficolta punti, poi pero prendo tutte le combinazioni che mi diano i piu alti punteggi possibili e se sforo la difficolta complessiva nel main allora vado a ricalcolare la combinazione col rapporto peggiore andando ad ottimizzarne il rapporto difficolta punti
int comb_r(int pos,elemento *val,elemento *sol,elemento **migliore,int n,int k,int start, int count,float *rapportoDiffPunti,int *dimMigliore){
    int i=0;
    float totPunti=0.0,totDiff=0.0,totMigliore=0.0;
    if (pos >= k) {
        for (i=0; i<k; i++){
            totPunti+=sol[i].punteggio;
            totDiff+=sol[i].difficolta;
            totMigliore+=(*migliore)[i].punteggio;
            printf("%s ",sol[i].nome);
        }
        printf("\n");
        if(totPunti>totMigliore){
            (*migliore)=sol;
            *dimMigliore=k;
            *rapportoDiffPunti=(float)(totPunti)/(float)(totDiff);
        }
        return count+1;
    }
    for (i=start; i<n; i++) {
        sol[pos] = val[i];
        count = comb_r(pos+1, val, sol, migliore, n, k, start, count,rapportoDiffPunti,dimMigliore);
        start++;
    }
    
    return count;
}
void ricombina(combinazione_elementi val,combinazione_elementi sol){
    int k,dimMigl=0;
    elemento solTmp[val.numElementi];
    float rapportoDiffPunti=0.0;
    for(k=val.minElementi;k<=val.maxElementi;k++){
        //fra tutte queste combinazioni prendo quella col punteggio piu alto
        rComb_r(0,val.elenco,solTmp,sol.elenco,k,val.maxElementi,0,0,&rapportoDiffPunti,&dimMigl);
    }
    sol.numElementi=dimMigl;
    sol.rapportoDiffPunti=rapportoDiffPunti;
}
int rComb_r(int pos,elemento *val,elemento *sol,elemento *migliore,int n,int k,int start, int count,float *rapportoDiffPunti,int *dimMigliore){
    int i=0;
    float totPunti=0.0,totDiff=0.0,rDiffParziale;
    if (pos >= k) {
        for (i=0; i<k; i++){
            totPunti+=sol[i].punteggio;
            totDiff+=sol[i].difficolta;
        }
        rDiffParziale=(float)(totPunti)/(float)(totDiff);
        if(rDiffParziale>(*rapportoDiffPunti)){
            migliore=sol;
            *dimMigliore=k;
            *rapportoDiffPunti=rDiffParziale;
        }
        return count+1;
    }
    for (i=start; i<n; i++) {
        sol[pos] = val[i];
        count = rComb_r(pos+1, val, sol, migliore, n, k, start, count,rapportoDiffPunti,dimMigliore);
        start++;
    }
    
    return count;
}

int soluzioneValida(combinazione_elementi *soluzione, int diffMax,int numCat){
    int k;
    float tot=0.0;
    for(k=0;k<numCat;k++){
        for(int i=0;i<soluzione[k].numElementi;k++){
            tot+=soluzione[k].elenco[i].difficolta;
        }
    }
    
    if(tot>diffMax){
        return 0;
    }
    else{
        return 1;
    }
}


int cercaPeggiore(combinazione_elementi soluzione[], int numCat){
    int k,indicePeggiore=0;
    for(k=1;k<numCat;k++){
        if(soluzione[k].rapportoDiffPunti<soluzione[indicePeggiore].rapportoDiffPunti){
            indicePeggiore=k;
        }
    }
    return indicePeggiore;
}



void stampa(combinazione_elementi soluzione[], int numCat){
    float diffTot=0.0;
    printf("La soluzione è: \n");
    for(int k=0;k<numCat;k++){
        printf("Categoria:\n");
        for(int i=0;i<soluzione[k].numElementi;k++){
            printf("\t\t\t %s\n",soluzione[k].elenco[i].nome);
            diffTot+=soluzione[k].elenco[i].difficolta;
        }
        printf("\n");
    }
    printf("Difficolta totale: %.2f",diffTot);
    printf("\n");
}





