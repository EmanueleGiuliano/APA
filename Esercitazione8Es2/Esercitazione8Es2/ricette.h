//
//  ricette.h
//  Esercitazione8Es2
//
//  Created by apple on 30/11/16.
//  Copyright © 2016 emag. All rights reserved.
//

#ifndef ricette_h
#define ricette_h

#include <stdio.h>
#include "ingredienti.h"

typedef struct ricetta *Ricetta;
typedef struct elencoRicette{
    Ricetta head;
} ElencoRicette;

ElencoRicette cercaRicetta(ElencoRicette elenco, char chiave[]);
ElencoRicette caricaRicettaDaFile(char nomefile[],ElencoIngredienti ingredienti);
void aggiungiRicetta(ElencoRicette elenco, ElencoIngredienti ingredienti);
void stampaRicetta(ElencoRicette elenco,ElencoIngredienti ingredienti, char chiave[]);
float getCostoRicetta(ElencoRicette elenco, ElencoIngredienti ingredienti, char chiave[]);
int getMinutiRicetta(ElencoRicette elenco, char chiave[]);
float getApportoRicetta(ElencoRicette elenco,ElencoIngredienti ingredienti, char chiave[]);
char* getNomeRicetta(ElencoRicette elenco,int pos);
void liberaRicette(ElencoRicette elenco);
void stampaElencoCompletoRicette(ElencoRicette elenco, ElencoIngredienti ingredienti);
void stampaRicetteConIngrediente(ElencoRicette elenco, ElencoIngredienti ingredienti,char chiave[]);
#endif /* ricette_h */
