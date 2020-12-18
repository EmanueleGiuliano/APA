//
//  Graph.h
//  RaccoltaADTIClasse
//
//  Created by apple on 10/01/17.
//  Copyright © 2017 emag. All rights reserved.
//

#ifndef Graph_h
#define Graph_h

#include <stdio.h>
#include "Edge.h"
#include "ST.h"


typedef struct graph *Graph;
Graph GRAPHinit(int dim);
void  GRAPHread(Graph G, FILE *fin);
void  GRAPHwrite(Graph G, FILE *fout);
void  GRAPHinsert(Graph G);
void  GRAPHremove(Graph G);
void  GRAPHshow(Graph G);
void  GRAPHshowVerts(Graph G);
void  GRAPHedges(Graph G, Edge *a);
int   GRAPHpath(Graph G);
int GRAPHpathH(Graph G);
void GRAPHbfs(Graph G);
void GRAPHdfs(Graph G);
int GRAPHcc(Graph G);
int GRAPHscc(Graph G);
void GRAPHloadVerts(Graph G, FILE *fp);
void GRAPHloadEdges(Graph G, FILE *fp);
Graph GRAPHrand1(Graph G, int V, int E);
Graph GRAPHrand2(Graph G, int V, int E);
#endif /* Graph_h */
