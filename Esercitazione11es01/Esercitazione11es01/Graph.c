//
//  Graph.c
//  RaccoltaADTIClasse
//
//  Created by apple on 10/01/17.
//  Copyright © 2017 emag. All rights reserved.
//

#include "Graph.h"
#include <stdlib.h>
#define DENSO 1
//#define SPARSO 1

//.......................FUNZIONI DI UTILITA' INTERNE AL MODULO e STRUTTURA....................................


            //Grafi densi: utilizza una matrice di adiacenza


#ifndef DENSO
struct graph {
    int V; int E; int **adj; ST tab;
};



int **MATRIXint(int r, int c, int val) {
    int i, j;
    int **t = malloc(r * sizeof(int *));
    for (i=0; i < r; i++) t[i] = malloc(c * sizeof(int)); for (i=0; i < r; i++){
        for (j=0; j < c; j++){
            t[i][j] = val;
        }
    }
    return t;
}

void  insertE(Graph G, Edge e) {
    int v = e.v, w = e.w, wt =e.wt;
    if (G->adj[v][w] == 0){
        G->E++;
    }
    //cambiando le rappresentazioni modifichiamo il tipo di grafo(orientato o meno e pesato o meno)
    //qua è non orientato(matrice simmetrica) non pesato (o 1 o 0)
    G->adj[v][w] = 1;
    //G->adj[v][w] = wt;
    G->adj[w][v] = 1;
    //G->adj[w][v] = wt;
}

void removeE(Graph G, Edge e) {
    int v = e.v, w = e.w;
    if (G->adj[v][w] != 0){
        G->E--;
        //se il grafo è orientato queste due righe vanno modificate
        G->adj[v][w] = 0;
        G->adj[w][v] = 0;//togli questa, se è orientato
    }
}

#endif









                        //Grafi sparsi: utilizza una lista di adiacenza

#ifndef SPARSO
#define maxV 100
#define MAX 10
typedef struct node *adjLink;
struct node { int v; int wt; adjLink next;};
struct graph{int V; int E; adjLink *adj; ST tab; adjLink z} ;

adjLink NEW(int v, adjLink next, int wt) {
    adjLink x = malloc(sizeof *x);
    x->v = v;
    x->next = next;
    x->wt = wt;
    return x;
}


void insertE(Graph G, Edge e) {
    int v = e.v, w = e.w, wt = e.wt;
    G->adj[v] = NEW(w,  G->adj[v],wt);
    G->adj[w] = NEW(v,  G->adj[w],wt);//per grafi orientati eliminare questa riga
    G->E++;
    
}

void removeE(Graph G, Edge e) {
    //notare che questa funzione non esegue una free dei nodi perchè a tutti gli effetti serve solo realizzare il bypass per eliminare l arco, il vertice deve continuare ad esistere
    int v = e.v, w = e.w;
    adjLink x;
    if (G->adj[v]->v == w) {
        G->adj[v] = G->adj[v]->next;
        G->E--;
    }
    else{
        for (x = G->adj[v]; x != G->z; x = x->next){
            if (x->next->v == w) {
                x->next = x->next->next;
                G->E--;
            }
        }
    }
    //per grafi non orientati ci vuole anche questa parte(rimuovi in entrambe le direzioni)
    if (G->adj[w]->v == v){
        G->adj[w] = G->adj[w]->next;
    }
    else{
        for (x = G->adj[w]; x != G->z; x = x->next){
            if (x->next->v == v){
                x->next = x->next->next;
            }
        }
    }
}
#endif




//........................................................................................................

//...........................FUNZIONI DI INTERFACCIA COL CLIENT...............................................

                //Grafi densi: utilizza una matrice di adiacenza


#ifndef DENSO

Graph GRAPHinit(int numV) {
    Graph G = malloc(sizeof (struct graph));
    if (G == NULL){
        return NULL;
    }
    G->V = numV;
    G->E = 0;
    G->adj = MATRIXint(numV, numV, 0);
    G->tab = STinit(numV);//tabella di simboli ad accesso diretto
    if (G->tab == NULL){
        return NULL;
    }
    return G;
}






void  GRAPHshow(Graph G){
    int i,j;
    Item tmp=ITEMinit();
    printf("Questo grafo ha %d vertici e %d archi\n",G->V,G->E);
    for(i=0;i<G->V;i++){
        STretrieve(G->tab, i, &tmp);//le st retrieve vanno modificate in ST.h
        printf("Il vertice: ");
        ITEMshow(tmp);
        printf(" è collegato ai seguenti altri vertici: \n");
        for (j=0; j < G->V; j++){
            if (G->adj[i][j] != 0){
                printf("\t");
                STretrieve(G->tab, i, &tmp);
                ITEMshow(tmp);
                printf(" %d",G->adj[i][j]);//Questa printf stampa il peso(per grafi non pesati sara sempre 1)
                printf("\n");
            }
        }
    }
    ITEMfree(tmp);
}



void GRAPHedges(Graph G, Edge *a) {
    int v, w, E = 0;
    for (v=0; v < G->V; v++){
        for (w=v+1; w < G->V; w++){//essendo la matrice simmetrica, per grafi non orientati non serve visitarla tutta
        //for (w=0; w < G->V; w++){-->sostiutisci con questa per grafi orientati
            if (G->adj[v][w] !=0){
                    a[E++] = EDGEcreate(v, w, G->adj[v][w]);//crea l arco inserendo il valore contenuto nella lista di adiacenza come peso, se il grafo non e pesato trovera un uno nella matrice
            }
            
        }
    }
    return;
}
/*
        DA REALIZZARE
 
 
int   GRAPHpath(Graph G);
int GRAPHpathH(Graph G);
void GRAPHbfs(Graph G);
void GRAPHdfs(Graph G);
int GRAPHcc(Graph G);
int GRAPHscc(Graph G);*/
#endif











                            //Grafi sparsi: utilizza una lista di adiacenza

#ifndef SPARSO
Graph GRAPHinit(int dimV){
    int v;
    Graph G = malloc(sizeof (struct graph));
    if (G == NULL){
        return NULL;
    }
    G->V = dimV;
    G->E = 0;
    G->adj=malloc(sizeof(adjLink));
    G->z=NEW(-1,NULL,0);
    for (v = 0; v < G->V; v++){
        G->adj[v] = G->z;
    }
    G->tab = STinit(dimV);
    if (G->tab == NULL){
       return NULL;
    }
    else{
        return G;
    }
}
void  GRAPHshow(Graph G){
    int v;
    adjLink t=NULL;
    Item tmp=ITEMinit();
    printf("%d vertici, %d archi \n", G->V, G->E);
    for (v=0; v < G->V; v++) {
        STretrieve(G->tab,v,&tmp);
        printf("Nodi adiacenti a: ");ITEMshow(tmp);printf("\n");
        for (t=G->adj[v]; t != G->z; t = t->next){
            STretrieve(G->tab,t->v,&tmp);ITEMshow(tmp);printf("Peso: %d\n",t->wt);
        }
    }
    ITEMfree(tmp);
}
void GRAPHedges(Graph G, Edge *a) {
    int v, E = 0;
    adjLink t=NULL;
    for (v=0; v < G->V; v++){
        for (t=G->adj[v]; t != G->z; t = t->next){
            if (v < t->v){//questo controllo vale per grafi non orientati, se no deve creare ogni volta che trova il vertice nella lista di adiacenza(senza questo controllo)
                a[E++] = EDGEcreate(v, t->v,t->wt);
            }
        }
    }
}
/*int   GRAPHpath(Graph G);
int GRAPHpathH(Graph G);
void GRAPHbfs(Graph G);
void GRAPHdfs(Graph G);
int GRAPHcc(Graph G);
int GRAPHscc(Graph G);*/
#endif





//............................INDIPENDENTI DALLA RAPPRESENTAZIONE............................................



void  GRAPHread(Graph G, FILE *fin){
    int id1, id2, wt;
    Item letturaA=ITEMinit();
    Item letturaB=ITEMinit();
    if (fin == NULL){
        printf("File non trovato, il programma verra' terminato\n");
        exit(-1);
    }
    //in questo modulo utilizzo la item read, dovrò poi modificare il modulo item in modo opportuno per far si che gli item letti siano vertici e vadano bene nel grafo(andrà anche modificata opportunamente la itemread)
    
    ITEMread(fin,&letturaA);//leggo i due item vertici e il peso
    ITEMread(fin,&letturaB);
    fscanf(fin,"%d",&wt);
    
    while(!ITEMcheckvoid(letturaA) && !ITEMcheckvoid(letturaB)){
        id1=STsearchIndex(G->tab,KEYget(letturaA));
        if(id1==-1){
            id1=STinsert(G->tab,letturaA);
        }
        id2=STsearchIndex(G->tab,KEYget(letturaB));
        if(id2==-1){
            id2=STinsert(G->tab,letturaB);
        }
        if(id1>=0 && id2>=0){
            insertE(G,EDGEcreate(id1,id2,wt));
        }
    }
    ITEMfree(letturaA);
    ITEMfree(letturaB);
    return;
}



void  GRAPHwrite(Graph G, FILE *fout){
    int i;
    //char name[51];
    
    Edge a[G->E];
    Item bufStmp1=ITEMinit();
    Item bufStmp2=ITEMinit();
    if (fout == NULL){
        printf("File non trovato, il programma verra' terminato\n");
        exit(-1);
    }
    GRAPHedges(G, a);
    for (i = 0; i < G->E; i++){
        STretrieve(G->tab, a[i].v, &bufStmp1);
        STretrieve(G->tab, a[i].w, &bufStmp2);
        ITEMprint(bufStmp1,fout);
        ITEMprint(bufStmp2,fout);
        fprintf(fout,"%d\n",a[i].wt);
    }
    ITEMfree(bufStmp1);
    ITEMfree(bufStmp2);
    fclose(fout);
    return;
}





void  GRAPHinsert(Graph G){
    Item buf1=ITEMinit();
    Item buf2=ITEMinit();
    int id1, id2, wt;
    printf("Primo vertice = "); ITEMscan(buf1);
    printf("Secondo vertice = "); ITEMscan(buf2);
    printf("Peso arco = "); scanf("%d", &wt);
    id1 = STsearchIndex(G->tab, KEYget(buf1));
    id2 = STsearchIndex(G->tab, KEYget(buf2));
    if (id1 < 0 || id2 < 0){
        printf("Hai inserito dei vertici non esistenti\n");
        return;
    }
    insertE(G, EDGEcreate(id1, id2, wt));
    ITEMfree(buf1);
    ITEMfree(buf2);
    return;
}



void GRAPHloadVerts(Graph G, FILE *fp){
    Item lettura=ITEMinit();
    for(int i=0;i<G->V;i++){
        ITEMread(fp, &lettura);
        if(!ITEMcheckvoid(lettura)){
            STinsert(G->tab, lettura);
        }
    }
    ITEMfree(lettura);
}

void  GRAPHshowVerts(Graph G){
    Item buffer=ITEMinit();
    for(int i=0;i<G->V;i++){
        STretrieve(G->tab, i, &buffer);
        ITEMshow(buffer);
    }
    ITEMfree(buffer);
}

void  GRAPHremove(Graph G){
    Item buf1=ITEMinit();
    Item buf2=ITEMinit();
    int id1, id2;
    printf("Primo vertice = "); ITEMscan(buf1);
    printf("Secondo vertice = "); ITEMscan(buf2);
    id1 = STsearchIndex(G->tab, KEYget(buf1));
    id2 = STsearchIndex(G->tab, KEYget(buf2));
    if (id1 < 0 || id2 < 0){
        printf("Hai inserito dei vertici non esistenti\n");
        return;
    }
    removeE(G, EDGEcreate(id1, id2, 0));
    ITEMfree(buf1);
    ITEMfree(buf2);
    return;
}

//Funzioni che presuppongono di avere la tabella di simboli contenente i vertici completamente carica
int randV(Graph G) {
    return G->V * (rand() / (RAND_MAX + 1.0));
}
Graph GRAPHrand1(Graph G, int V, int E) {
    int vert1,vert2;
    Item v1=ITEMinit();
    Item v2=ITEMinit();
    while (G->E < E){
        vert1=randV(G);
        vert2=randV(G);
        STselect(G->tab,vert1 , &v1);
        STselect(G->tab,vert2 , &v2);
        while(ITEMcheckvoid(v1) || ITEMcheckvoid(v2)){
            vert1=randV(G);
            vert2=randV(G);
            STselect(G->tab,vert1 , &v1);
            STselect(G->tab,vert2 , &v2);
        }
    
        insertE(G, EDGEcreate(vert1, vert2,1));
    }
    return G;
}
Graph GRAPHrand2(Graph G, int V, int E) {
    int i, j;
    double p = 2.0 * E / (V * (V-1));
    for ( i = 0; i < V; i++){
        for ( j = i+1; j < V; j++){
            if (rand() < p * RAND_MAX){
                insertE(G, EDGEcreate(i, j,1));
            }
        }
    }
    return G;
}

void GRAPHfree(Graph G){
    STfree(G->tab);
    free(G);
}
//..........................................................................................................
//...........................................................................................................