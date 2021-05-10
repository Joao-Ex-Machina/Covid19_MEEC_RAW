/*-----------------------------------------------------------------------------------------------------+
| covid19_read_module.c  |Read module for covid19_main.c                                               |
|                        |                                                                             |
|                        |                                                                             |
+------------------------------------------------------------------------------------------------------+
| Authors: Joao Barreiros C. Rodrigues (Joao-Ex-Machina) nº99968, Henrique "Delfas" Delfino            |
| Date: 09 May 2021                                                                                    |
+-----------------------------------------------------------------------------------------------------*/
#include "covid19.h"

char** readfile(char* _filename){
   FILE *fp = fopen(_filename,"r");
   char string[150];
   printf("%x", fp);
   fgets(string,150,fp);
   while (fgets(string,150,fp)!=0)
   {
    printf("%s",string);
   }
}

