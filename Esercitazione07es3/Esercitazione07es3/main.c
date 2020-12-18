//
//  main.c
//  Esercitazione07es3
//
//  Created by apple on 26/11/16.
//  Copyright © 2016 emag. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ingredienti.h"
#define DBG = 1
//STRUTTURE DATI DEL CLIENT
typedef struct ricetta{
    char nome[21];
    int minuti;// tempo di preparazione
    ElencoIngredienti ingredientiRicetta;
}Ricetta;

typedef struct elencoRicette{
    Ricetta* elenco[50];
} ElencoRicette;

//PROTOTIPI
ElencoRicette new_elencoRicette(int n);
Ricetta* acquisisciRicetta(ElencoIngredienti ingredienti);
void stampaMenu();
void stampaValori();
//CLIENT DI ingredienti.h
int main(int argc, const char * argv[]) {
    int risposta=1;
    int numIngredienti=0,k=-1;
    ElencoIngredienti ingredienti;
    //ElencoIngredienti daStampare;
    ElencoRicette ricette;
    FILE *fin=NULL;
    fin=fopen("ingredienti.txt","r");
    fscanf(fin,"%d",&numIngredienti);
    fclose(fin);
    ingredienti=new_elencoIngredienti(numIngredienti);//istanzia un nuovo elenco ingredienti
    caricaIngredientiDaFile(ingredienti,"ingredienti.txt");//popola l elenco da file
    ricette=new_elencoRicette(10);//istanzia un elenco ricette
    while(risposta!=0){
        stampaMenu();//pensato perche in futuro magari si decidera di inserire un menu e richiamare diverse funzioni sulle ricette a seconda di cosa sceglie l utente
        k++;
        ricette.elenco[k]=acquisisciRicetta(ingredienti);//ha bisogno di un elenco ingredienti come parametro
        stampaValori(ricette.elenco[k]);
        printf("Vuoi inserire un altra ricetta? 1-->Sì 0-->No\n");
        fflush(stdin);
        scanf("%d",&risposta);
        fflush(stdin);
    }
    libera(ingredienti);
    for(int i=0;i<k;i++){
        libera(ricette.elenco[k]->ingredientiRicetta);
        free(ricette.elenco[k]);
    }
    return 0;
}

//PROCEDURE E FUNZIONI
ElencoRicette new_elencoRicette(int n){
    ElencoRicette tmp;
    for(int k=0;k<n;k++){
        tmp.elenco[k]=malloc(sizeof(struct ricetta));
    }
    return tmp;
}
void stampaMenu(){
    printf("\t\tInserisci i dati di una ricetta(nome,tempo di preparazione ed elenco ingredienti)\n");
    return;
}
Ricetta* acquisisciRicetta(ElencoIngredienti ingredienti){
    char nome[21],ingrediente[21];
    int minuti=0,numIngredienti=0;
    Ricetta* ricetta=NULL;
    ElencoIngredienti daAggiungere;
    ricetta=malloc(sizeof(struct ricetta));
    ricetta->ingredientiRicetta=new_elencoIngredienti(10);
    printf("\t\tInserisci il nome: ");
    scanf("%s",nome);
    printf("\n");
    printf("\t\tInserisci il tempo di preparazione: ");
    scanf("%d",&minuti);
    printf("\n");
    printf("\t\tQuanti ingredienti servono in questa ricetta?  ");
    scanf("%d",&numIngredienti);
    printf("\n");
    strcpy(ricetta->nome,nome);
    ricetta->minuti=minuti;
    for(int j=0;j<numIngredienti;j++){
        printf("\t\t\tInserisci il %d°ingrediente: ",(j+1));
        scanf("%s",ingrediente);
        daAggiungere=cercaIngredienti(ingredienti,ingrediente);
        if(daAggiungere.head==NULL){
            printf("\t\t\tIngrediente non presente nell elenco ingredienti\n");
        }
        else{
            aggiungiIngrediente(ricetta->ingredientiRicetta,daAggiungere);
        }
    }
    return ricetta;
}

void stampaValori(Ricetta* ricetta){
    float costoComplessivo=0;
    float apportoComplessivo=0;
    ElencoIngredienti elencoI;
    //scorro la lista degli ingredienti, sommo e stampo
    elencoI=ricetta->ingredientiRicetta;
    while(getNome(elencoI)!=NULL){
        costoComplessivo+=getCosto(elencoI);
        apportoComplessivo+=getApporto(elencoI);
        elencoI=elementoSuccessivo(elencoI);
    }
    printf("\t\t\tApporto complessivo: %.2f costo complessivo %.2f\n",apportoComplessivo,costoComplessivo);
}