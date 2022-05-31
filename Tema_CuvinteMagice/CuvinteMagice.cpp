#include <iostream>
#include <math.h>
#include <string.h>
#include <cstring>

using namespace std;

void functie_a(int M[50][50],int &i,int &j,char cuv[],int poz)
{
    char maxim = max(max(max(cuv[1], cuv[2]), cuv[3]), cuv[4]);
    if (cuv[1]==maxim)
        j++;
    else if(cuv[2]==maxim)
        i--;
    else if(cuv[3]==maxim)
        j--;
    else
        i++;
    M[i][j] = poz;
}

void functie_b(int M[50][50], int &i, int &j, char cuv[], int poz)
{
    int value = 0;
    for (int l = 1; l < strlen(cuv); l++)
        value = value * 10 + int(cuv[l]) - 48;
    bool ok = true;
    int check_prim = value % 100;
    for (int d = 2; d*d<=check_prim && ok; d++)
        if(check_prim%d==0){
            ok = 0;
            break;
        }
    int value1 = value;
    int palindrom = 0;
    while (value1!=0)
    {
        palindrom = palindrom * 10 + (value1 % 10);
        value1 /= 10;
    }
    if(palindrom == value && ok)
        j--;
    else if(palindrom == value && !ok)
        j++;
    else if(palindrom!=value && ok)
        i--;
    else
        i++;
    M[i][j] = poz;
}

void functie_c(int M[50][50], int &i, int &j, char cuv[], int poz)
{
    int n = int(cuv[1]) - 48; //nrc
    int k = int(cuv[2]) - 48;
    int S = 0;

    for (int d = 1; d <= k;d++)
        S += int(cuv[(d * k) % n + 2]) - 48;
    if(S%4==0)
        j--;
    else if(S%4==1)
        i--;
    else if(S%4==2)
        j++;
    else
        i++;
    M[i][j] = poz;
}

int main()
{
    int N, M; //dimensiune linie+coloana
    cin >> N >> M;
    cin.get();
    int Matrix[50][50] = {0}; // declare matrix
    Matrix[0][0] = 1;
    char cuvinte_magice[1200];
    int pozitie = 2;
    int i = 0;
    int j = 0;
    cin.getline(cuvinte_magice, 1200);
    char *pp;
    pp = strtok(cuvinte_magice, " ");
    while (pp)
    {
        if (pp[0] == 'a')
            functie_a(Matrix, i, j, pp, pozitie);
        if(pp[0]=='b')
            functie_b(Matrix, i, j, pp, pozitie);
        if(pp[0]=='c')
             functie_c(Matrix, i, j, pp, pozitie);
        pozitie++;
        pp=strtok(NULL, " ");
    }
    for (int i = 0; i < N; i++)
    {
        for(int j = 0; j < M; j++)
            cout << Matrix[i][j] << ' ';
        cout << '\n';
    }
    return 0;
}
