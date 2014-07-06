//Brittany Arthur

#ifndef LIST_H
#define LIST_H

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{ 
    struct Node* next;
    struct Node* previous;
    int data;
} Node;

struct List
{
Node* head;
Node* tail;
int length;

Node* cursor;
int index;
};

typedef struct List* List;

// Constructors-Destructors 
List newList(void);
void freeList(List* list);

// Access functions 
int length(List L);
int getIndex(List L);
int front(List L);
int back(List L);
int getElement(List L);
int equals(List A, List B);

// Manipulation procedures 
void clear(List L);
void moveTo(List list, int index);
void movePrev(List list);
void moveNext(List list);
void prepend(List list, int data);
void append(List list, int data);
void insertBefore(List list, int data);
void insertAfter(List list, int data);
void deleteFront(List list);
void deleteBack(List list);
void sorting(List list);
void delete(List list);

// Other operations 
void printList(FILE* out, List list);
List copyList(List L);

#endif
