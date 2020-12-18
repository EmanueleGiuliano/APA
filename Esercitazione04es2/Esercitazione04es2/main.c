//
//  main.c
//  Esercitazione04es2
//
//  Created by apple on 09/11/16.
//  Copyright © 2016 emag. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
//STRUTTURE

//PROTOTIPI
int** malloc2dr(int *nr, int *nc);
int** generaDiagonali(int **m, int *numeroDiagonali,int *diagPrincipale,int nr,int nc);//restituisce il numero di diagonali della matrice come return
int** generaAntidiagonali(int **m, int *numeroDiagonali, int *diagPrincipale,int nr, int nc);
void stampa(int *v[],int dim, int elDiagonale);
void liberaMemoria(int **v,int dim);
//MAIN
int main(int argc, const char * argv[]) {
    int **matrice,nr,nc,**diagonali,**antidiagonali,numDiagonali=0,diagPrincipale=0;
    matrice=malloc2dr(&nr, &nc);
    printf("Diagonali:\n");
    diagonali=generaDiagonali(matrice,&numDiagonali,&diagPrincipale,nr,nc);
    stampa(diagonali, numDiagonali,diagPrincipale);
    liberaMemoria(diagonali,numDiagonali);
    printf("Antidiagonali:\n");
    antidiagonali=generaAntidiagonali(matrice,&numDiagonali,&diagPrincipale,nr,nc);
    stampa(diagonali, numDiagonali,diagPrincipale);
    liberaMemoria(diagonali,numDiagonali);
    return 0;
}
//PROCEDURE E FUNZIONI
int** malloc2dr(int *nr, int *nc){
    int** m,k,j;
    FILE *fin;
    fin=fopen("matrice.txt","r");
    if(fin!=NULL){
        fscanf(fin,"%d %d",nr,nc);
        m=(int**)malloc((*nr)*sizeof(int*));//alloco nr puntatori
        for(k=0;k<*nr;k++){
            m[k]=(int*)malloc((*nc)*sizeof(int));//alloco dinamicamente nr vettori di nc*int
        }
        //carico i valori nella matrice
        for(k=0;k<*nr;k++){
            for(j=0;j<*nc;j++){
                fscanf(fin,"%d",(m[k]+j));
            }
        }
    }
    else{
        printf("\nerrore nell' apertura del file\n");
    }
    fclose(fin);
    return m;
}

int** generaAntidiagonali(int **m, int *numeroDiagonali, int *diagPrincipale,int nr, int nc){
    int r,c,j,u=0,k,elDiagonale=0,dimVett=0,medio=0;
    int **v;//vettore delle diagonali
    for(r=0;r<nr;r++){//conto gli elementi della diagonale principale
        for(c=0;c<nc;c++){
            if(c==r){
                elDiagonale++;
            }
        }
    }
    
    //conteggio numero di puntatori necessari nel vettore che conterra le diagonali
    dimVett=(elDiagonale*2)-1;//sono tutti doppi tranne la diagonale principale
    
    v=(int**)malloc(dimVett*sizeof(int*));//alloco un vettore di dimvett puntatori
    medio=(dimVett-1)/2;//elemento di metà vettore
    
    v[medio]=(int*) malloc(elDiagonale*sizeof(int));//alloco il vettore della diagonale principale come elemento centrale
    //allocazione diagonali sopra la principale
    for(j=medio-1,c=1;c<nc && j>=0;c++){//sopra la diag
        v[j]=(int*) malloc((elDiagonale-c)*sizeof(int));
        j--;//vado sempre piu verso l inizio del vettore e la dimensione delle diagonali da contenere decresce(eldiagonale-c)
    }
    
    for(j=medio+1,r=1;r<nr && j<dimVett;r++){//alloco quelli sotto la diagonale principale
        v[j]=(int*) malloc((elDiagonale-r)*sizeof(int));
        j++;
    }
    
    
    //FINE ALLOCAZIONE INIZIO CARICAMENTO VETTORE
    
    for(r=0,j=0,u=0,k=1,c=0;c<nc;c++){
        v[j][u]=m[r][c];
        u++;
        while((c-k)>=0 && (r+k)<nr){//continua, se ce a prendere l elemento sotto a destra
            v[j][u]=m[r+k][c-k];
            k++;
            u++;
        }
        j++;//passo alla diagonale successiva
        u=0;
        k=1;
    }
    
    for(r=1,j=medio+1,u=0,k=1,c=(nc-1);r<nr;r++){
        v[j][u]=m[r][c];
        u++;
        while((c-k)>=0 && (r+k)<nr){//continua, se ce a prendere l elemento sotto a destra
            v[j][u]=m[r+k][c-k];
            k++;
            u++;
        }
        j++;//passo alla diagonale successiva
        u=0;
        k=1;
    }
    
    
    
    *numeroDiagonali=dimVett;
    *diagPrincipale=elDiagonale;
    return v;
    
}

int** generaDiagonali(int **m, int *numeroDiagonali, int *diagPrincipale,int nr, int nc){
    int r,c,j,u=0,k,elDiagonale=0,dimVett=0,medio=0;
    int **v;//vettore delle diagonali
    for(r=0;r<nr;r++){//conto gli elementi della diagonale principale
        for(c=0;c<nc;c++){
            if(c==r){
                elDiagonale++;
            }
        }
    }
    
    //conteggio numero di puntatori necessari nel vettore che conterra le diagonali
    dimVett=(elDiagonale*2)-1;//sono tutti doppi tranne la diagonale principale
    
    v=(int**)malloc(dimVett*sizeof(int*));//alloco un vettore di dimvett puntatori
    medio=(dimVett-1)/2;//elemento di metà vettore
    
    v[medio]=(int*) malloc(elDiagonale*sizeof(int));//alloco il vettore della diagonale principale come elemento centrale
    //allocazione diagonali sopra la principale
    for(j=medio-1,c=1;c<nc && j>=0;c++){//sopra la diag
        v[j]=(int*) malloc((elDiagonale-c)*sizeof(int));
        j--;//vado sempre piu verso l inizio del vettore e la dimensione delle diagonali da contenere decresce(eldiagonale-c)
    }
    
    for(j=medio+1,r=1;r<nr && j<dimVett;r++){//alloco quelli sotto la diagonale principale
        v[j]=(int*) malloc((elDiagonale-r)*sizeof(int));
        j++;
    }
    
    
    //FINE ALLOCAZIONE INIZIO CARICAMENTO VETTORE
    
    for(r=0,j=0,u=0,k=1,c=(nc-1);c>=0;c--){
        v[j][u]=m[r][c];
        u++;
        while((c+k)<nc && (r+k)<nr){//continua, se ce a prendere l elemento sotto a destra
            v[j][u]=m[r+k][c+k];
            k++;
            u++;
        }
        j++;//passo alla diagonale successiva
        u=0;
        k=1;
    }
    
    for(r=1,j=medio+1,u=0,k=1,c=0;r<nr;r++){
        v[j][u]=m[r][c];
        u++;
        while((c+k)<nc && (r+k)<nr){//continua, se ce a prendere l elemento sotto a destra
            v[j][u]=m[r+k][c+k];
            k++;
            u++;
        }
        j++;//passo alla diagonale successiva
        u=0;
        k=1;
    }
    
    
    
    *numeroDiagonali=dimVett;
    *diagPrincipale=elDiagonale;
    return v;
    
}

void liberaMemoria(int **v,int dim){
    int j;
    for(j=0;j<dim;j++){//libero la memoria
        free(v[j]);
    }
    free(v);
}
void stampa(int **v,int dim, int elDiagonale){
    int k,j,u,stampadiag=0;
    for(k=0,u=elDiagonale-1;k<dim;k++){
        printf("\tDiagonale numero: %d\n",k);
        printf("\t\t\t\t\t\t");
        for(j=0;j<elDiagonale-u;j++){
            printf("%d ",v[k][j]);
        }
        if(j==elDiagonale){
            stampadiag=1;
        }
        if(stampadiag==0){
            u--;
        }
        else if(stampadiag==1){
            u++;
        }
        
        printf("\n");
    }
}