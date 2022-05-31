#ifndef MIN_HEAP_H_INCLUDED
#define MIN_HEAP_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef int Data;
typedef struct
{
    Data *vec;
    int size, capacity;
} Heap;

Heap * create (int,  int);
void resize(Heap *);
void delete (Heap**);
void printHeap(Heap *);
int parent(Heap *, int );
int leftChild(Heap *,int );
int rightChild(Heap *h,int i);
Data max(Heap *h);
void heapify_up( Heap*h, int i);
void heapify_down (Heap *h, int i);
void populateHeap ( Heap * h, Data *buf, int n);
void insert (Heap *h, Data x);
void heapsort(Heap *h, Data *buf, int n);



#endif // MIN_HEAP_H_INCLUDED
