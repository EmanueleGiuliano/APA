//
//  main.c
//  Esercitazione11es03
//
//  Created by apple on 16/01/17.
//  Copyright © 2017 emag. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

static int verificato=0;

void decomponi(char *str, int num, int *lungh);
int comb(int pos, char **val, char *sol,char *verifica, int n, int k,int start, int count);
int disp_rip(int pos,char *val,char *sol,int n,int k,int count,int numSottostr, int *lunghVett,int posDecomponi,char** solFinale,char *verifica,char*str);
int comb_r(int pos,int *val,int *sol,int **salvaSol,int n,int k, int start, int count,int *numSol);
int main(int argc, const char * argv[]) {
    char parola[30];
    int *lun=NULL,numSottoStr=0;
    printf("\tInserisci la parola da decomporre: ");
    scanf("%s",parola);
    printf("\n");
    printf("\tQuante lunghezze vuoi inserire? ");
    scanf("%d",&numSottoStr);
    lun=malloc(numSottoStr*sizeof(int));
    for(int k=0;k<numSottoStr;k++){
        printf("Lunghezza numero %d: ",(k+1));
        scanf("%d",&lun[k]);
    }
    printf("\t\t\t....Elaboro.......\n");
    decomponi(parola, numSottoStr, lun);
    return 0;
}

int fact(int num){
    if(num==0 || num==1){
        return 1;
    }
    return num*fact(num-1);
}

void generaSottostr(int pos,char *val,int n,int k,int count,int numSottostr, int *lunghVett,int posDecomponi,char** solFinale,char *verifica,char*str){
    char *sottoStrTmp=malloc(strlen(str)*sizeof(char));
    disp_rip(0, val, sottoStrTmp,(int) strlen(val), k, 0,numSottostr,lunghVett,posDecomponi,solFinale,verifica,str);
}

void decomponiR(char *verifica,char *str,char *val, int num, int *lungh,int pos,char** sol){
    if(pos>=num){
        for(int i=0;i<num;i++){
            verifica=strcat(verifica,sol[i]);
        }
        if(strcmp(verifica,str)==0){
            printf("Soluzione: ");
            for(int i=0;i<num;i++){
                printf(" %s ",sol[i]);
            }
            printf("\n");
            verificato=1;
        }
        for(int i=0;i<strlen(verifica);i++){
            verifica[i]='\0';
        }
        //un primo pruning potrebbe essere mettere un flag che segnala che la verifica ha avuto successo cosi da non generare le disposizioni successive
        return;
    }
    if(!verificato){
        generaSottostr(0, val,(int) strlen(val), lungh[pos], 0,num,lungh,pos,sol,verifica,str);
    }
    return;
}
void decomponi(char *str, int num, int *lungh){
    int tro,j=0;char **decomposta=NULL;int somma=0;char *val=malloc(strlen(str)*sizeof(char));
    int **combLunghezze=NULL,*solCombTmp=malloc(num*sizeof(int));
    int numeroCombLung=0,numeroSol=0;
    char *verifica=malloc(strlen(str)*sizeof(char));
    for(int i=0;i<strlen(str);i++){
        verifica[i]='\0';
    }
    decomposta=malloc(num*sizeof(char*));
    for(int i=0;i<num;i++){
        decomposta[i]=malloc(lungh[i]*sizeof(char));
        strcpy(decomposta[i],"\0");
    }
    for(int i=0;str[i]!='\0';i++){
        tro=0;
        for(int k=0;val[k]!='\0' && !tro;k++){
            if(str[i]==val[k]){
                tro=1;
            }
        }
        if(!tro){
            val[j]=str[i];
            j++;
        }
    }
    for(int i=1;i<=num;i++){
        numeroCombLung=fact(num+i-1)/(fact(i)*fact(num-1));
        combLunghezze=malloc(numeroCombLung*sizeof(int*));
        printf("Numero combinazioni: %d\n",numeroCombLung);
        for(int j=0;j<numeroCombLung;j++){
            combLunghezze[j]=malloc(num*sizeof(int));
        }
        comb_r(0, lungh,solCombTmp, combLunghezze, num, i, 0, 0,&numeroSol);
        //fatte queste, faccio il pruning sulla somma e vado a mettere in decomponiR
        for(int j=0;j<numeroCombLung;j++){
            for(int u=0;u<num;u++){
                printf("%d ",combLunghezze[j][u]);
                somma+=combLunghezze[j][u];
            }
            if(somma==strlen(str)){
                //decomponi verrà chiamato solo se la somma della combinazione di lunghezze e = alla strlen
                decomponiR(verifica,str,val,i,combLunghezze[j],0,decomposta);
                verificato=0;
            }
            somma=0;
            printf("\n");
            
        }
        numeroSol=0;
        for(int j=0;j<numeroCombLung;j++){
            free(combLunghezze[j]);
        }
        printf("\n\t\t.............\n");
    }
    
    
}



int disp_rip(int pos,char *val,char *sol,int n,int k,int count,int numSottostr, int *lunghVett,int posDecomponi,char** solFinale,char *verifica,char*str){
    int i;
    if (pos >= k) {
        strcpy(solFinale[posDecomponi], sol);
        decomponiR(verifica,str,val, numSottostr, lunghVett, posDecomponi+1, solFinale);
        return count+1;
    }
    for (i = 0; i < n; i++) {
        sol[pos] = val[i];
        count = disp_rip(pos+1, val, sol, n, k, count,numSottostr,lunghVett,posDecomponi,solFinale,verifica,str);
    }
    return count;
}





int comb_r(int pos,int *val,int *sol,int **salvaSol,int n,int k, int start, int count,int *numSol) {
    int i;
    if (pos >= k) {
        for (i=0; i<k; i++)
             salvaSol[*numSol][i]=sol[i];
        (*numSol)++;
        return count+1;
    }
    for (i=start; i<n; i++) {
        sol[pos] = val[i];
        count = comb_r(pos+1, val, sol,salvaSol, n, k, start, count,numSol);
        start++;
    }
    return count;
}