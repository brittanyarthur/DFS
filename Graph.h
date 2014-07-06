//Brittany Arthur

#ifndef GRAPH_H
#define GRAPH_H

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "List.h"

#define INF -1
#define NIL 0

typedef struct Graph* Graph;

/*** Constructors-Destructors ***/
Graph newGraph(int n);
void freeGraph(Graph* pG);
/*** Access functions ***/
int getOrder(Graph G);
int getSize(Graph G);
int getSource(Graph G);
int getParent(Graph G, int u);
int getDiscover(Graph G, int i);
int getFinish(Graph G, int i);
/*** Manipulation procedures ***/
void addEdge(Graph G, int u, int v);
void addArc(Graph G, int u, int v);
void DFS(Graph G, List L); /* Pre: getLength(S)==getOrder(G) */
/*** Other Functions ***/
void printGraph(FILE* out, Graph G);
void sort(Graph G);
Graph transpose(Graph G);
Graph copyGraph(Graph G);
#endif
