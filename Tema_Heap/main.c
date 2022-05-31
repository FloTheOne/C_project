#include "min_heap.h"
int main ()
{

    int n;

    Heap *hh = create(5, 0);
    scanf("%d",&n);
    Data *buf = (int *)malloc(n*sizeof(Data));
    for (int i=0; i<n; i++) scanf("%d",&buf[i]);
    populateHeap(hh, buf, n);
    printHeap(hh);
    printf("\n%d ",  parent(hh,3));
    printf("\n%d ", max(hh));
    printf("\n");
    printf("\n%d ", leftChild(hh,1));
    printf("\n");
    printf("\n%d ",rightChild(hh,1));
    printf("\n");


    heapsort(hh,buf,n);
    return 0;

}
