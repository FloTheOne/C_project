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

void push(Node**top, Echipe *echipe)
{
    Node* newNode=(Node*)malloc(sizeof(Node));
    newNode->val=echipe;
    newNode->next=*top;
    *top=newNode;
}
int isEmptyStack(Node*top)
{
    return (top==NULL);
}

Echipe* pop(Node**top)
{
    Node *temp;
    Echipe *aux;
    if (isEmptyStack(*top)) return NULL;
    temp=(*top);
    aux=temp->val;
    *top=(*top)->next;
    free(temp);
    return aux;
}

typedef struct Q
{
    Node *front, *rear;
} Queue;

Queue* createQueue()
{
    Queue *q;
    q=(Queue *)malloc(sizeof(Queue));
    if (q==NULL) return NULL;
    q->front=q->rear=NULL;
    return q;
}

void enQueue(Queue*q, Echipe *echipe)
{
    Node* newNode=(Node*)malloc(sizeof(Node));
    newNode->val=echipe;
    newNode->next=NULL;

    if (q->rear==NULL) q->rear=newNode;
    {
        (q->rear)->next=newNode;
        (q->rear)=newNode;
    }
    if (q->front==NULL) q->front=q->rear;
}

int isEmpty(Queue*q)
{
    return (q->front==NULL);
}

Echipe* deQueue(Queue*q)
{
    Node* aux;
    Echipe *d;
    if (isEmpty(q)) return NULL;
    aux =q->front;
    d= aux->val;
    q->front=(q->front)->next;
    free(aux);
    return d;
}




Echipe* citire ( FILE *intrare, FILE* iesire, int *nr_echipe)
{
    char spatiu[1];
    fscanf(intrare,"%d", nr_echipe);

    Echipe *echipe;
    echipe=NULL;
    echipe=(Echipe*)malloc (sizeof(Echipe));
    echipe->next=NULL;

    fscanf (intrare,"%d%c", &(echipe->nr_membrii), spatiu);
    char buffer_nume_echipa[50];
    fscanf(intrare,"%[^\n]",buffer_nume_echipa);
    echipe->nume_echipa=(char*)malloc(sizeof(char)*strlen(buffer_nume_echipa));
    strcpy(echipe->nume_echipa, buffer_nume_echipa);

    for ( int i=0 ; i<(*nr_echipe); i++)
    {
        int suma=0;
        player *head;
        head=NULL;
        head= (player*)malloc (sizeof (player));
        head->next=NULL;

        char buffer_firstName[25];
        char buffer_secondName[25];

        fscanf(intrare,"%s %s %d",buffer_firstName, buffer_secondName, &head->points);
        head->firstName=(char*)malloc ( sizeof(char)* strlen(buffer_firstName));
        head->secondName=(char*)malloc ( sizeof ( char )* strlen(buffer_secondName));
        strcpy(head->firstName,buffer_firstName);
        strcpy(head->secondName, buffer_secondName);

        suma=head->points;
        for ( int j=0 ; j<echipe->nr_membrii-1; j++)
        {
            player *aux;
            aux=(player*)malloc (sizeof (player));
            aux->next=head;
            fscanf(intrare,"%s %s %d",buffer_firstName, buffer_secondName, &aux->points);
            aux->firstName=(char*)malloc ( sizeof(char)* strlen(buffer_firstName));
            aux->secondName=(char*)malloc ( sizeof ( char )* strlen(buffer_secondName));
            strcpy(aux->firstName,buffer_firstName);
            strcpy(aux->secondName, buffer_secondName);
            suma+=aux->points;
            head=aux;
        }
        echipe->puncte_echipa=(float)(suma);
        echipe->puncte_echipa/= (echipe->nr_membrii);
        echipe->val=head;

        if (i==(*nr_echipe)-1)
        {
            break;
        }

        else
        {
            Echipe *aux2;
            aux2=NULL;
            aux2= (Echipe*)malloc (sizeof(Echipe));
            aux2->next=echipe;
            fscanf (intrare,"%d ", &(aux2->nr_membrii));
            fscanf(intrare,"%[^\n]",buffer_nume_echipa);
            aux2->nume_echipa=(char*)malloc(sizeof(char)*strlen(buffer_nume_echipa));
            strcpy(aux2->nume_echipa, buffer_nume_echipa);
            echipe=aux2;
        }
    }
    return echipe;
}

void afisare ( Echipe *echipe, FILE* iesire)
{
    Echipe *copie;
    copie=echipe;

    if (echipe!=NULL)
        while (echipe!=NULL)
        {
            fprintf(iesire,"%s\n",echipe->nume_echipa);
            echipe=echipe->next;
        }

}
void admisi( int nr_echipe, int *nr_ramase)
{
    *nr_ramase=1;
    while (*nr_ramase<nr_echipe)
    {
        *nr_ramase*=2;
    }
    *nr_ramase/=2;

}

Echipe* stergere ( int echipe_sterse, Echipe *echipe)
{
    Echipe *nod_de_sters,*anterior_nod_de_sters;
    for (int i=0; i<echipe_sterse; i++)
    {
        int ok=0;
        float minim=echipe->puncte_echipa;
        Echipe *copie;
        copie=echipe;
        while (copie->next!=NULL)
        {
            if ( copie->next->puncte_echipa<minim)
            {
                anterior_nod_de_sters=copie;
                nod_de_sters=copie->next;
                minim=copie->next->puncte_echipa;
                ok=1;
            }
            copie=copie->next;
        }

        if (ok==1)
        {
            anterior_nod_de_sters->next=anterior_nod_de_sters->next->next;
            free(nod_de_sters);
        }

        else
        {
            echipe=echipe->next;
        }
    }
    return echipe;

}
Queue* meciuri ( Queue *q, Node * top_castigatori, Node * top_invinsi, int nr_ramase, FILE * iesire, Queue **top8, int k)
{
    Echipe *echipa1, *echipa2;
    for ( int i=0 ; i< nr_ramase/2 ; i++ )
    {
        echipa1= deQueue (q);
        echipa2= deQueue (q);
        fprintf(iesire, "%s - %s\n", echipa1->nume_echipa, echipa2->nume_echipa);
        if ( echipa1->puncte_echipa > echipa2->puncte_echipa)
        {
            if ( nr_ramase/2==8)
                echipa1->pozitie=echipa1->puncte_echipa+1;
            echipa1->puncte_echipa++;
            push ( &top_castigatori, echipa1);
            push ( &top_invinsi, echipa2);
        }
        else if ( echipa1->puncte_echipa == echipa2->puncte_echipa)
        {
            if ( nr_ramase/2==8)
                echipa2->pozitie=echipa2->puncte_echipa+1;
            echipa2->puncte_echipa++;
            push ( &top_castigatori, echipa2);
            push ( &top_invinsi, echipa1);
        }
        else
        {
            if ( nr_ramase/2==8)
                echipa2->pozitie=echipa2->puncte_echipa+1;
            echipa2->puncte_echipa++;
            push ( &top_castigatori, echipa2);
            push ( &top_invinsi, echipa1);
        }
    }


    q=NULL;
    q=createQueue();

    fprintf(iesire,"\nWINNERS OF ROUND NO:%d\n",k);
    for ( int i=0 ; i< nr_ramase/2 ; i++ )
    {
        echipa1=pop(&top_castigatori);
        if( nr_ramase/2==8)
        {
            enQueue(*top8,echipa1);
        }
        enQueue (q, echipa1);
        fprintf(iesire,"%s - %0.2f\n", echipa1->nume_echipa, echipa1->puncte_echipa);
        pop(&top_invinsi);
    }
    return q;
}

typedef struct N
{
    float val;
    Echipe *echipe;
    struct N *left,*right;
} arbore;

arbore* newNode(Echipe* echipe)
{
    arbore* node = (arbore*)malloc(sizeof(arbore));
    node->val = echipe->pozitie;
    node->echipe=echipe;
    node->left = node->right = NULL;
    return node;
}

arbore* insert(arbore* node, Echipe *echipe)
{
    if (node == NULL) return newNode(echipe);
    if (echipe->pozitie < node->val)
        node->left = insert(node->left,echipe);
    else if (echipe->pozitie> node->val)
        node->right = insert(node->right,echipe);
    else
    {
        if (strcmp( echipe->nume_echipa, node->echipe->nume_echipa)>0)
          node->right = insert(node->right,echipe);
        else node->left = insert(node->left,echipe);
    }
    return node;
}

void inorder(arbore*root, FILE* iesire)
{
    if (root)
    {
        inorder(root->right,iesire);
        fprintf(iesire,"%s - %0.2f\n",root->echipe->nume_echipa ,root->echipe->pozitie);
        inorder(root->left,iesire);
    }
}
Queue * primul_queue ( Echipe * head, int nr_ramase)
{   Queue *q=createQueue();
    for ( int i=0 ; i<nr_ramase ; i++)
    {
        enQueue( q, head);
        head=head->next;
    }
    return q;

}

Queue* afisare_2 ( FILE*iesire, Queue *q, int nr_ramase)
{    Node *top_castigatori, *top_invisi;
    Queue *top8=createQueue();
     int i=1;
    while ( nr_ramase!=1)
    {
        fprintf(iesire,"\n--- ROUND NO:%d\n", i);
        q=meciuri ( q, top_castigatori, top_invisi,nr_ramase, iesire,&top8, i);
        nr_ramase/=2;
        i++;
    }
return top8;
}

arbore* afisare_tree ( FILE* iesire, Queue* top8)
{   Echipe *nr_4;
    fprintf(iesire,"\nTOP 8 TEAMS:\n");
    int    i=8;
    arbore * root=NULL;
    while ( i!=0)
    {
        nr_4=deQueue(top8);
        i--;
        root =insert(root, nr_4);
    }
    return root;
}
void free_tree (arbore* root)
{
    if (root)
    {
        free_tree(root->left);
        free_tree(root->right);
        free(root);
    }
}

void free_Echipe ( Echipe* echipe)
{   Echipe* aux;
    while ( echipe->next!=NULL)
    {   aux=echipe;
        echipe=echipe->next;
        free(aux);
    }
    free(echipe);
}

int main()
{
    FILE *intrare, *iesire;
    Echipe *head,*copie,*nr_4;
    Node *top_castigatori, *top_invisi;
    int nr_echipe,nr_ramase,echipe_top8=0;
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
    root=afisare_tree( iesire, top8);
    inorder( root,iesire);

    free_tree( root);
    free_Echipe(head);
}
