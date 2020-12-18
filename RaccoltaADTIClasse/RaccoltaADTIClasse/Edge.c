//
//  Edge.c
//  RaccoltaADTIClasse
//
//  Created by apple on 10/01/17.
//  Copyright © 2017 emag. All rights reserved.
//

#include "Edge.h"
Edge EDGEcreate(int v, int w, int wt) {
    Edge e;
    e.v = v;
    e.w = w;
    e.wt = wt;
    return e;
}
