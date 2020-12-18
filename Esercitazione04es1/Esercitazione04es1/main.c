//
//  main.c
//  Esercitazione04es1
//
//  Created by apple on 02/11/16.
//  Copyright © 2016 emag. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
//#include <time.h>
//STRUTTURE
//ogni volta nel file andrai a guardare la lunghezza delle stringhe che compongono i campi del prodotto e allocherai in memoria delle stringhe della dimensione giusta(nella struttura hai solo i puntatori, tranne per il codice che ha dimensione fissa
typedef struct prodotto{
    char codice[10];
    char *nome;
    char *categoria;
    float prezzo;
    int quantita;
    char ultimoAggiornamento[11];//gg/mm/aaaa
    
}Prodotto;
typedef  enum{
    stampa, ordina_pr, ordina_cp, ordina_np, stampa_pc, aggiorna_qt, ricerca_cp, ricerca_pn, fine
}comando_menu;
typedef enum{
    nome,prezzo,codice,categoria
}ordinamento;
//PROTOTIPI
Prodotto* leggiProdotti(char nomeFile[],int *numeroProdotti);
void stampaProdotti(char tipoStampa,Prodotto *catalogo, int numProd, ordinamento *ord);//tipo stampa serve a dire se voglio stampare tutto o per categoria
void ordinaProdotti(char filtro,Prodotto *catalogo, int numProd);
void stampaMenu();
void aggiornaQuantita(char cod[],Prodotto *catalogo, int numProd, ordinamento *ord);
void ricercaProdotto(char filtro,ordinamento tipoOrd,Prodotto *catalogo, int numProd,char chiave[]);
int ricLineare(char chiave[], int dim, Prodotto *catalogo);
comando_menu leggiComando();
void strToLower(char s[],int dim);
int cercaElementoBin(char chiave[],Prodotto *catalogo, int numProd);
void quicksort(Prodotto *catalogo, int dim, ordinamento *ord);
void quicksortR(Prodotto *catalogo,int l, int r, ordinamento *ord);
int partition(Prodotto *catalogo, int l, int r, ordinamento *ord);
void swap(Prodotto *catalogo, int k,int h);
void liberaMemoria(Prodotto *catalogo, int dim);
//MAIN
int main(int argc, const char * argv[]) {
    int continua=1,numeroProdotti;
    char filtro,prodotto[10];
    ordinamento tipoOrd=codice;//flag che manterra salvato il modo in cui è ordinato il db
    Prodotto* catalogo;//deve essere un vettore allocato dinamicamente a seconda del numero di prodotti nel file(sara il puntatore al primo elemento del vettore di strutture
    comando_menu cmd=0;
    catalogo= leggiProdotti("catalogo.txt",&numeroProdotti);
    while(continua){
        cmd=leggiComando();
        if(cmd!=fine){
            switch(cmd){
                case 0:
                    stampaProdotti('N',catalogo,numeroProdotti,&tipoOrd);//stampa normale
                    break;
                case 1:
                    printf("Vuoi ordinare per prezzo ascendente o discendente?(A->Ascendente D->Discendente)\n");
                    scanf("%c",&filtro);
                    filtro=toupper(filtro);
                    while(filtro!='A' && filtro!='D'){
                        printf("Vuoi ordinare per prezzo ascendente o discendente?(A->Ascendente D->Discendente)\n");
                        scanf("%c",&filtro);
                    }
                    ordinaProdotti(filtro,catalogo,numeroProdotti);//se il parametro del filtro è A o D stampa per prezzo ascendente o discendente
                    tipoOrd=prezzo;
                    break;
                case 2:
                    ordinaProdotti('C',catalogo,numeroProdotti);//C e per ordinamento per codice prodotto
                    tipoOrd=codice;
                    break;
                case 3:
                    ordinaProdotti('N',catalogo,numeroProdotti);//N ordina per nome
                    tipoOrd=nome;
                    break;
                case 4:
                    stampaProdotti('C',catalogo,numeroProdotti,&tipoOrd);//stampa per categoria
                    break;
                case 5:
                    printf("Inserisci il codice del prodotto che vuoi aggiornare:\n");
                    scanf("%s",prodotto);
                    aggiornaQuantita(prodotto,catalogo,numeroProdotti,&tipoOrd);
                    break;
                case 6:
                    printf("Inserisci il codice del prodotto che vuoi cercare:\n");
                    scanf("%s",prodotto);
                    ricercaProdotto('C',tipoOrd,catalogo,numeroProdotti,prodotto);//per codice
                    break;
                case 7:
                    printf("Inserisci il codice del prodotto che vuoi cercare:\n");
                    scanf("%s",prodotto);
                    ricercaProdotto('N',tipoOrd,catalogo,numeroProdotti,prodotto);//per nome
                    break;
                default:
                    printf("Inserisci un comando valido tra quelli elencati.\n");
                    break;
            }
        }
        else{
            continua=0;
            printf("Programma terminato.\n");
        }
    }
    liberaMemoria(catalogo, numeroProdotti);//dealloco la memoria dinamica
    return 0;
}

//FUNZIONI
Prodotto* leggiProdotti(char nomeFile[],int *numeroProdotti){
    Prodotto *catalogo;
    char nome[31],categoria[31];//vettori di appoggio per la lettura
    int k=0;
    FILE *fin=fopen(nomeFile, "r");
    if(fin!=NULL){
        fscanf(fin,"%d",numeroProdotti);
        catalogo=(Prodotto*) malloc((*numeroProdotti)*sizeof(Prodotto));//alloco numeroProdotti strutture di tipo Prodotto e salvo il puntatore alla prima in catalogo
        while(k<*numeroProdotti){
            if(fscanf(fin, "%s %s %s %f %d %s",catalogo[k].codice,nome,categoria,&catalogo[k].prezzo,&catalogo[k].quantita,catalogo[k].ultimoAggiornamento)!=EOF){
                catalogo[k].nome= (char*) malloc(strlen(nome)*sizeof(char));//alloco dinamicamente una stringa della dimensione del nome
                catalogo[k].categoria= (char*) malloc(strlen(categoria)*sizeof(char));
                strcpy(catalogo[k].nome, nome);//copio il nome nella struttura
                strcpy(catalogo[k].categoria, categoria);
            }
            else{//se sono arrivato a fine file forzo l uscita dal ciclo
                k=*numeroProdotti;
                }
            k++;
        }
        fclose(fin);
    }
    else{
        printf("Errore nell'apertura del file: catalogo non letto\n");
    }
    return catalogo;
}
void liberaMemoria(Prodotto *catalogo, int dim){
    int k;
    for(k=0;k<dim;k++){
        free(catalogo[k].nome);
        free(catalogo[k].categoria);
    }
    free(catalogo);
}
void stampaProdotti(char tipoStampa,Prodotto *catalogo,int numProd, ordinamento *ord){
    int k=0,i=1;
    printf("\n\t.....CATALOGO PRODOTTI.......\n");
    if(tipoStampa=='N'){
        for(k=0;k<numProd;k++){
            printf("%s %s %s %.2f %d %s\n",catalogo[k].codice,catalogo[k].nome,catalogo[k].categoria,catalogo[k].prezzo,catalogo[k].quantita,catalogo[k].ultimoAggiornamento);
        }
    }else {
        *ord=categoria;//vado a modificare lo stato perchè per stampare per categoria devo ordinare
        quicksort(catalogo, numProd,ord);//ordino per categoria
        printf("\n\t......CATEGORIA: %s ......\n",catalogo[k].categoria);
        for(k=0;k<numProd;k++){//stampa gli articoli
            if(strcmp(catalogo[k].categoria, catalogo[i].categoria)!=0){
                printf("\n\t......CATEGORIA: %s ......\n",catalogo[k].categoria);
                i=k;
            }
            printf("\n\t%s %s %s %.2f  %d %s\n",catalogo[k].codice,catalogo[k].nome,catalogo[k].categoria,catalogo[k].prezzo,catalogo[k].quantita,catalogo[k].ultimoAggiornamento);
            
        }
    }
    printf("\n");
}

void ordinaProdotti(char filtro,Prodotto *catalogo, int numProd){
    int i,j,scambi=1;
    Prodotto tmp;
    switch(filtro){
            //per gli ordinamenti momentaneamente uso il bubble sort perchè non abbiamo ancora studiato quelli di complessità minore
        case 'A'://prezzo ascendente
            for(i=0;i<numProd&&scambi;i++){
                scambi=0;
                for(j=0;j<numProd-i-1;j++){//ogni giro il sottovettore destro cresce e io devo ciclare una volta in meno
                    if(catalogo[j].prezzo>catalogo[j+1].prezzo){
                        scambi=1;
                        tmp=catalogo[j+1];
                        catalogo[j+1]=catalogo[j];
                        catalogo[j]=tmp;
                        //se io mi fossi fatto un array di puntatori che puntavano ognuno a una cella del vettore di struct e avessi fatto gli scambi tra quelli avrebbe avuto senso?
                    }
                }
            }
            break;
        case 'D'://prezzo discendente
            for(i=0;i<numProd&&scambi;i++){//=Bubble sort ma fa emergere il minore
                scambi=0;
                for(j=0;j<numProd-i-1;j++){
                    if(catalogo[j].prezzo<catalogo[j+1].prezzo){
                        scambi=1;
                        tmp=catalogo[j];
                        catalogo[j]=catalogo[j+1];
                        catalogo[j+1]=tmp;
                    }
                }
            }
            break;
        case 'C'://per codice
            for(i=0;i<numProd&&scambi;i++){
                scambi=0;
                for(j=0;j<numProd-i-1;j++){//ogni giro il sottovettore destro cresce e io devo ciclare una volta in meno
                    if(strcmp(catalogo[j].codice,catalogo[j+1].codice)>0){
                        scambi=1;
                        tmp=catalogo[j+1];
                        catalogo[j+1]=catalogo[j];
                        catalogo[j]=tmp;
                        //se io mi fossi fatto un array di puntatori che puntavano ognuno a una cella del vettore di struct e avessi fatto gli scambi tra quelli avrebbe avuto senso?
                    }
                }
            }
            break;
        case 'N'://per nome
            for(i=0;i<numProd&&scambi;i++){
                scambi=0;
                for(j=0;j<numProd-i-1;j++){//ogni giro il sottovettore destro cresce e io devo ciclare una volta in meno
                    if(strcmp(catalogo[j].nome,catalogo[j+1].nome)>0){
                        scambi=1;
                        tmp=catalogo[j+1];
                        catalogo[j+1]=catalogo[j];
                        catalogo[j]=tmp;
                        //se io mi fossi fatto un array di puntatori che puntavano ognuno a una cella del vettore di struct e avessi fatto gli scambi tra quelli avrebbe avuto senso?
                    }
                }
            }
            break;
        default:
            printf("Errore nella chiamata alla funzione di ordinamento\n");
            break;
    }
}

comando_menu leggiComando(){
    comando_menu comando=fine;//inizializzo a fine, se poi il comando e un altro non termino se no restituisco fine
    char lettura[26];//usciva il sigabrt perchè andavo a sovrascrivere un area di memoria che non dovevo siccome "lettura" era di dimensione giusta giusta, la soluzione e' stata ingrandire la stringa
    char *tabellaComandi[fine]={
        "stampa", "ordinaprezzo", "ordinacodice", "ordinanome","stampacat","aggiornaqt","ricercacod","ricercanome"
    };
    stampaMenu();
    fflush(stdin);//pulisco il buffer
    scanf("%s",lettura);
    strToLower(lettura,strlen(lettura));
    comando=stampa;//parte da 0(ricorda equivalenza enum-->0,1,2,3...
    while(comando<fine && strcmp(lettura,tabellaComandi[comando])!=0){//scorro i comandi alla ricerca di una corrispondenza con la str immessa
        comando++;
    }
    return comando;
}


void swap(Prodotto *catalogo, int k,int h){
    Prodotto tmp;
    //h è l indice di quello minore del pivot k di quello maggiore
    //lo swap avviene tra i puntatori e non tra le strutture
    tmp=catalogo[k];
    catalogo[k]=catalogo[h];
    catalogo[h]=tmp;
}

int partition(Prodotto *catalogo, int l, int r,ordinamento *ord){
    int i,j;
    i=l-1;j=r;
    char *pivot;
    int pivotInteri=0;
    switch(*ord){
        case 0://nome
            pivot=catalogo[r].nome;
            for(;;){
                while(strcmp(catalogo[++i].nome, pivot)<0);//scorro da sinistra a destra alla ricerca di elementi maggiori del pivot
                while(strcmp(catalogo[--j].nome, pivot)>0);//scorro da destra a sinistra alla ricerca di elementi minori
                if(j==l){//se sono arrivato a inizio vettore ho finito e forzo l uscita, perche vuol dire che ho scorso tutto il vettore all indietro senza trovare nulla di minore del pivot,(pivot è il minore del vettore)
                    break;
                }
                if(j<=i){//i due indici si sono "incontrati" per cui devo terminare il ciclo(ho trovato la posizione del pivot e ho diviso in due sottovettori maggiori e minori di esso VETTORI DI STRUTTURE VEDI P. 124 LUCIDO 2
                    break;
                }
                //se non sono uscito dal ciclo significa che ho trovato un elemento maggiore alla sinistra ed uno minore alla destra del pivot  per cui scambio
                swap(catalogo,i,j);
            }
            break;
        case 1://prezzo
            pivotInteri=catalogo[r].prezzo;
            for(;;){
                while(catalogo[--j].prezzo< pivotInteri);//scorro da sinistra a destra alla ricerca di elementi maggiori del pivot
                while(catalogo[--j].prezzo> pivotInteri);//scorro da destra a sinistra alla ricerca di elementi minori
                if(j==l){//se sono arrivato a inizio vettore ho finito e forzo l uscita, perche vuol dire che ho scorso tutto il vettore all indietro senza trovare nulla di minore del pivot,(pivot è il minore del vettore)
                    break;
                }
                if(j<=i){//i due indici si sono "incontrati" per cui devo terminare il ciclo(ho trovato la posizione del pivot e ho diviso in due sottovettori maggiori e minori di esso VETTORI DI STRUTTURE VEDI P. 124 LUCIDO 2
                    break;
                }
                //se non sono uscito dal ciclo significa che ho trovato un elemento maggiore alla sinistra ed uno minore alla destra del pivot  per cui scambio
                swap(catalogo,i,j);
            }
            break;
        case 2://codice
            pivot=catalogo[r].codice;
            for(;;){
                while(strcmp(catalogo[++i].codice, pivot)<0);//scorro da sinistra a destra alla ricerca di elementi maggiori del pivot
                while(strcmp(catalogo[--j].codice, pivot)>0);//scorro da destra a sinistra alla ricerca di elementi minori
                if(j==l){//se sono arrivato a inizio vettore ho finito e forzo l uscita, perche vuol dire che ho scorso tutto il vettore all indietro senza trovare nulla di minore del pivot,(pivot è il minore del vettore)
                    break;
                }
                if(j<=i){//i due indici si sono "incontrati" per cui devo terminare il ciclo(ho trovato la posizione del pivot e ho diviso in due sottovettori maggiori e minori di esso VETTORI DI STRUTTURE VEDI P. 124 LUCIDO 2
                    break;
                }
                //se non sono uscito dal ciclo significa che ho trovato un elemento maggiore alla sinistra ed uno minore alla destra del pivot  per cui scambio
                swap(catalogo,i,j);
            }
            break;
        case 3://categoria
            pivot=catalogo[r].categoria;
            for(;;){
                while(strcmp(catalogo[++i].categoria, pivot)<0);//scorro da sinistra a destra alla ricerca di elementi maggiori del pivot
                while(strcmp(catalogo[--j].categoria, pivot)>0);//scorro da destra a sinistra alla ricerca di elementi minori
                if(j==l){//se sono arrivato a inizio vettore ho finito e forzo l uscita, perche vuol dire che ho scorso tutto il vettore all indietro senza trovare nulla di minore del pivot,(pivot è il minore del vettore)
                    break;
                }
                if(j<=i){//i due indici si sono "incontrati" per cui devo terminare il ciclo(ho trovato la posizione del pivot e ho diviso in due sottovettori maggiori e minori di esso VETTORI DI STRUTTURE VEDI P. 124 LUCIDO 2
                    break;
                }
                //se non sono uscito dal ciclo significa che ho trovato un elemento maggiore alla sinistra ed uno minore alla destra del pivot  per cui scambio
                swap(catalogo,i,j);
            }
            break;
        default:
            break;
    }
    swap(catalogo,i,r);//scambia il pivot mettendolo nella posizione giusta dell ordinamento
    return i;//ritorno la posizione del pivot
}

void quicksortR(Prodotto *catalogo,int l, int r,ordinamento *ord){
    int q;
    if(r<=l){//ho un elemento solo per cui è ordinato per forza(condizione di terminazione della ricorsione)
        return;
    }
    q=partition(catalogo, l, r,ord);
    quicksortR(catalogo,l,q-1,ord);//ordino ricorsivamente il vettore sinistro
    quicksortR(catalogo,q+1,r,ord);//ordino il destro
    return;
}

void quicksort(Prodotto *catalogo, int dim,ordinamento *ord){
    int l=0, r=dim-1;
    quicksortR(catalogo,l,r,ord);
}
int cercaElementoBin(char chiave[],Prodotto *catalogo, int numProd){
    int m,l=0,r=numProd-1;
    while(l <= r){
        m=l+(r-l)/2;//calcola l indice dell elemento di mezzo
        if(strcmp(catalogo[m].codice,chiave)==0 || strcmp(catalogo[m].nome,chiave)==0 ){//unico problema che puo sorgere da questa implementazione e se un prodotto avesse nome = al codice di un altro
            return(m);
        }
        if(strcmp(catalogo[m].codice,chiave)<0 || strcmp(catalogo[m].nome,chiave)<0 ){
            l=m+1;
        }
        else{
            r=m-1;
        }
    }
    return(-1);
}
void aggiornaQuantita(char cod[],Prodotto *catalogo, int numProd, ordinamento *ord){
    int indiceProdotto=-1;
    *ord=codice;//devo ordinare per codice prima di stampare la quantita
    //codice per prendere la data di sistema e aggiornare tutto(chiedere come si può realizzare)
    
    //char dataStr[11],gg,mm,aaaa,sep='/';
    
    /*struct tm *data= NULL;//struttura appartenente a time.h
    time_t tempo;
    time(&tempo);
    data = localtime(&tempo);
    gg=(char)(data->tm_mday);
    mm=(char)(data->tm_mon);
    aaaa=(char)(data->tm_year);
    strcpy(dataStr,strcat(&gg, &sep));
    strcpy(dataStr,strcat(dataStr, &mm));
    strcpy(dataStr,strcat(dataStr, &sep));
    strcpy(dataStr,strcat(dataStr, &aaaa));*/
    
    
    //ordino col quicksort e poi eseguo una ricerca dicotomica
    quicksort(catalogo, numProd,ord);
    indiceProdotto=cercaElementoBin(cod,catalogo,numProd);
    if(indiceProdotto!=-1){
        printf("Inserisci la nuova quantita':\n");
        scanf("%d",&catalogo[indiceProdotto].quantita);
        //strcpy(catalogo[indiceProdotto].ultimoAggiornamento,dataStr);
    }
    else{
        printf("Elemento non trovato\n");
    }
}
int ricLineare(char chiave[], int dim, Prodotto *catalogo){
    int k;
    for(k=0;k<dim;k++){
        if(strcmp(chiave,catalogo[k].codice)==0||strcmp(chiave, catalogo[k].nome)==0){
            return k;
        }
    }
    return -1;
}
void ricercaProdotto(char filtro,ordinamento tipoOrd,Prodotto *catalogo, int numProd,char chiave[]){
    int indice;
    if(filtro=='C'){
        switch(tipoOrd){// a seconda dello stato di ordinamento chiamo una diversa funzione di ricerca
            case 0://nome
                indice=ricLineare(chiave, numProd, catalogo);
                break;
            case 1://prezzo
                indice=ricLineare(chiave, numProd, catalogo);
                break;
            case 2://codice
                indice=cercaElementoBin(chiave, catalogo, numProd);
                break;
            default:
                indice=ricLineare(chiave, numProd, catalogo);
                break;
        }
    }
    else if (filtro=='N'){
        switch(tipoOrd){// a seconda dello stato di ordinamento chiamo una diversa funzione di ricerca
            case 0://nome
                indice=cercaElementoBin(chiave, catalogo, numProd);
                break;
            case 1://prezzo
                indice=ricLineare(chiave, numProd, catalogo);
                break;
            case 2://codice
                indice=ricLineare(chiave, numProd, catalogo);
                break;
            default:
                indice=ricLineare(chiave, numProd, catalogo);
                break;
        }
    }
    if(indice!=-1){
        printf("\t.....DATI RELATIVI ALL ELEMENTO CERCATO....\n");
        printf(" %s %s %.2f %d %s\n",catalogo[indice].nome,catalogo[indice].categoria,catalogo[indice].prezzo,catalogo[indice].quantita,catalogo[indice].ultimoAggiornamento);
    }
    else{
        printf("\tLa ricerca non ha prodotto risultati.\n");
    }
}
void strToLower(char s[],int dim){
    int j;
    for(j=0;j<dim;j++){
        s[j]=tolower(s[j]);
    }
}

void stampaMenu(){
    printf("\nElenco comandi:(scegli cosa vuoi fare)\n");
    printf("stampa - stampa tutti i prodotti del catalogo\n");
    printf("ordinaprezzo - ordina i prodotti per prezzo\n");
    printf("ordinacodice - ordina i prodotti per codice\n");
    printf("ordinanome - ordina i prodotti per nome\n");
    printf("stampacat - stampa i prodotti divisi per categoria\n");
    printf("aggiornaqt - aggiorna la quantita di articoli in magazzino di un determinato prodotto\n");
    printf("ricercacod - ricerca un prodotto inserendo il codice\n");
    printf("ricercanome - ricerca un prodotto inserendo il nome\n");
    printf("fine - termina il programma\n");
}