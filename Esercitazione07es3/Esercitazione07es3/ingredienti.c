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
    Ingrediente next;
};

ElencoIngredienti new_elencoIngredienti(int n){
    
    Ingrediente head=NULL;
    Ingrediente x=NULL;
    Ingrediente p=NULL;
    ElencoIngredienti elenco;
    head=(Ingrediente)malloc(sizeof(struct ingrediente));
    head->costo=0.0;
    head->apportoCalorico=0.0;
    strcpy(head->nome, "ZZZZZZZZZZZZ");
    
    
    p=head;
    for(int i=0;i<n;i++){//alloca ed inizializza una lista concatenata di n elementi
        x=malloc(sizeof(struct ingrediente));
        x->costo=0.0;
        x->apportoCalorico=0.0;
        strcpy(x->nome, "ZZZZZZZZZZZZ");
        p->next=x;
        p=x;
        x=NULL;
    }
    
    elenco.head=head;
    return elenco;
}

ElencoIngredienti cercaIngredienti(ElencoIngredienti elenco, char chiave[]){
    Ingrediente x=elenco.head;
    ElencoIngredienti ris;
    while(x->next!=NULL && strcmp(x->nome,chiave)!=0){
            x=x->next;
    }
    if(strcmp(x->nome,"ZZZZZZZZZZZZ")==0){
        ris.head=NULL;
    }
    else{
        ris.head=x;
    }
    return ris;
}
void aggiungiIngrediente(ElencoIngredienti elencoIn,ElencoIngredienti elencoOut){
    Ingrediente x=NULL;
    x=elencoIn.head;
    while(x->next!=NULL && strcmp(x->nome,"ZZZZZZZZZZZZ")!=0){
        x=x->next;
    }
    
    if(strcmp(x->nome,"ZZZZZZZZZZZZ")==0){
        x->costo=(elencoOut.head)->costo;
        x->apportoCalorico=(elencoOut.head)->apportoCalorico;
        strcpy(x->nome, (elencoOut.head)->nome);
    }
    
}
void stampaIngrediente(ElencoIngredienti elenco){
    printf("\t\t\t\t\tNome:  %s\n",(elenco.head)->nome);
    printf("\t\t\t\t\tCosto: %.2f\n",(elenco.head)->costo);
    printf("\t\t\t\t\tApporto: %.2f\n",(elenco.head)->apportoCalorico);
    
}

void libera(ElencoIngredienti elenco){
    Ingrediente head=NULL;
    Ingrediente x=NULL;
    head=elenco.head;
    x=head->next;
    while(head!=NULL){
        free(head);
        head=x;
        if(x!=NULL){
            x=x->next;
        }
    }
}

char* getNome(ElencoIngredienti elenco){
    if(strcmp((elenco.head)->nome,"ZZZZZZZZZZZZ")==0){
        return NULL;
    }
    return (elenco.head)->nome;
}

ElencoIngredienti elementoSuccessivo(ElencoIngredienti elenco){
    ElencoIngredienti succ;
    succ.head=(elenco.head)->next;
    return succ;
}
float getCosto(ElencoIngredienti elenco){
    return elenco.head->costo;
}
float getApporto(ElencoIngredienti elenco){
    return elenco.head->apportoCalorico;
}
void caricaIngredientiDaFile(ElencoIngredienti elenco, char nomeFile[]){
    Ingrediente x=NULL;
    FILE *fin=NULL;
    fin=fopen(nomeFile, "r");
    if(fin==NULL){
        printf("\t\tIl modulo ingredienti.h non è riuscito ad aprire il file che hai specificato, controlla di aver inserito il nome correttamente\n");
    }
    else{
        char nome[21];
        float costo=0.0;
        float apporto=0.0;
        int numeroIngredienti=0,i=0;
        fscanf(fin,"%d",&numeroIngredienti);
        x=elenco.head;//parto dalla testa della lista per scorrerla
        while(fscanf(fin,"%s %f %f",nome,&costo,&apporto)==3 && i<=numeroIngredienti && x!=NULL){
            x->costo=costo;
            x->apportoCalorico=apporto;
            strcpy(x->nome, nome);
            x=x->next;
            i++;
        }
        if(i<numeroIngredienti){
            printf("\t\tIl file non è stato completamente caricato, controlla che il formato in cui è stato scritto sia corretto\n");
        }
    fclose(fin);
    }
}