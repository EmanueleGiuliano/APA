//
//  ingredienti.h
//  Esercitazione07es3
//
//  Created by apple on 26/11/16.
//  Copyright © 2016 emag. All rights reserved.
//

#ifndef ingredienti_h
#define ingredienti_h

typedef struct ingrediente *Ingrediente;//ADT di prima classe
typedef struct elencoIngredienti{//NB: il client avrà la possibilità di vedere solo questo e non potra utilizzare ingrediente e basta
    Ingrediente head;//testa della lista
} ElencoIngredienti;//nasconde un puntatore

ElencoIngredienti new_elencoIngredienti(int n);
ElencoIngredienti cercaIngredienti(ElencoIngredienti elenco, char chiave[]);
void caricaIngredientiDaFile(ElencoIngredienti elenco, char nomefile[]);
void aggiungiIngrediente(ElencoIngredienti elencoIn,ElencoIngredienti elencoOut);
void stampaIngrediente(ElencoIngredienti elenco);
ElencoIngredienti elementoSuccessivo(ElencoIngredienti elenco);//restituisce il successivo elemento dell elenco fino a quando ce ne sono
float getCosto(ElencoIngredienti elenco);
float getApporto(ElencoIngredienti elenco);
char* getNome(ElencoIngredienti elenco);
void libera(ElencoIngredienti elenco);
#endif /* ingredienti_h */
