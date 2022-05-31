#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int V; //nr. varfuri
    int E; //nr. muchii
    int ** a; //double – daca vrem sa stocam ponderile, iar acestea nu sunt intregi
} Graph;

Graph * create_matrix ()  // functia aloca spatiu pentru un graf si il initializeaza cu valori
{
    int i, j, orientat;
    Graph *g = (Graph *) malloc (sizeof(Graph));
    if (g==NULL)
    {
        printf ( " no memory for this graph");
        return NULL;
    }
    printf("Cate varfuri are ?");
    scanf (" %d", &(g->V));
    g->a = (int **) malloc(g->V*sizeof(int*));
    for (i=0; i<g->V; i++)
        g->a[i] = (int *) calloc(g->V, sizeof(int));
    if (g->a==NULL)
    {
        printf ( " no memory for this matrix");
        return NULL;
    }
    g->E = 0;
    printf("E orientat? 0 - da, altfel - nu este");
    scanf (" %d", &orientat);
    if (orientat!=0)  //daca nu e orientat => matricea a este simetrica
    {
        for (i=0; i<g->V; i++)
            for (j=0; j<i; j++)
            {
                printf( "Exista arc de la %d la %d?\n", i, j);
                scanf ("%d", &g->a[i][j]);
                g->a[j][i]=g->a[i][j];
                if(g->a[i][j]!=0) g->E+=2;
            }
    }


    else     //este orientat
    {
        for (i=0; i<g->V; i++)
            for (j=0; j<g->V; j++)
            {
                printf( "Exista arc de la %d la %d?\n",i,j);
                scanf ("%d", &g->a[i][j]);
                if(g->a[i][j]!=0) g->E++;
            }
    }
    return g;
}
void printGraph_matrix(Graph *g)
{
    int i, j;
    for (i=0; i<g->V; i++)
    {
        for (j=0; j<g->V; j++)
            printf( " %d ",g->a[i][j]);
        printf("\n");
    }
//am afisat matricea de adiacenta linie cu linie
}

struct ListNode
{
    int vertex_no; //informatia utila = numarul varfului de stocat
    struct ListNode* next;
};

typedef struct ListNode Node;
typedef struct
{
    int V, E;
    Node** b; //vector pentru capetele de liste – lungime V
} Graph_list;


Graph_list * create_list ()  // creare graf folosind liste de adiacenta
{
    int i, j, next,val;
    Graph_list *g = (Graph_list *) malloc (sizeof(Graph_list));
    if (g==NULL)
    {
        printf ( " no memory for this graph");
        return NULL;
    }
    printf("Cate varfuri are ?");
    scanf (" %d", &(g->V));
    g->b=(Node**)malloc(g->V * sizeof(Node*));
    for (i=0; i<g->V; i++)
    {
        printf( "Dati nr varfului stocat ca si capat de lista pe pozitia %d \n",i);
        scanf("%d",&val);
        Node * newnode=(Node*)malloc(sizeof(Node));
        newnode->vertex_no =val;
        newnode->next=NULL;
        g->b[i]=newnode;
    }
    g->E = 0;
    for (i=0; i<g->V; i++)
    {
        printf( "dati varfurile care urmeaza dupa %d \n",g->b[i]->vertex_no );
        next=0;
        Node*p = g->b[i]; // stochez adresa in p pentru ca nu vreau sa o modific
        while (next==0)   //adaug varfuri in lista
        {
            printf( "exista varf urmator? da=0, nu- altceva");
            scanf(" %d", &next);
            if (next ==0)
            {
                printf( "care e varful urmator ?\n");
                scanf ("%d", &val);
                Node * newnode=(Node*)malloc(sizeof(Node));
                newnode->vertex_no =val;
                newnode->next=NULL;
                p->next = newnode; //adaug varful
                p = p->next ; //ma pozitionez la finalul listei
                g->E++; //cresc numarul de muchii
            }
        }
    }
    return g;
}

void printGraph_list(Graph_list *g)
{
    int i, j;
    for (i=0; i<g->V; i++)
    {
        printf("Pentru nodul:");
        while (g->b[i]!=NULL)
        {
            printf( "%d -> ",g->b[i]->vertex_no);
            g->b[i] = g->b[i]->next;
        }
        printf("\n");
    }
}


Graph_list* transformare_Matrice_In_Lista (Graph *g)
{
    int i, j, next,val;
    Graph_list *nou = (Graph_list *) malloc (sizeof(Graph_list));
    if (nou==NULL)
    {
        printf ( " no memory for this graph");
        return NULL;
    }

    nou->V=g->V;
    nou->b=(Node**)malloc(g->V * sizeof(Node*));

    for (i=0; i<g->V; i++)
    {

        Node * newnode=(Node*)malloc(sizeof(Node));
        newnode->vertex_no =i+1;
        newnode->next=NULL;
        nou->b[i]=newnode;
    }

    for (i=0; i<g->V; i++)
    {
        Node*p=nou->b[i];
        for (j=0; j<g->V; j++)
        {
            if(g->a[i][j]==1)
            {
                Node * newnode=(Node*)malloc(sizeof(Node));
                newnode->vertex_no =j+1;
                newnode->next=NULL;
                p->next = newnode; //adaug varful
                p = p->next ; //ma pozitionez la finalul listei
                nou->E++; //cresc numarul de muchii
            }
        }

    }

    return nou;
}

Graph* transformare_Lista_In_Matrice (Graph_list *g)
{
    int i, j, orientat;
    Graph *matrice = (Graph *) malloc (sizeof(Graph));
    if (g==NULL)
    {
        printf ( " no memory for this graph");
        return NULL;
    }
    matrice->V=g->V;
    matrice->a = (int **) malloc(matrice->V*sizeof(int*));
    for (i=0; i<g->V; i++)
        matrice->a[i] = (int *) calloc(matrice->V, sizeof(int));
    if (g->b==NULL)
    {
        printf ( " no memory for this matrix");
        return NULL;
    }
    matrice->E = g->E;

    for (i=0; i<g->V; i++)
    {
        int ok=0;
        while (g->b[i]!=NULL)
        {
            if( g->b[i]->vertex_no-1!= i || ok==1)
                matrice->a[i][g->b[i]->vertex_no-1]++;
            else
                ok=1;
            g->b[i] = g->b[i]->next;
        }
    }
    return matrice;

}

void free_matrice ( Graph* g)
{
    for (int i=0; i<g->V; i++)
        free(g->a[i]);
    free(g->a);
    free(g);
}

void free_lista ( Graph_list *g)
{
    for (int i=0; i<g->V; i++)
    {
        Node * newnode=(Node*)malloc(sizeof(Node));
        while (g->b[i]!=NULL)
        {
            newnode=g->b[i]->next;
            free(g->b[i]);
            g->b[i]=newnode;
        }

    }
    free(g->b);
    free(g);

}

void functie_verificare_matrice ( int x, int y, Graph *g)
{
    if ( g->a[x-1][y-1]!=0) printf("\nExista\n");
    else printf("\nNu exista\n");
}

void funtie_verificare_lista ( int x , int y , Graph_list *g)
{int i=1;
    Graph_list *copie =g;
    if (copie->b[x-1]->next!=NULL )
        copie->b[x-1]=copie->b[x-1]->next;
    else {printf("Nu exista");
            return;}

    while (copie->b[x-1]!=NULL)
    {
        if(copie->b[x-1]->vertex_no==y){
                    printf("\nExista\n");
                    return;
                   }
        copie->b[x-1]=copie->b[x-1]->next;
        i++;
    }
    printf("\nNu Exista\n");

}

void afis_muchi_matrice( int x, Graph*g)
{   for ( int i=0 ;i <g->V ; i++)
    if ( g->a[x-1][i]==1) printf("%d ",i+1);

}

void afis_muchi_lista ( int x, Graph_list *g)
{
     Graph_list *copie =g;
    if (copie->b[x-1]->next!=NULL )
        copie->b[x-1]=copie->b[x-1]->next;
    else {printf("\nNu exista\n");
            return;}
    printf("\n");
    while (copie->b[x-1]!=NULL)
    {
        printf("%d " , copie->b[x-1]->vertex_no);
        copie->b[x-1]=copie->b[x-1]->next;
    }
}

int** matrice_drum ( Graph *g)
{int D[g->V][g->V],k;
    for ( int i=0 ; i<g->V ; i++)
        for ( int j=0 ; j<g->V ;j++)
            D[i][j]=g->a[i][j];


    for (int k = 0; k < g->V-1; k++) //la fiecare pas formez lanturi de lungime 1,2,..
        for (int i = 0; i < g->V-1; i++) //varfurile sunt numerotate de la 0 la V-1
            for (int j = 0; j < g->V-1; j++)
                if(D[i][k] + D[k][j] <D[i][j])
                    {
                    D[i][j]==D[i][k]+D[k][j];
                    printf("\n");
                    }
    for ( int i=0 ; i<g->V ; i++)
        {for ( int j=0 ; j<g->V ;j++)
            printf("%d ",D[i][j]);
        printf("\n");}
    return D;
}
int main()
{
//    Graph *g = create_matrix();
//    printGraph_matrix(g);
//    Graph_list *gg = transformare_Matrice_In_Lista (g);
//    printGraph_list(gg);

    Graph_list *g=create_list();
    printf("\n");
    //afis_muchi_lista(1,g);
   // funtie_verificare_lista( 2,3,g);
    Graph *gg=transformare_Lista_In_Matrice(g);
    printf("\n");
    int **D;
    printGraph_matrix(gg);
    printf("\n");
    functie_verificare_matrice(1,3,gg);
    printf("\n");
    afis_muchi_matrice(2,gg);
    printf("\n");
    D=matrice_drum(gg);
    printf("\n");
    return 0;
}



