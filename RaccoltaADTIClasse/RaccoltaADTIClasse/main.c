//
//  main.c
//  RaccoltaADTIClasse
//
//  Created by apple on 28/12/16.
//  Copyright © 2016 emag. All rights reserved.
//

#include <stdio.h>
#include "Item.h"
#include "List.h"
#include "PQ.h"
#include "Tree.h"
#include "BST.h"
#include "Heap.h"
#define LISTA 1
//#define PQ 1
#define Tree 1
#define BIESSETTI 1
#define TESTHEAP 1

int main(int argc, const char * argv[]) {
#ifndef LISTA
    //Test di list.h
    List lista=LISTinit();
    Item x=NULL;
    Key chiave;
    FILE *fin=NULL;
    FILE *fout=NULL;
    Item estratto=ITEMinit();
    Item ottenuto=ITEMinit();
    int numeroNodi=0;
    /*printf("\t\t\tQuanti nodi vuoi inserire in lista??\n");
    scanf("%d",&numeroNodi);
    for(int i=0;i<numeroNodi;i++){
        x=ITEMinit();
        printf("\t\tInserisci nome e punteggio separati da uno spazio\n");
        x=ITEMscan(x);
        LISTinsertHead(x, lista);
    }*/
    fin=fopen("item.txt", "r");
    LISTreadF(fin, lista);
    LISTextractTail(lista, &estratto);
    printf("La lista che hai caricato in memoria è:\n");
    LISTdisplay(lista);
    printf("L elemento che ho estratto è:\n");
    ITEMshow(estratto);
    printf("Inserisci la chiave di un item(punti):\n");
    chiave=KEYscan();
    printf("Uso la shownode:\n");
    LISTshowNode(chiave, lista);
    lista=LISTreverse(lista);
    printf("Lista invertita\n");
    LISTdisplay(lista);
    fout=fopen("provaScrittura.txt","w");
    LISTprintF(fout,lista);
    //ottenuto=LISTgetItem(chiave, lista);
    //printf("L elemento che ho ottenuto con la get e'\n");
    //ITEMshow(ottenuto);
    //LISTextract(chiave, lista, &estratto);
    //printf("Ho anche estratto questo item e vale:\n");
    //printf("(Cancello anche l item che ho ottenuto)\n");
    //LISTdeleteNode(ottenuto, lista);
    //ITEMshow(estratto);
    LISTfree(lista);
    ITEMfree(estratto);
    //ITEMfree(ottenuto);
#endif
#ifndef PQ
    Item temp=ITEMinit();
    PQ coda=PQinit();
    FILE *fin=fopen("partecipanti.txt","r");
    PQreadF(fin,coda);
    printf("Coda a priorità letta:\n");
    PQdisplay(coda);
    printf("Estraggo il nodo a priorità più alta\n");
    PQextractMax(coda, &temp);
    ITEMshow(temp);
    printf("Dopo estrazione:\n");
    PQdisplay(coda);
    printf("Test di PQshowmax\n");
    PQshowMax(coda);
    FILE *fout=fopen("provaSalvataggio.txt","w");
    PQprintF(fout, coda);
    PQfree(coda);
#endif
#ifndef Tree
    //Item tmp=ITEMinit();
    Item vett[10];
    Tree alberoProva=TREEinit();
    FILE *fin=fopen("provaAlbOutput.txt","r");
    //FILE *fout=fopen("provaAlbOutput.txt","w");
    TREEreadF(fin, &alberoProva);
    TREEdisplay(alberoProva);
    for(int i=0;i<TREEcountNodes(alberoProva);i++){
        vett[i]=ITEMinit();
    }
    /*printf("Inserisci nome e punteggio di un partecipante: ");
    ITEMscan(tmp);
    TREEinsert(alberoProva, tmp);
    printf("Inserisci nome e punteggio di un partecipante: ");
    ITEMscan(tmp);
    TREEinsert(alberoProva, tmp);
    printf("Inserisci nome e punteggio di un partecipante: ");
    ITEMscan(tmp);
    TREEinsert(alberoProva, tmp);
    TREEprintF(fout, alberoProva);*/
    /*printf("inserisci la chiave di un nodo: ");
    Key k1=KEYscan();
    printf("inserisci la chiave di un nodo: ");
    Key k2=KEYscan();
    printf("I due nodi distano: %d\n",TREEdistNodes(alberoProva, k1, k2));*/
    TREEsortpreorder(alberoProva, vett, TREEcountNodes(alberoProva));
    printf("Vettore risultante dal preorder:\n");
    for(int i=0;i<TREEcountNodes(alberoProva);i++){
        ITEMshow(vett[i]);
    }
    TREEfree(alberoProva);
    fclose(fin);
    //fclose(fout);
#endif
#ifndef BIESSETTI
    Item ordinamento[10];
    Item ins=ITEMinit();
    Key cerca;
    Item save=ITEMinit();
    BST testBst=BSTinit();
    FILE *fin=NULL,*fout=NULL;
    fin=fopen("testBST.txt", "r");
    BSTreadF(fin,&testBst);
    BSTdisplay(testBst);
    //fout=fopen("provaScriviBST.txt","w");
    //BSTprintF(fout, testBst);
    printf("Il numero di nodi nel BST è: %d\n",BSTcount(testBst));
    //printf("Inserisci la chiave di un item: ");
    //cerca=KEYscan();
    printf("Inserisci un item da mettere in radice: ");
    ITEMscan(ins);
    BSTinsert_root(testBst, ins);
    BSTdisplay(testBst);
    /*BSTsearch(testBst, cerca, &save);
    printf("Ho trovato: \n");
    ITEMshow(save);
    BSTmin(testBst,&save);
    printf("Il minimo e':\n");
    ITEMshow(save);
    BSTmax(testBst,&save);
    printf("Il massimo e':\n");
    ITEMshow(save);*/
    //printf("Inserisci un item che vuoi cancellare:\n");
    //ITEMscan(ins);
    //BSTdelete(testBst, cerca);
    //BSTdisplay(testBst);
   /* printf("L item con la 2a chiave piu piccola e':\n");
    BSTselect(testBst, 1, &save);
    ITEMshow(save);
    for(int i=0;i<BSTcount(testBst);i++){
        ordinamento[i]=ITEMinit();
    }
    BSTsortinorder(testBst, ordinamento, BSTcount(testBst));
    printf("\nBST visitato in order\n");
    for(int i=0;i<BSTcount(testBst);i++){
        ITEMshow(ordinamento[i]);
    }
    BSTsortpreorder(testBst, ordinamento, BSTcount(testBst));
    printf("\nBST visitato in preorder\n");
    for(int i=0;i<BSTcount(testBst);i++){
        ITEMshow(ordinamento[i]);
    }
    BSTsortpostorder(testBst, ordinamento, BSTcount(testBst));
    printf("\nBST visitato in postorder\n");
    for(int i=0;i<BSTcount(testBst);i++){
        ITEMshow(ordinamento[i]);
    }
    printf("Inserisci un item di cui vuoi cercare il successore:\n");
    ITEMscan(ins);
    BSTsucc(testBst, KEYget(ins), &save);
    printf("successore: ");
    ITEMshow(save);
    printf("Inserisci un item di cui vuoi cercare il predecessore:\n");
    ITEMscan(ins);
    BSTpred(testBst, KEYget(ins), &save);
    printf("predecessore: ");
    ITEMshow(save);*/
#endif
#ifndef TESTHEAP
    FILE *fout=NULL;
    FILE *fin=NULL;
    Heap testH=HEAPinit(5);
    Item buffer=ITEMinit();
    struct tree *x=TREEinit();
    for(int i=0;i<5;i++){
        printf("Inserisci un elemento da mettere nell heap: ");
        ITEMscan(buffer);
        HEAPfill(testH, buffer);
        printf("\n");
    }
    printf("Prima di costruire l heap:\n");
    HEAPdisplay(testH);
    HEAPbuild(testH);
    printf("Dopo aver costruito l heap:\n");
    HEAPdisplay(testH);
    fout=fopen("provaStampaHeap.txt","w");
    HEAPprintF(fout, testH);
    fclose(fout);
    fin=fopen("provaStampaHeap.txt", "r");
    TREEreadF(fin, &x);
    printf("Heap come albero:\n");
    TREEdisplay(x);
    HEAPsort(testH);
    printf("Heapsort:\n");
    HEAPdisplay(testH);
#endif
    return 0;
}




