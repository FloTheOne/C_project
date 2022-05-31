#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* function(char *str )
{
    char *ajutor;
    int numar=0, count=0;
    ajutor= (char*)malloc ( sizeof(char)* 3*strlen(str));
    for ( int i=0; str[i]; i++)
        if ( str[i]>=65 && str[i]<=90)
        {
            numar= str[i]-64;
            if ( numar >9 )
            {
                ajutor[count++]=numar/10+48;
                ajutor[count++]=numar%10+48;
            }
            else ajutor[count++]=numar+48;
            ajutor[count++]=' ';
        }
        else if ( str[i]>=97 && str[i]<=122){

            numar=str[i]-96;
            if ( numar >9 )
            {
                ajutor[count++]=numar/10+48;
                ajutor[count++]=numar%10+48;
            }
            else ajutor[count++]=numar+48;
            ajutor[count++]=' ';
        }
    ajutor[count-1]='\0';
    return ajutor;
}

int main()
{
    char str[]="The sunset sets at twelve o'clock";
    char *rezultat;
    rezultat= function(str);
    printf("%s",rezultat);

}
