//
//  main.c
//  Esercitazione05es2
//
//  Created by apple on 13/11/16.
//  Copyright © 2016 emag. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
int converti(int N,int b);
int main(int argc, const char * argv[]) {
    int N,b;
    printf("Inserisci il numero da convertire: ");
    scanf("%d",&N);
    printf("\nInserisci la base in cui convertirlo: ");
    scanf("%d",&b);
    while(b<2){
        printf("Inserisci una base maggiore o uguale a 2 ");
        scanf("%d",&b);
    }
    printf("Il risultato e':  ");
    printf("(");
    printf("%d",converti(N,b));//stampa il valore della funzione quando riemerge completamente nel main (ovvero il valore della prima chiamata di converti che è anche il valore dell ultima cifra del numero convertito(l'ultimo resto))
    printf(")..base %d..\n",b);
    return 0;
}

int converti(int N, int b){
    if((N/b)<1){
        return (N%b);
    }
    else{
        printf("%d ",converti((N/b), b));
        return (N%b);
    }
}