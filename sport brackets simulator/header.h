#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED

/*Comentarii:
Exemplul din checker nu corespunde cu cerinta:"In cazul unui meci in care ambele echipe au acelasi punctaj, se va alege prima echipa adaugata in meciul disputat." - aici se alege a 2 a echipa
La unele exemple din checker (d.in-15 de exemplu ) unele cuvinte au spatiu la final (ALIEN PANTHERS ALIENS)
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Player
{
    char* firstName;
    char* secondName;
    int points;
    struct Player* next;
} player;

typedef struct elem
{
    int nr_membrii;
    char *nume_echipa;
    player *val;
    float puncte_echipa;
    float pozitie;
    struct elem* next;
} Echipe;

typedef struct node
{
    Echipe *val;
    struct node* next;
} Node;

typedef struct Q
{
    Node *front, *rear;
} Queue;

typedef struct N
{
    float val;
    Echipe *echipe;
    struct N *left,*right;
} arbore;

void push(Node**, Echipe *);
int isEmptyStack(Node*);
Echipe* pop(Node**);
Queue* createQueue();
void enQueue(Queue*, Echipe *);
int isEmpty(Queue*);
Echipe* deQueue(Queue*);
Echipe* citire ( FILE *, FILE* , int *);
void afisare ( Echipe *, FILE* );
void admisi( int , int *nr_);
Echipe* stergere ( int , Echipe *);
Queue* meciuri ( Queue *, Node *, Node *, int , FILE *, Queue **, int );
arbore* newNode(Echipe*);
arbore* insert(arbore*, Echipe *);
void inorder(arbore*, FILE*);
Queue * primul_queue ( Echipe *, int);
Queue* afisare_2 ( FILE*, Queue *, int );
arbore* afisare_tree ( FILE* , Queue* );
void free_tree ( arbore* );
void free_Echipe ( Echipe* );



#endif // HEADER_H_INCLUDED
