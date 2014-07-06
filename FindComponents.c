//Brittany Arthur
//CMPS101
//takes 2 command line arguments, input and output file

#include<stdio.h> 
#include<stdlib.h>
#include<string.h>

#include "Graph.h"
#include "List.h"

#define MAX_LEN 250

int main(int argc, char * argv[]){

   FILE *in, *out;
   char line[MAX_LEN];
  // char line_out[MAX_LEN];
   Graph G;
   char ch = '\0';
   int line_count = 0;
   int connected = 0;
   
   // check command line for correct number of arguments
   if( argc != 3 ){
      printf("Usage: %s <input file> <output file>\n", argv[0]);
      exit(1);
   }

   // open files for reading and writing 
   in = fopen(argv[1], "r");
   out = fopen(argv[2], "w");
   if( in==NULL ){
      printf("Unable to open file %s for reading\n", argv[1]);
      exit(1);
   }
   if( out==NULL ){
      printf("Unable to open file %s for writing\n", argv[2]);
      exit(1);
   }
   while (EOF != (ch = fgetc(in)))
   {
       if (ch == '\n')
       {
           ++line_count;
       }
   }

   rewind(in);
   
    int i, u, v, n;
    for (i = 0; i < line_count; ++i)
    {  
       if(i==0){
        //input number of vertices into G
        fgets(line, sizeof(line),in);
        sscanf(line, "%d", &n);
        G = newGraph(n);
        continue;
       }

       //line is read is and stored in line
       fgets(line, sizeof(line), in);
       sscanf(line, "%d %d", &u, &v);
       if(u+v==0){
         break; 
       }
      addArc(G,u,v);       
    }
   fprintf(out,"Adjacency list representation of G:\n");
   printGraph(out,G);
   fprintf(out,"\n\n");
   List S = newList();
   Graph T = transpose(G);
   for(i=1; i<=getOrder(G); i++) append(S, i);
   DFS(G,S);
   DFS(T,S);
   for(int count = 1; count <= getOrder(G); count++){
     if(getParent(T, count) == 0){
       ++connected;
     }
   } 
   fprintf(out, "\nGraph G contains %d strongly connected components:\n",connected);
   int flag = 0; 
   int print_comp = 1;
   for(int component = connected; component > 0; component--){
      fprintf(out, "Component %d:",print_comp);
      ++print_comp;
      moveTo(S,0);
      while(getIndex(S)!=-1){
      if(getParent(T,getElement(S))==0){
        ++flag;
      }
      if(flag == component){
       fprintf(out," %d ",getElement(S));
      }
      moveNext(S);
      }
      fprintf(out,"\n");
      flag = 0;
   }
   
   // close files 
   freeGraph(&G);
   freeGraph(&T);
   freeList(&S);
   fclose(in);
   fclose(out);
   return(0);
}

