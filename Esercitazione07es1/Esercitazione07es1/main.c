//
//  main.c
//  Esercitazione07es1
//
//  Created by Emanuele Giuliano on 21/11/16.
//  Copyright © 2016 emag. All rights reserved.
//
#include <stdio.h>
#include <stdlib.h>
#define DBG = 1
#define CPYDBG = 1
#define SDBG = 1
#define SDBG = 1
#define RDBG = 1
#define SROTDBG = 1
int combInsiemi(int pos, int **val, int sol[][10], int n, int k, int start,int count,int insiemeCompleto[],int dimCompleto);
int rDicotomica(int v[], int l, int r, int chiave);
void cover(int **S, int n, int k);
int main(int argc, const char * argv[]) {
    int **sottoinsiemi,numeroSottoinsiemi=0, elemInsieme=0,j=0,buffer[10],elementiCover=0;
    FILE *fin=NULL;
    fin=fopen(argv[1],"r");
    fscanf(fin,"%d",&numeroSottoinsiemi);
    sottoinsiemi=(int**)malloc(numeroSottoinsiemi*sizeof(int*));
    while(j<numeroSottoinsiemi && buffer[elemInsieme-1]!=EOF){
        fscanf(fin,"%d",&buffer[elemInsieme++]);
        if(buffer[elemInsieme-1]==0){
            sottoinsiemi[j]=(int*)malloc(elemInsieme*sizeof(int));
            for(int k=0;k<elemInsieme;k++){
                sottoinsiemi[j][k]=buffer[k];
            }
            j++;
            elemInsieme=0;
        }
    }
    fclose(fin);
    do{
        printf("Con quanti elementi vuoi fare il set cover?  ");
        scanf("%d",&elementiCover);
        if(elementiCover>numeroSottoinsiemi){
            printf("\tNel file non sono presenti abbastanza sottoinsiemi\n\n");
        }
    }
    while(elementiCover>numeroSottoinsiemi);
    printf("\tSottoinsiemi:\n");
    for(int k=0;k<numeroSottoinsiemi;k++){
        printf("\t{");
        for(int j=0;sottoinsiemi[k][j]!=0;j++){
            printf(" %d",sottoinsiemi[k][j]);
        }
        printf(" }\n");
    }

    cover(sottoinsiemi,numeroSottoinsiemi,elementiCover);
    //deallocazione
    for(int i=0;i<numeroSottoinsiemi;i++){
     free(sottoinsiemi[i]);
     }
    free(sottoinsiemi);
    return 0;
}
/*LEGENDA:
 Comb insiemi
 
.n=numero di sottoinsiemi
.pos=indice di dove sono all interno di sol(mi dice quanto mi manca a costruire un possibile set cover che poi andra verificato)
.sol=matrice dei sottoinsiemi che sto scegliendo come soluzione
.val=matrice dei sottoinsiemi che ho ricevuto in input
.k=numero di sottoinsiemi con cui mi e stato richiesto di fare il set cover
.start=indice di partenza per andare a pescare nella matrice dei sottoinisiemi in input
.count=numero di soluzioni trovate
.insiemeCompleto=insieme finale su cui si sta facendo il set cover(ovvero che sto cercando di raggiungere attraverso la combinazione dei sottoinsiemi che mi sono stati forniti in input)
.dimCompleto=dimensione di questo insieme
 */
void cover(int **S, int n, int k){
    int trovata=0;
    int completo[9]={1,2,3,4,5,6,7,8,9},soluzioni[k][10];
    //inizializzazione soluzioni e stampa insieme completo
    for(int j=0;j<k;j++){
        for(int u=0;u<10;u++){
            soluzioni[j][u]=0;
        }
    }
    printf("\n\t\t...(Insieme iniziale:");
    for(int j=0;j<9;j++){
        printf(" %d ",completo[j]);
        
    }
    printf(")...\n\n");
    
    trovata=combInsiemi(0, S, soluzioni, n, k, 0,1 , completo, 9);
    if(trovata){
        printf("SET COVER:\n");
        for(int j=0;j<k;j++){
            printf("Insieme:\n");
            for(int i=0;soluzioni[j][i]!=0;i++){
                printf("%d",soluzioni[j][i]);
            }
            printf("\n");
        }
    }
    else{
        printf("Non esiste un set cover con k=%d con gli insiemi forniti in ingresso\n",k);
    }
}
int combInsiemi(int pos, int **val, int sol[][10], int n, int k, int start,int valida,int insiemeCompleto[],int dimCompleto){
    int j=0,i=0,t=0,u=0,indiceOccorrenza=0,tmp[9]={0,0,0,0,0,0,0,0,0},occorrenze[9]={0,0,0,0,0,0,0,0,0},forzata=0;
    if(pos>=k){//ho costruito la soluzione parzialeper cui mi chiedo se e valida, se e cosi ho finito
#ifndef RDBG
        printf("\t\t\t\t ELENCO DEGLI INSIEMI CHE STO PROVANDO:\n");
        for(int e=0;e<k;e++){
            printf("\t");
            for(int o=0;sol[e][o]!=0;o++){
                printf(" %d ",sol[e][o]);
            }
            printf("\n");
        }
#endif
        for(i=0;i<k;i++){//NB k e il numero di elementi(sottoinsiemi in questo caso, della combinazione)
            //srotolo i sottoinsiemi in un unico vettore
            for(u=0;sol[i][u]!=0 && forzata==0;u++){//zero è terminatore di riga
                tmp[t]=sol[i][u];
#ifndef SROTDBG
                printf("\tValore soluzione parziale durante srotolamento: SOL %d TMP %d\n\n",sol[i][u],tmp[t]);
#endif
                if(t>=dimCompleto){// se supero la lunghezza massima di tmp setto tutto a -1 nelle occorrenze
                    for(int j=0;j<dimCompleto;j++){
                        occorrenze[j]=-1;
                    }
                    //t--;
#ifndef DBG
                    printf("\t\t\t\tUSCITA FORZATA t=%d",t);
#endif
                    forzata=1;//forzo uscita dal ciclo, anche se modifico la solluzione non fa niente perche non e valida
                }
                else{
                t++;
                }
            }
            //elementiSottoinsieme[i]=(u-1);
        }
       
        for(int z=0;z<t;z++){
#ifndef DBG
            printf("\tValore di SONOQUI!!! INSIEMECOMPLETO %d durante controllo.\n\n",insiemeCompleto[z]);
            printf("\tValore di TMP %d durante controllo.\n\n",tmp[z]);
#endif
            
            indiceOccorrenza=rDicotomica(insiemeCompleto, 0, dimCompleto, tmp[z]);
            if(indiceOccorrenza!=-1){//conto le occorrenze di ogni elemento
                occorrenze[indiceOccorrenza]++;
            }
        }
#ifndef SDBG
        printf("FASE DI CONTROLLO VALIDITA':\n");
        for(int z=0;z<t;z++){
            printf("\t\t\t\tVETTORE OCCORRENZE cella %d (numero %d) valore:%d\n\n",z,z+1,occorrenze[z]);
        }
        printf("\t\t\t\t..............Fine tentativo...............\n\n");
#endif  
        valida=1;//setto il flag come soluzione valida e se poi non lo e lo riporto a 0

        for(t=0;t<dimCompleto;t++){
#ifndef SDBG
            
            printf("\tValore OCCORRENZE di %d (INDICE %d)durante controllo: %d\n\n",insiemeCompleto[t],insiemeCompleto[t]-1,occorrenze[insiemeCompleto[t]-1]);
#endif

            if(occorrenze[t]!=1){//se un elemento compare piu di una volta c'è errore oppure se non compare
                valida=0;
            }
        }
        if (valida){
            return 1;
        }
        else{
            return 0;
        }
        
    }
for(j=start;j<n;j++){
    
    for(u=0;u<10;u++){//reinizializza a 0 sol
        sol[j][u]=0;
    }
        u=0;
        while(val[j][u]!=0 && u<10){//al posto che copiare il singolo elemento come nell algoritmo da template copio tutta la riga
         sol[pos][u] = val[j][u];//copio il puntatore alla riga pos-esima di sol nel j-esimo puntatore di val
        
#ifndef DBG
        printf("\t\tValore della soluzione:%d alla riga %d, colonna %d\n\n",sol[pos][u],pos,u);
        printf("\t\tValore del val:%d alla riga %d, colonna %d\n\n",val[j][u],j,u);
        printf("\t\t\t\t..............Fine iterazione...............\n\n");
#endif
          u++;
    }
#ifndef CPYDBG
    printf("......\nHo copiato l insieme:\n ");
    
    for(int v=0;sol[pos][v]!=0 && v<10;v++){
        printf(" %d",sol[pos][v]);
    }
    printf("\n");
    
    printf("Mentre val di j vale:\n ");
    
    for(int v=0;val[j][v]!=0 && v<10;v++){
        printf(" %d ",val[j][v]);
    }
   
    
    printf("\t\t\tNB: J VALE %d mentre pos vale %d\n",j,pos);
     printf("\n....\n");
#endif
        valida = combInsiemi(pos+1, val, sol, n, k, j+1, valida,insiemeCompleto,dimCompleto);
    if(valida==1){//forzo l uscita dal ciclo in caso abbia trovato una soluzione valida(non mi interessa enumerarle
        break;
    }
    }

    return valida;//in caso non ci siano nemmeno abbastanza insiemi di k elementi non vado nemmeno a fare il controllo successivo
}



int rDicotomica(int v[], int l, int r, int chiave){
    int m;
    while(l<=r){//ciclo fino a quando gli indici di estrema dei vettori non si incontrano
        m=l+(r-l)/2;//trovo l elemento di mezzo del vettore
        if(v[m] == chiave){
            return(m);//terminazione, ho trovato la chiave
        }
        if(v[m] < chiave){//se il valore e minore della chiave cerco a sinistra
                l = m+1;
        }
        else{//se il valore e maggiore cerco a destra
                r = m-1;
            }
    }
    return -1;
}


