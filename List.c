//Brittany Arthur

#include "List.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void freeNode(Node* pN);

List newList(void)
{
    List list = (List)malloc(sizeof(struct List));
    list->head = NULL;
    list->tail = NULL;
    list->length = 0; 

    list->cursor = NULL;
    list->index = -1;

    return list;
}

int length(List L){
  if(L==NULL){return -1;}
   return L->length;
}

int getIndex(List L){
   return L->index;
}

// Returns front element in this list. Pre: length()>0
int front(List L){
   if(L==NULL){
     printf("NULL list, returning -1 value\n");
     return -1;
   }
   if (L->length > 0){ 
      return L->head->data;
   }
    else{
      printf("Error: empty list\n\n");
   }
   return 0;
}

int back(List L){
   if (L->length > 0){
      return L->tail->data;
   }
    else{
      fprintf(stderr, "empty list\n\n");
   }
   return 0;
}

int getElement(List L){
   assert((L->length > 0)&&(getIndex(L)>=0));
   //
   if(L->cursor!= NULL){
      return L->cursor->data;
   }
   return 0;
}

int equals(List A, List B){

   Node* nodeA = A->head; 
   Node* nodeB = B->head; 
   if(A->length != B->length){
      return 0;
   }
   while(nodeA != NULL && nodeB != NULL){
      if(nodeA->data == nodeB->data){
         nodeA = nodeA->next;
         nodeB = nodeB->next;
      }else{
         return 0;
      }
   }
   return 1;
}

   void clear(List L){
      L->head = NULL;
      L->tail = NULL;
      L->cursor = NULL;
      L->index = -1; //when off end
      L->length = 0;
   }

   void moveTo(List list, int index)
{
    if (list == NULL){ return;}
    if (list->length == 0){ return;}

    if (list->cursor == NULL)
    {
        list->cursor = list->head;
        list->index = 0;
    }

    Node* current = list->head;
    int i = 0;

    while(current != NULL)
    {
        if (i == index)
        {
            list->cursor = current;
            list->index = i;
            return;
        }

        current = current->next;
        ++i;
    }

    list->cursor = NULL;
    list->index = -1;
}

void movePrev(List list)
{   
    if(getIndex(list)==0){
       list->cursor = NULL;
    }
    //
    if (list == NULL) return;

    if (list->cursor == NULL)
    {
        list->cursor = list->head;
        list->index = 0;
        return;
    }

    list->cursor = list->cursor->previous;

    if (list->cursor != NULL)
    {
        --list->index;
    }
    else
    {
        list->index = -1;
    }
}

void moveNext(List list)
{   
   // if(getIndex(list)==list->length-1){
   //    list->cursor = NULL;
   // }
   //
    if (list == NULL){ return;}
    if (list->length == 0){ return;}

    if (list->cursor == NULL)
    {
        list->cursor = list->head;
        list->index = 0;
        return;
    }

    list->cursor = list->cursor->next;

    if (list->cursor != NULL)
    {
        ++list->index;
    }
    else
    {
        list->index = -1;
    }
}

void prepend(List list, int data) //Node* node
{
   Node* node = (Node*)malloc(sizeof(Node));
   node->data = data;

    if (list == NULL){ printf("list is null\n"); return;}
    if (node == NULL){ printf("node is null\n"); return;}

    ++list->length;
    if (list->index != -1)
    {
        ++list->index;
    }

    if (list->head == NULL)
    {
        list->head = node;
        list->tail = node;
        return;
    }

    list->head->previous = node;
    node->next = list->head;
    node->previous = NULL;
    list->head = node;
}

void append(List list, int data)
{
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = data;
    if (length(list) == 0)       
    {  
       ++list->length;
       list->head = node;
       list->tail = node;
       return;
    }
    ++list->length;

    list->tail->next = node;
    node->previous = list->tail;
    list->tail = node;
} 

void insertBefore(List list, int data)
{
   //temp to debug
   if(getIndex(list)<0){
   //moveTo(list,0);
   }

    //assert(list->length>0 && getIndex(list) >= 0);
   if(list->length<=0){
     printf("list length was less than or equal to 0");
   }    
    if(getIndex(list)<0){
      printf("index was less than 0");
    }
    
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = data;
	
    if (list == NULL){ printf("list was NULL ");return;}
    //if (node == NULL) return;
    if (list->cursor == NULL) {printf("cursor was NULL"); return;}

    node->previous = list->cursor->previous;

    if (node->previous != NULL)
    {
        node->previous->next = node;
    }

    node->next = list->cursor;
    list->cursor->previous = node;

    if (list->index != -1)//i had this commented out for prog4 submission
    {
        ++list->index;
    }
   // if(list->length == 2){//added Aug6
   //    list->head = node;
   // }
} 

void insertAfter(List list, int data)
{
    assert(list->length>0); 
    assert(getIndex(list) >=0);

    Node* node = (Node*)malloc(sizeof(Node));
    node->data = data;
	
    if (list == NULL){ return;}
    //if (node == NULL) return;
    if (list->cursor == NULL){ return;}
    ++list->length;
 
    node->next = list->cursor->next;

    if (node->next != NULL)
    {
        node->next->previous = node;
    }

    if(list->cursor->next == NULL){///added Aug 6
      list->tail = node; 
    }    

    node->previous = list->cursor;
    list->cursor->next = node;
} 

void deleteFront(List list)
{
    assert(list->length>0);
    if (list == NULL){  
      return;
    }
    if (list->length == 0){ 
      return;
    }

    if (list->cursor == list->head)
    {
        list->cursor = NULL;
        list->index = -1;
    }

  ///  Node* temp = list->head;

    list->head = list->head->next;

    if (list->head != NULL)
    {
        list->head->previous = NULL;
    }

    --list->length;
    --list->index;
    
   //free(temp);
}

void deleteBack(List list)
{
    assert(list->length>0);
    if (list == NULL) return;
    if (list->length == 0) return;

    if (list->cursor == list->tail)
    {
        list->cursor = NULL;
        list->index = -1;
    }

    list->tail = list->tail->previous;
    Node* temp = list->tail;//7

    if (list->tail != NULL)
    {
        list->tail->next = NULL;
    }

    --list->length;
    free(temp);//7
    //*temp = NULL;
    ///free(temp);
}

void delete(List list)
{
    assert(list->length>0 && getIndex(list)>=0);
    if (list == NULL) return;
    if (list->cursor == NULL) return;

    if (list->cursor->previous != NULL)
    {
        list->cursor->previous->next = list->cursor->next;
    }
    else
    {
        list->head = list->cursor->next;
    }

    if (list->cursor->next != NULL)
    {
        list->cursor->next->previous = list->cursor->previous;
    }
    else
    {
        list->tail = list->cursor->previous;
    }

    list->cursor->next = NULL;
    list->cursor->previous = NULL;

    list->cursor = NULL;
    list->index = -1;

    --list->length;
    free(list->cursor);
}

void printList(FILE* out, List list)
{
    if (list == NULL) return;
    if (list->head == NULL) return;

    Node* current = list->head;

   // while (current != NULL)
   for(int itor = 0; itor < list->length; itor++){
    
        fprintf(out, "%i ", current->data);
        current = current->next;
    
   }
}

List copyList(List L){
   List copy = (List)malloc(sizeof(List));
   L->cursor = L->head;
   moveTo(L, 0);
   for(int itor = 0; itor < L->length; itor++){
        append(copy, getElement(L));
        moveNext(L); 
   }
   copy->length = L->length; 
   return copy;   
}

void sorting(List A){
   for(int q = 1; q < A->length; q++){
      moveTo(A,q);
      while(A->index > 0){
      if(A->cursor->data < A->cursor->previous->data){
         int temp = A->cursor->data;
         A->cursor->data = A->cursor->previous->data;
         A->cursor->previous->data = temp;
      }
      movePrev(A);
      }
   }
}


void freeList(List* list)
{
   if (*list == NULL) return;
   Node* current = (*list)->head;//save
   while (current != NULL)
   {
     Node* temp = current->next;
     if(current!=NULL){
      freeNode(current);
     }
     current = temp;
   }
}

// freeNode()
// Frees heap memory pointed to by *pN, sets *pN to NULL.
void freeNode(Node* pN){
   if( pN!=NULL && pN!=NULL){
      free(pN);
      pN = NULL;
   }
}
