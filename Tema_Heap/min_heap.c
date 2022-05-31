#include "min_heap.h"

Heap * create (int capacitate,  int heap_type){
    Heap * h = (Heap *) malloc (sizeof(Heap));
    if (h == NULL)
    {
        printf("Nu s-a putut aloca spatiu");
        return NULL;
    }
    h->size = 0;
    h->capacity = capacitate;
    h->vec = (Data*) malloc(sizeof(Data)*(h->capacity));
    if (h->vec == NULL)
    {
        printf("Nu s-a putut aloca spatiu");
        return NULL;
    }
    return h;
}

void resize(Heap *h)
{
    Data *v=(Data*)realloc( h->vec, h->capacity=h->capacity*2);
    if (v == NULL)
    {
        printf ( "out-of-memory");
        return ;
    }
    if (h->vec!=NULL) free(h->vec);
    h->vec=v;
}


void delete (Heap**h)
{
    if (*h==NULL) return;
    if ((*h)->vec!=NULL) free((*h)->vec);
    free(*h );
    *h=NULL;
}

void printHeap(Heap *h)
{
    int i;
    for (i=0; i<h->size; i++) printf("%d ",h->vec[i]);
    printf("\n");
}

int parent(Heap *h, int i)
{
    if (i>h->size - 1 || i<=0)
        return (-1);
    return (i-1)/2;
}


int leftChild(Heap *h,int i)
{
    int poz = 2*i+1;
    if (poz > h->size -1 || i<0)
        return -1;
    return poz;
}

int rightChild(Heap *h,int i)
{
    int poz = 2*i+2;
    if (poz > h->size-1 || i<0)
        return (-1);
}

Data max(Heap *h)
{
    if (h->size==0)
        return INT_MIN;
    return h->vec[0];
}

void heapify_up( Heap*h, int x)
{int i=h->size;
    while ( i > 0 && x > h->vec[(i-1)/2])
    {
        h->vec[i] = h->vec[(i-1)/2];
        i=(i-1)/2;
    }
    h->vec[i] = x;
}

void heapify_down (Heap *h, int i)
{
    int l, r, max=i, aux;
    l= leftChild(h,i);
    r= rightChild(h,i);
    if(l==-1 && r==-1) return;
    if (l!=-1 && h->vec[l]> h->vec[max]) max = l;
    if (r!=-1 && h->vec[r]> h->vec[max]) max = r;
    if(max!=i)
    {
        aux=h->vec[i];
        h->vec[i]=h->vec[max];
        h->vec[max]=aux;
        heapify_down(h,max);
    }
}

int deleteElement(Heap *h,int *n)
{
 int temp;
 temp=h->vec[1];
 h->vec[1]=h->vec[*n];
 --(*n);
 heapify_down(h,n);
 return temp;
}

void populateHeap ( Heap * h, Data *buf, int n)
{
    if (h==NULL || buf==NULL ||n==0) return;
    while ( n > h->capacity)
        resize(h);
    for (int i=0; i<n; i++)
        h->vec[i]=buf[i];
    h->size = n;

    for (int i=(n-1)/2; i>=0; i--)
        heapify_down(h,i);

}

void insert (Heap *h, Data x)
{
    int i;
    if (h->size==h->capacity) resize(h);
    i=h->size;
    (h->size)++;
    while ( i > 0 && x > h->vec[(i-1)/2])
    {
        h->vec[i] = h->vec[(i-1)/2];
        i=(i-1)/2;
    }
    h->vec[i] = x;
}

/*void deleteRoot(int arr[], int& n)
{
    // Get the last element
    int lastElement = arr[n - 1];

    // Replace root with last element
    arr[0] = lastElement;

    // Decrease size of heap by 1
    n = n - 1;

    // heapify the root node
    heapify(arr, n, 0);
}
*/


void heapsort(Heap *h, Data *buf, int n)
{
    if (h==NULL || buf==NULL ||n==0) return;
    while ( n > h->capacity) resize(h);

    for (int i=0; i<n; i++) h->vec[i]=buf[i];
    h->size = n;
    for (int i=(n-1)/2-1; i>=0; i--)
        heapify_down (h,i);
    for (int i=n-1; i>=0; i--)
    {
        int aux = h->vec[0];
        h->vec[0]=h->vec[i];
        h->vec[i]=aux;
        h->size = i;
        heapify_down(h,0);
    }
    h->size = n;
    printHeap(h);
}



