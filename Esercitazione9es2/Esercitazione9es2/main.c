//
//  main.c
//  Esercitazione9es2
//
//  Created by apple on 13/12/16.
//  Copyright © 2016 emag. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "Item.h"
#include "PQ.h"

typedef enum {
    c_stampa,c_inserisci,c_elimina,c_evolvi,c_carica,c_salva,c_fine
}comando_t;


comando_t leggiComando();
void strToLower(char s[],long int dim);
void stampaMenu();
void caricaCoda();
void salvaSuFile();
void evolvi();
int main(int argc, const char * argv[]) {
    Item tmp;
    //caricaCoda();
    comando_t cmd=c_carica;
    while(cmd!=c_fine){
        switch(cmd){
            case 0:
                PQdisplay();
                break;
            case 1:
                printf("Inserisci nome e punti:\n");
                tmp=ITEMscan();
                PQinsert(tmp);
                break;
            case 2:
                printf("Inserisci nome e punti:\n");
                tmp=ITEMscan();
                PQdelete(tmp);
                break;
            case 3:
                evolvi();
                break;
            case 4:
                caricaCoda();
                break;
            case 5:
                salvaSuFile();
                break;
            default:
                printf("\t\t\t!!Comando non riconosciuto\n");
                break;
        }
        cmd=leggiComando();
    }
    printf("Programma terminato\n");
    return 0;
}

void evolvi(){
    Item x1,x2;
    int r;
    float sott,punti1,punti2;
    r = rand() < RAND_MAX/2;
    printf("\t\tEsito: %d\n",r);
    //estrae i primi due elementi
    x1=PQextractMax();
    x2=PQextractMax();
    punti1=ITEMgetPti(x1);
    punti2=ITEMgetPti(x2);
    if(r==0){//vince x1
        sott=((punti2*25)/100);
        ITEMsetPti(&x1, (punti1+=sott));
        ITEMsetPti(&x2, (punti2-=sott));
    }
    if(r==1){//vince x2
        sott=((punti1*25)/100);
        ITEMsetPti(&x1, (punti1-=sott));
        ITEMsetPti(&x2, (punti2+=sott));
    }
    PQinsert(x1);
    PQinsert(x2);
    
    if(ITEMgetPti(x1)<5){
        PQdelete(x1);
        printf("\t\t%s è fuori dal torneo!!\n",x1.name);
    }
    
    if(ITEMgetPti(x2)<5){
        PQdelete(x2);
        printf("\t\t%s è fuori dal torneo!!\n",x2.name);
    }
}

void caricaCoda(){
    FILE *fin=NULL;
    Item tmp;
    char nomeFile[26];
    printf("Inserisci il nome del file da cui vuoi caricare: ");
    scanf("%s",nomeFile);
    printf("\n");
    fin=fopen(nomeFile,"r");
    if(fin==NULL){
        printf("\t\tNon e stato possibile caricare il file, controlla di aver inserito correttamente il nome\n");
        return;
    }
    else{
        tmp=ITEMread(fin);
        while(!ITEMcheckvoid(tmp)){
            PQinsert(tmp);
            tmp=ITEMread(fin);
        }
    }
    fclose(fin);
    return;
}



void salvaSuFile(){
    FILE *fout=NULL;
    Item tmp;
    char nomeFile[26];
    printf("Inserisci il nome del file su cui vuoi salvare: ");
    scanf("%s",nomeFile);
    printf("\n");
    fout=fopen(nomeFile,"w");
    while(!PQempty()){
        tmp=PQextractMax();
        ITEMprint(tmp, fout);
    }
    fclose(fout);
}


comando_t leggiComando(){
    comando_t comando=c_fine;//inizializzo a fine, se poi il comando e un altro non termino se no restituisco fine
    char lettura[26];//usciva il sigabrt perchè andavo a sovrascrivere un area di memoria che non dovevo siccome "lettura" era di dimensione giusta giusta, la soluzione e' stata ingrandire la stringa
    char *tabellaComandi[c_fine]={
        "stampa","inserisci","elimina","evolvi","carica","salva"
    };
    stampaMenu();
    fflush(stdin);//pulisco il buffer
    scanf("%s",lettura);
    strToLower(lettura,strlen(lettura));
    comando=c_stampa;//parte da 0(ricorda equivalenza enum-->0,1,2,3...
    while(comando<c_fine && strcmp(lettura,tabellaComandi[comando])!=0){//scorro i comandi alla ricerca di una corrispondenza con la str immessa
        comando++;
    }
    return comando;
}






void strToLower(char s[],long int dim){
    int j;
    for(j=0;j<dim;j++){
        s[j]=tolower(s[j]);
    }
}








void stampaMenu(){
    printf("\nElenco comandi:(scegli cosa vuoi fare)\n");
    printf("stampa - stampa la classifica\n");
    printf("inserisci - inserisci un nuovo partecipanteo\n");
    printf("elimina - elimina un partecipante\n");
    printf("evolvi - fai evolvere la classifica generando una sfida\n");
    printf("carica - carica l elenco partecipanti da file\n");
    printf("salva - stampa su file l elenco partecipantio\n");
}