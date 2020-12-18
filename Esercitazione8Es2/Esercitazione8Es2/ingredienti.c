//
//  ingredienti.c
//  Esercitazione07es3
//
//  Created by apple on 26/11/16.
//  Copyright © 2016 emag. All rights reserved.
//

#include "ingredienti.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
//#define DBG = 1
struct ingrediente{
    char nome[21];
    float costo;
    float apportoCalorico;
};

ElencoIngredienti new_elencoIngredienti(int n){
    ElencoIngredienti tmp;
    tmp.dimensioneElenco=n;
    for(int i=0;i<n;i++){
        tmp.elenco[i]=malloc(sizeof(struct ingrediente));
    }
    return tmp;
}

int cercaIngredienti(ElencoIngredienti elenco, char chiave[]){//returna la posizione dove ha trovato l ingrediente
    int k=0,pos=-1;
    while(k<elenco.dimensioneElenco){
        if(strcmp(elenco.elenco[k]->nome,chiave)==0){
            pos=k;
            k=elenco.dimensioneElenco;//forza l uscita dal ciclo
        }
        k++;
    }
    return pos;
}
void aggiungiIngrediente(ElencoIngredienti elenco){
    Ingrediente x=NULL;
    x=malloc(sizeof(struct ingrediente));
    elenco.dimensioneElenco++;
    elenco.elenco[elenco.dimensioneElenco-1]=x;
    
}
void stampaIngrediente(ElencoIngredienti elenco, int posizione){
    printf("\t\t%s - Costo: %f Apporto calorico: %f\n",elenco.elenco[posizione]->nome,elenco.elenco[posizione]->costo,elenco.elenco[posizione]->apportoCalorico);
}

void liberaIngredienti(ElencoIngredienti elenco){
    int k=0;
    while(k<elenco.dimensioneElenco){
        free(elenco.elenco[k]);//libero le strutture
        k++;
    }
}

char* getNomeIngrediente(ElencoIngredienti elenco, int pos){
    return (elenco.elenco[pos])->nome;
}

/*ElencoIngredienti elementoSuccessivo(ElencoIngredienti elenco){
    ElencoIngredienti succ;
    succ.head=(elenco.head)->next;
    return succ;
}*/
float getCosto(ElencoIngredienti elenco, int pos){
    return elenco.elenco[pos]->costo;
}
float getApporto(ElencoIngredienti elenco, int pos){
    return elenco.elenco[pos]->apportoCalorico;
}
void caricaIngredientiDaFile(ElencoIngredienti elenco, char nomeFile[]){
    FILE *fin=NULL;
    char nome[21];
    float costo=0.0;
    float apporto=0.0;
    int numeroIngredienti=0,i=0;
    fin=fopen(nomeFile, "r");
    if(fin==NULL){
        printf("\t\tIl modulo ingredienti.h non è riuscito ad aprire il file che hai specificato, controlla di aver inserito il nome correttamente\n");
    }
    else{
        fscanf(fin,"%d",&numeroIngredienti);
        while(fscanf(fin,"%s %f %f",nome,&costo,&apporto)==3 && i<numeroIngredienti){
            elenco.elenco[i]->apportoCalorico=apporto;
            elenco.elenco[i]->costo=costo;
            strcpy(elenco.elenco[i]->nome,nome);
            i++;
        }
        elenco.dimensioneElenco=numeroIngredienti;
    fclose(fin);
    }
}

void stampaElencoCompletoIngredienti(ElencoIngredienti elenco){
    printf("Elenco di tutti gli ingredienti caricati in memoria:\n");
    for(int k=0;k<elenco.dimensioneElenco;k++){
        printf("\t%s - Apporto:%f Costo:%f\n",elenco.elenco[k]->nome,elenco.elenco[k]->apportoCalorico,elenco.elenco[k]->costo);
    }
}