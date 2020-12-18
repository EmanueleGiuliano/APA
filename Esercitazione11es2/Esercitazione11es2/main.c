//
//  main.c
//  Esercitazione11es2
//
//  Created by apple on 16/01/17.
//  Copyright © 2017 emag. All rights reserved.
//

#include <stdio.h>
#include "HeapPQ.h"
#include "Item.h"
int main(int argc, const char * argv[]) {
    PQ pq = PQinit(20);
    Item tmp=ITEMinit();
    ITEMsetCod(tmp,"ciao");
    ITEMsetPrio(tmp,4);
    PQinsert(tmp,pq);
    ITEMsetCod(tmp,"come");
    ITEMsetPrio(tmp,7);
    PQinsert(tmp,pq);
    ITEMsetCod(tmp,"va");
    ITEMsetPrio(tmp,5);
    PQinsert(tmp,pq);
    PQdisplay(pq);
    printf("\n---------\n");
    while(!PQempty(pq)) {
        PQextract(pq,&tmp);
        ITEMshow(tmp);
    }
    
    return 0;
}
