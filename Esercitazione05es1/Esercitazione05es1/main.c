//
//  main.c
//  Esercitazione05es1
//
//  Created by apple on 12/11/16.
//  Copyright © 2016 emag. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
int hof(int N, int v[]);
int main(int argc, const char * argv[]) {
    int num ,*sequenza = NULL,i=0;
    printf("Quanti numeri di Hofstadter vuoi stampare?  ");
    scanf("%d",&num);
    while(num<0 && i<3){
        printf("Inserisci un numero maggiore di 0\n");
        i++;
    }
    if(num>0){
        sequenza=(int*)malloc(num*sizeof(int));//alloco un vettore di num interi
        sequenza[0]=1;
        sequenza[1]=1;
        for(int k=2;k<num;k++){
            sequenza[k]=0;//inizializza
        }
        hof(num,sequenza);
        printf("La sequenza di Hofstadter fino al %d° termine è:\n",num);
        for(int k=0;k<num;k++){
            printf("%d ",sequenza[k]);
        }
        printf("\n");
    }
   
    return 0;
}

int hof(int N, int v[]){
    int tmp=0;
    if(N==1 || N==2){
        return 1;
    }
    else{
        tmp=hof(N - hof((N - 1),v),v) + hof(N - hof((N - 2),v),v);
        if(v[N-1]==0){
            v[N-1]=tmp;
        }
        return(tmp);
    }
}
