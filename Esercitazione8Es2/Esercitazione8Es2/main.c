//
//  main.c
//  Esercitazione8Es2
//
//  Created by apple on 30/11/16.
//  Copyright © 2016 emag. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include "ingredienti.h"
#include "ricette.h"
void stampaMenu();
typedef  enum{
    c_stamparic, c_stampaing, c_costo, c_apporto, c_stampacompletor, c_stampacompletoi,c_stamparicingr,c_addric,stop,c_err
}comando_m;
comando_m leggiComando(char input[]);
int main(int argc, const char * argv[]) {
    int size=0;
    char inputUtente[21],nomeFileR[256],nomeFileI[256];
    FILE *fin=NULL;
    ElencoIngredienti ingredienti;
    ElencoRicette ricette;
    comando_m comando=c_err;
    strcpy(nomeFileI, argv[1]);
    strcpy(nomeFileR, argv[2]);
    fin=fopen(nomeFileI,"r");
    if(fin!=NULL){
        fscanf(fin,"%d",&size);
        fclose(fin);
        ingredienti=new_elencoIngredienti(size);
        caricaIngredientiDaFile(ingredienti, nomeFileI);
        ricette=caricaRicettaDaFile(nomeFileR, ingredienti);
        stampaElencoCompletoRicette(ricette,ingredienti);
        while(comando!=stop){
            do{
                stampaMenu();
                scanf("%s",inputUtente);
                comando=leggiComando(inputUtente);
                if(comando==c_err){printf("\tComando non valido inseriscine un altro\n");}
            }while(comando==c_err);
            switch(comando){
                case 0:
                    printf("Inserisci il nome della ricetta che vuoi stampare: ");
                    scanf("%s",inputUtente);
                    stampaRicetta(ricette, ingredienti, inputUtente);
                    break;
                case 1:
                    printf("Inserisci il nome dell ingrediente: ");
                    scanf("%s",inputUtente);
                    stampaIngrediente(ingredienti, cercaIngredienti(ingredienti, inputUtente));
                    break;
                case 2:
                    printf("Inserisci il nome della ricetta: ");
                    scanf("%s",inputUtente);
                    printf("\t\t\t Costo: %.2f\n",getCostoRicetta(ricette,ingredienti,inputUtente));
                    break;
                case 3:
                    printf("Inserisci il nome della ricetta: ");
                    scanf("%s",inputUtente);
                    printf("\t\t\t Apporto: %.2f\n",getApportoRicetta(ricette,ingredienti,inputUtente));
                    break;
                case 4:
                    stampaElencoCompletoRicette(ricette,ingredienti);
                    break;
                case 5:
                    stampaElencoCompletoIngredienti(ingredienti);
                    break;
                case 6:
                    printf("Inserisci il nome dell ingrediente: ");
                    scanf("%s",inputUtente);
                    stampaRicetteConIngrediente(ricette, ingredienti, inputUtente);
                    break;
                case 7:
                    aggiungiRicetta(ricette, ingredienti);
                    break;
                default:
                    break;
            }
            //eseguiComando(comando);
        }
    }
    else{
        printf("Il modulo degli ingredienti non è stato caricato correttamente\n");
    }
    liberaIngredienti(ingredienti);
    //liberaRicette(ricette);
    printf("Programma terminato\n");
    return 0;
}

void stampaMenu(){
    printf("stamparic - stampa dei dettagli di una ricetta\n stampaingr - stampa dei dettagli di un ingrediente\n calcolacosto - calcolo del costo di una ricetta\ncalcapporto - calcolo dell’apporto calorico di una ricetta\nstampaelencoric - stampa dell’intero elenco di ricette\nstampaelencoing - stampa dell’intero elenco di ingredienti\nstamparicing - stampa dell’elenco di ricette in cui sia presente un dato ingrediente\nnuovaric - introduzione (e memorizzazione) di una nuova ricetta (usando solo ingredienti già disponibili in elenco)\nstop- termina il programma\n");
}

comando_m leggiComando(char input[]){
char*tabellaComandi[stop]={"stamparic","stampaingr","calcolacosto","calcapporto","stampaelencoric","stampaelencoing","stamparicing","nuovaric"
    };
    for(int k=c_stamparic;k<=stop;k++){
        if(k!=stop){
        if(strcmp(input,tabellaComandi[k])==0){
            return k;
            }
        }
        else{
            return stop;
        }
    }
    return c_err;
}