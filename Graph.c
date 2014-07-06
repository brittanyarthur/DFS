//Brittany Arthur

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Graph.h"

struct Graph{
  int size;   //stores the number of edges
  int order;  //stores the number of vertices
  int time;
  List *adj;  //stores the adjacency list
  int *color; 
  int *discover;
  int *finish;
  int *parent;
};

void Visit (Graph G, int x, List L);

// Constructors-Destructors 
Graph newGraph(int n){
 Graph tmp = malloc(sizeof(struct Graph));
 assert(tmp != NULL);
 tmp->size = 0;
 tmp->time = 0;
 tmp->order = n; 
 tmp->adj = calloc(n+1, sizeof(List));
 tmp->color = calloc(n+1, sizeof(int));
 tmp->discover = calloc(n+1, sizeof(int));
 tmp->finish = calloc(n+1, sizeof(int));
 tmp->parent = calloc(n+1, sizeof(int));
 /*initializing values*/
 for(int itor = 1; itor <= n; itor++){
   tmp->adj[itor] = newList();
   tmp->color[itor] = 0;
   tmp->discover[itor] =INF; 
   tmp->finish[itor] =INF; 
   tmp->parent[itor] = NIL;
 }
 return tmp; 
}

void freeGraph(Graph* pG){
  if(*pG == NULL||pG==NULL){
   return; 
  }
  for(int i=1; i <= getOrder(*pG); i++){
    freeList(&(*pG)->adj[i]); 
  }
  free((*pG)->color); 
  free((*pG)->discover); 
  free((*pG)->finish); 
  free((*pG)->parent); 
  free((*pG)->adj);
  free(*pG);
  *pG=NULL;  
}

// Access functions
/*returns number of vertices in Graph G*/
int getOrder(Graph G){
 assert(G != NULL);
 return G->order;
}

/*returns number of edges in Graph G*/
int getSize(Graph G){
 assert(G != NULL);
 return G->size;
}

//are there any new return functions that i need?
int getParent(Graph G, int u){
 assert(G!=NULL);
 if(!(1<= u)||!(u<= getOrder(G))){
   printf("vertex does not exist");
   exit(1);
 }
 return G->parent[u];
}

//get Finish
int getFinish(Graph G, int u){
 assert(G!=NULL);
 if(!(1<= u)||!(u<= getOrder(G))){
   printf("vertex does not exist");
   exit(1);
 }
 return G->finish[u]; 
}

//get Discover
int getDiscover(Graph G, int u){
 assert(G!=NULL);
 if(!(1<= u)||!(u<= getOrder(G))){
   printf("vertex does not exist");
   exit(1);
 }
 return G->discover[u]; 
}

//addEdge() inserts a new edge joining u to v, i.e. u is added to the adjacency List of v, and v to the adjacency List of u.
void addEdge(Graph G, int u, int v){
  if(G==NULL){
    printf("Cannot add edge to NULL graph");
    exit(1);
  }
 if(!(1<= u)||!(u<= getOrder(G))){
   printf("u vertex does not exist");
   exit(1);
 }
 if(!(1<= v)||!(v<= getOrder(G))){
   printf("v vertex does not exist");
   exit(1);
 }

  //add v to u
  append(G->adj[u],v);
  //add u to v
  append(G->adj[v], u);
  sort(G);
}

void sort(Graph G){
for(int i = 1; i <= G->order; i++){
  sorting(G->adj[i]);
}
}

//addArc() inserts a new directed edge from u to v, i.e. v is added to the adjacency List of u (but not u to the adjacency List of v). 
void addArc(Graph G, int u, int v){
 if(!(1<= u)||!(u<= getOrder(G))){
   printf("u vertex does not exist");
   exit(1);
 }
 if(!(1<= v)||!(v<= getOrder(G))){
   printf("v vertex does not exist");
   exit(1);
 }
  //add v to u
  append(G->adj[u],v);
}

void DFS(Graph G,List L){
  for(int i = 1; i <= getOrder(G); i++){ 
    G->color[i] = 0;
    G->parent[i] = NIL;
    G->discover[i] = INF;
    G->finish[i] = INF;
  }
  List A = newList();
  //G->connected = 0; //reset in case DFS is ran multiple times
  G->time = 0;
  for(int j = 0; j < length(L); j++){
    moveTo(L,j);
    if(G->color[getElement(L)]==0){
      int vis = getElement(L);
      Visit(G, vis, A);
    }
    moveNext(L);
  } 
  clear(L);
   moveTo(A, 0);
   for(int itor = 0; itor < length(A); itor++){
        append(L, getElement(A));
        moveNext(A); 
   }
   L->length = A->length; 
   //freeList(&A);
}

void Visit (Graph G, int x, List A){
  G->color[x]=1; 
  ++G->time;
  G->discover[x] = G->time;
  int k;  
  moveTo(G->adj[x],0); 
  for(k = 0; k < length(G->adj[x]); k++){
      if(G->color[getElement(G->adj[x])]==0){
         G->parent[getElement(G->adj[x])]=x;
         int vis = getElement(G->adj[x]);
         Visit(G,vis,A);
      }
      moveNext(G->adj[x]); 
  }
    G->color[x]=2;
    ++G->time;
    G->finish[x]= G->time;
    prepend(A,x);
}

///*** Other operations ***/
void printGraph(FILE* out, Graph G){
  if(G==NULL){
    fprintf(out, "Error: Cannot print a NULL graph");
    exit(1);
  }
  for(int i = 1; i <= getOrder(G); i++){
    sorting(G->adj[i]);
    fprintf(out, "%d: ",i);
    if(length(G->adj[i])>0){
      moveTo(G->adj[i],0);
      for(int y = 0; y < length(G->adj[i]); y++){
      moveTo(G->adj[i],y);
       int curr = getElement(G->adj[i]);
       fprintf(out, " %d ", curr);
       }
    }
    fprintf(out, "\n");
  }  
}

Graph transpose(Graph G){
assert(G!=NULL);
Graph G2 = newGraph(getOrder(G)); // make a graph with same num vertices

for(int i =1; i <= G->order; ++i){
 for(int k = 0; k < length(G->adj[i]);++k){
   moveTo(G->adj[i],k);
   int getvalue = getElement(G->adj[i]);
   addArc(G2, getvalue, i);
 }
}
return G2;
}

Graph copyGraph(Graph G){
assert(G!=NULL);
Graph A = newGraph(getOrder(G));
A->size = G->size;
A->order = G->order;
for (int i = 0; i <= G->order; ++i){
  for(int j = 0; j < length(G->adj[i]); ++j){
    moveTo(G->adj[i],j);
    int value = getElement(G->adj[i]);
    addArc(A, i, value);
  }
A->color[i] = G->color[i];
A->discover[i] = G->discover[i];
A->finish[i] = G->finish[i];
A->parent[i] = G->parent[i];
}

return A;
}


