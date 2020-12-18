//
//  main.c
//  Esercitazione11es01
//
//  Created by apple on 13/01/17.
//  Copyright © 2017 emag. All rights reserved.
//

#include <stdio.h>
#include "Graph.h"
int main(int argc, const char * argv[]) {
    FILE *fin = fopen(argv[1],"r");
    Graph rete=NULL;
    int numeroVertici=0;
    fscanf(fin, "%d",&numeroVertici);
    rete=GRAPHinit(numeroVertici);
    GRAPHloadVerts(rete, fin);
    printf("Ho letto i seguenti vertici:\n");
    GRAPHshowVerts(rete);
    /*ST prova=STinit(10);
    Item tmp=ITEMinit();
    ITEMscan(tmp);
    STinsert(prova, tmp);
    ITEMscan(tmp);
    STinsert(prova, tmp);
    ITEMscan(tmp);
    STinsert(prova, tmp);
    STshow(prova);*/
    return 0;
}
