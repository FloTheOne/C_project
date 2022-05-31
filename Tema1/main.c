#include "header.h"
/* in acest fisier este d.in -12 */
int main()
{
    FILE *intrare, *iesire;
    Echipe *head;
    int nr_echipe,nr_ramase;
    Queue *q=createQueue();
    Queue *top8=createQueue();
    arbore * root=NULL;

    intrare=fopen ("d.in","r");
    iesire=fopen ("d.out", "w");
//1//
    head=citire(intrare,iesire,&nr_echipe);
    admisi(nr_echipe, &nr_ramase);
//2//
    int echipe_sterse=nr_echipe-nr_ramase;
    head=stergere(echipe_sterse,head);
    q=primul_queue( head, nr_ramase);
    afisare(head,iesire);
//3//
    top8=afisare_2 (iesire,q,nr_ramase);
//4//
    root=afisare_tree(iesire,top8);
    inorder(root,iesire);
    free_tree(root);
    free_Echipe(head);
}
