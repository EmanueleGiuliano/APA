//
//  PQ.h
//  Esercitazione9es2
//
//  Created by apple on 17/12/16.
//  Copyright © 2016 emag. All rights reserved.
//

#include "Item.h"
#include <stdlib.h>
#ifndef PQ_h
#define PQ_h
//NB implementazione come "non-adt" per cui al main non è possibile dichiarare variabili di tipo PQ
int PQempty();
void PQinsert(Item val);
Item PQextractMax();
Item PQshowMax();
void PQdisplay();
void PQchange(Item x);
void PQdelete(Item x);
#endif /* PQ_h */
