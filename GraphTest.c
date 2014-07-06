//Brittany Arthur

#include<stdio.h>
#include<stdlib.h>
#include"List.h"
#include"Graph.h"


int main(int argc, char* argv[]){
   int i, n=6;
   List S = newList();
   Graph G = newGraph(n);
   Graph T=NULL;//, C=NULL;

   for(i=1; i<=n; i++) append(S, i);

   addArc(G,1 , 2);
   addArc(G,2 ,3);
   addArc(G,3 , 4);
   addArc(G,4 ,3);
   addArc(G,5 ,6);
   addArc(G,6 ,1);
   addArc(G,3 ,6);
   printGraph(stdout, G);

   DFS(G, S);
   fprintf(stdout, "\n");
   fprintf(stdout, "x:  d  f  p\n");
   for(i=1; i<=n; i++){
      fprintf(stdout, "%d: %2d %2d %2d \n", i, getDiscover(G, i), getFinish(G, i), getParent(G, i));
   }
   fprintf(stdout, "\n");
   printList(stdout, S);
   fprintf(stdout, "\n");

   T = transpose(G);
   
   //C = copyGraph(G);
   //fprintf(stdout, "\n");
   //printGraph(stdout, C);
   fprintf(stdout, "\n");
   printGraph(stdout, T);
   fprintf(stdout, "\n");

   DFS(T, S);
   fprintf(stdout, "\n");
   fprintf(stdout, "x:  d  f  p\n");
   for(i=1; i<=n; i++){
      fprintf(stdout, "%d: %2d %2d %2d\n", i, getDiscover(T, i), getFinish(T, i), getParent(T, i));
   }
   fprintf(stdout, "\n");
   printList(stdout, S);
   fprintf(stdout, "\n");
//
//
int connected = 0;
   for(int count = 1; count <= getOrder(G); count++){
     if(getParent(T, count) == 0){
       ++connected;
     }
   } 
   printf("\nGraph G contains %d strongly connected components:\n",connected);
   int flag = 0; 
   int print_comp = 1;
   for(int component = connected; component > 0; component--){
      printf("Component %d:",print_comp);
      ++print_comp;
      moveTo(S,0);
      while(getIndex(S)!=-1){
      if(getParent(T,getElement(S))==0){
        ++flag;
      }
      if(flag == component){
       printf(" %d ",getElement(S));
      }
      moveNext(S);
      }
      printf("\n");
      flag = 0;
   }



//
   freeList(&S);
   freeGraph(&G);
   return(0);
}
