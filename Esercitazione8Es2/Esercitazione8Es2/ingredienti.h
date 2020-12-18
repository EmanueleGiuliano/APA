//
//  ingredienti.h
//  Esercitazione07es3
//
//  Created by apple on 26/11/16.
//  Copyright © 2016 emag. All rights reserved.
//

#ifndef ingredienti_h
#define ingredienti_h

typedef struct ingrediente *Ingrediente;
typedef struct elencoIngredienti{//NB: il client avrà la possibilità di vedere solo questo e non potra utilizzare ingrediente e basta
    Ingrediente *elenco;
    int dimensioneElenco;
} ElencoIngredienti;//nasconde un puntatore

ElencoIngredienti new_elencoIngredienti(int n);
int cercaIngredienti(ElencoIngredienti elenco, char chiave[]);
void caricaIngredientiDaFile(ElencoIngredienti elenco, char nomefile[]);
void aggiungiIngrediente(ElencoIngredienti elenco);
void stampaIngrediente(ElencoIngredienti elenco, int posizione);
//ElencoIngredienti elementoSuccessivo(ElencoIngredienti elenco);//restituisce il successivo elemento dell elenco fino a quando ce ne sono
float getCosto(ElencoIngredienti elenco,int pos);
float getApporto(ElencoIngredienti elenco, int pos);
char* getNomeIngrediente(ElencoIngredienti elenco,int pos);
void liberaIngredienti(ElencoIngredienti elenco);
void stampaElencoCompletoIngredienti(ElencoIngredienti elenco);
#endif /* ingredienti_h */
