#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct _nome_do_pais{
char nome[30];
char sigla[4];
char continente[15];
int populacao;
struct _nome_do_pais *next;
}nome_do_pais;
int main()
{
   FILE *fp = fopen("covid19_w_t01.txt","r");
   char string[150];
   printf("%x", fp);
   fgets(string,150,fp);
   while (fgets(string,150,fp)!=0)
   {
    printf("%s",string);
   }
}
