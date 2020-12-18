//
//  ricette.c
//  Esercitazione8Es2
//
//  Created by apple on 30/11/16.
//  Copyright © 2016 emag. All rights reserved.
//

#include "ricette.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
typedef struct ingredRicetta *IngredRicetta;
 struct ingredRicetta{
    int grammi;
    int indice_ingrediente;
    IngredRicetta next;
};
 struct ricetta{
    char nome[21];
    int minuti;// tempo di preparazione
    IngredRicetta elencoIngredienti;//lista concatenata di indici corrispondenti agli ingredienti nel vettore ingredienti
    Ricetta next;
 };
ElencoRicette cercaRicetta(ElencoRicette elenco, char chiave[]){
    Ricetta x=elenco.head;
    ElencoRicette ris;
    while(x!=NULL && strcmp(x->nome,chiave)!=0){
        x=x->next;
    }
    ris.head=x;
    return ris;
}
ElencoRicette caricaRicettaDaFile(char nomefile[], ElencoIngredienti ingredienti){
    ElencoRicette elenco;
    FILE *fin=NULL;
    int numRicette=0,numIngredientiRicetta=0,grammi=0,indiceIng=-1,j=0,tempoRicetta=0;
    char ingredienteBuffer[21],nomeRicetta[21];
    Ricetta tmph=NULL;
    Ricetta x=NULL;
    IngredRicetta ingr=NULL;
    IngredRicetta head=NULL;
    fin=fopen(nomefile,"r");
    fscanf(fin,"%d",&numRicette);
    while(fscanf(fin,"%s %d %d",nomeRicetta,&tempoRicetta,&numIngredientiRicetta)!=EOF && j<numRicette){
        x=malloc(sizeof(struct ricetta));
        x->minuti=tempoRicetta;
        strcpy(x->nome, nomeRicetta);
        for(int i=0;i<numIngredientiRicetta;i++){
            fscanf(fin,"%s %d",ingredienteBuffer,&grammi);
            if((indiceIng=cercaIngredienti(ingredienti, ingredienteBuffer))!=-1){
                ingr=malloc(sizeof(struct ingredRicetta));
                ingr->indice_ingrediente=indiceIng;
                ingr->grammi=grammi;
                if(i==0){
                    head=ingr;//assegno la testa della lista al campo della ricetta
                    x->elencoIngredienti=head;
                }
                else{
                    head->next=ingr;
                    head=ingr;
                }
                
            }
            else{
                printf("Errore nel caricamento del file, controlla che gli ingredienti che hai inserito nelle ricette siano presenti nel file delle elenco ingredienti\n");
                elenco.head=NULL;
                return elenco;//termina l esecuzione della funzione dopo aver restituito l errore
            }
            ingr->next=NULL;//assegna null al next dell ultimo ingrediente della ricetta
        }
        if(j==0){
            tmph=x;
            elenco.head=x;
        }
        else{
            tmph->next=x;
            tmph=x;
        }
        j++;
    }
    fclose(fin);
    tmph->next=NULL;//setto a null il puntatore al next dell ultimo in coda
    return elenco;
}

void aggiungiRicetta(ElencoRicette elenco, ElencoIngredienti ingredienti){
    char ingredienteBuffer[21];
    Ricetta x=elenco.head;
    Ricetta tmp=NULL;
    IngredRicetta head=NULL;
    IngredRicetta ingr=NULL;
    int numIngredienti=0,indiceIng=0,grammi=0;
    if(x->next!=NULL){
        while(x->next!=NULL){x=x->next;}
    }
    tmp=x->next;
    tmp=malloc(sizeof(struct ricetta));
    printf("Inserisci il nome: ");
    scanf("%s",tmp->nome);
    printf("Inserisci il tempo: ");
    scanf("%d",&(tmp->minuti));
    printf("Quanti ingredienti vuoi inserire? ");
    scanf("%d",&numIngredienti);
   
    for(int i=0;i<numIngredienti;i++){
        printf("Ingrediente n°%d ",i+1);
        scanf("%s",ingredienteBuffer);
        printf("\n\t\tgrammi:");
        scanf("%d",&grammi);
        if((indiceIng=cercaIngredienti(ingredienti, ingredienteBuffer))!=-1){
            ingr=malloc(sizeof(struct ingredRicetta));
            ingr->indice_ingrediente=indiceIng;
            ingr->grammi=grammi;
            if(i==0){
                head=ingr;//assegno la testa della lista al campo della ricetta
                tmp->elencoIngredienti=head;
            }
            else{
                head->next=ingr;
                head=ingr;
            }
            
        }
        else{
            printf("L ingrediente che hai inserito non è stato trovato, hai ancora %d ingredienti da inserire\n",numIngredienti-i);
        }
    }
    ingr->next=NULL;//assegna null al next dell ultimo ingrediente della ricetta
    x->next=tmp;
}

void stampaRicetta(ElencoRicette elenco,ElencoIngredienti ingredienti, char chiave[]){
    Ricetta x=elenco.head;
    IngredRicetta i=NULL;
    int tro=0;
    while(x!=NULL && !tro){
            if(strcmp(x->nome,chiave)==0){
                tro=1;
            }
            else{
                x=x->next;
            }
    }
    if(tro){
        printf("\n\t\t%s - Minuti: %d\n",x->nome,x->minuti);
        i=x->elencoIngredienti;
        while(i!=NULL){//stampa gli ingredienti della ricetta e i rispettivi grammi
            printf("\t\t\t%s - Grammi: %d\n",getNomeIngrediente(ingredienti, i->indice_ingrediente),i->grammi);
            i=i->next;
        }
    }
    else{
        printf("\n\t\t\tRicetta non trovata\n\n");
    }
}
float getCostoRicetta(ElencoRicette elenco, ElencoIngredienti ingredienti,char chiave[]){
    float ris=0.0;
    Ricetta x=elenco.head;
    IngredRicetta i=NULL;
    int tro=0;
    while(x!=NULL && !tro){
        if(strcmp(x->nome,chiave)==0){tro=1;}
        x=x->next;
    }
    if(tro){
        i=x->elencoIngredienti;
        while(i!=NULL){
            ris+=getCosto(ingredienti, i->indice_ingrediente);
            i=i->next;
        }
    }
    else{
        printf("\t\t/Ricetta non trovata\n;");
        return -1;
    }
    return ris;
}
int getMinutiRicetta(ElencoRicette elenco, char chiave[]){
    Ricetta x=elenco.head;
    int tro=0;
    while(x!=NULL && !tro){
        if(strcmp(x->nome,chiave)==0){tro=1;}
        x=x->next;
    }
    if(tro){
        return x->minuti;
    }
    else{
        printf("\t\t/Ricetta non trovata\n;");
        return -1;
    }
}
char* getNomeRicetta(ElencoRicette elenco,int pos){//si sposta nel pos esimo nodo della lista e restituisce il nome(costo lineare)
    Ricetta x=elenco.head;
    int k=0;
    while(x!=NULL && k<=pos){
        x=x->next;
        k++;
    }
    return x->nome;
}
void liberaRicette(ElencoRicette elenco){
    Ricetta x=elenco.head;
    Ricetta x2=NULL;
    IngredRicetta tmp=NULL;
    IngredRicetta tmp2=NULL;
    while(x!=NULL){
        tmp=elenco.head->elencoIngredienti;
        while(tmp!=NULL){//libera la lista di ingredienti
            tmp2=tmp;
            free(tmp);
            tmp=tmp2->next;
        }
        x2=x;
        free(x);
        x=x2->next;
    }
}
void stampaElencoCompletoRicette(ElencoRicette elenco, ElencoIngredienti ingredienti){
    Ricetta x=elenco.head;
    IngredRicetta ingr=NULL;
    while(x!=NULL){
        printf("\t\t\t%s - Tempo preparazione : %d\n",x->nome,x->minuti);
        ingr=x->elencoIngredienti;
        while(ingr!=NULL){
            printf("\t\t\t\t %s grammi %d\n",getNomeIngrediente(ingredienti, ingr->indice_ingrediente),ingr->grammi);
            ingr=ingr->next;
        }
        x=x->next;
    }
}


float getApportoRicetta(ElencoRicette elenco,ElencoIngredienti ingredienti, char chiave[]){
    Ricetta x=elenco.head;
    IngredRicetta i=NULL;
    int tro=0;
    float ris=0;
    while(x!=NULL && !tro){
        if(strcmp(x->nome,chiave)==0){tro=1;}
        x=x->next;
    }
    if(tro){
        i=x->elencoIngredienti;
        while(i!=NULL){
            ris+=getApporto(ingredienti, i->indice_ingrediente);
            i=i->next;
        }
    }
    else{
        printf("\t\tRicetta non trovata\n;");
        return -1;
    }
    return ris;
}

void stampaRicetteConIngrediente(ElencoRicette elenco, ElencoIngredienti ingredienti,char chiave[]){
    Ricetta x=elenco.head;
    IngredRicetta ingr=NULL;
    int tro=0,indiceChiave=-1;//indice chiave e l indice dell ingrediente da cercare
    indiceChiave=cercaIngredienti(ingredienti, chiave);
    if(indiceChiave!=-1){
        while(x!=NULL){
            ingr=x->elencoIngredienti;
            while(ingr!=NULL){
                if(ingr->indice_ingrediente==indiceChiave){
                    tro=1;
                }
                ingr=ingr->next;
            }
            if(tro){printf("\t\t\t%s - Tempo preparazione : %d\n",x->nome,x->minuti);tro=0;}
            x=x->next;
        }
    }
    else{
        printf("\t\tIngrediente non presente nell elenco ingredienti\n");
    }
}