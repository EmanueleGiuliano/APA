//
//  Edge.h
//  RaccoltaADTIClasse
//
//  Created by apple on 10/01/17.
//  Copyright © 2017 emag. All rights reserved.
//

#ifndef Edge_h
#define Edge_h

#include <stdio.h>
typedef struct edge { int v; int w; int wt; } Edge;
Edge EDGEcreate(int v, int w, int wt);
#endif /* Edge_h */
