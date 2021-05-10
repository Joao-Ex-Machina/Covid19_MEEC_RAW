/*-----------------------------------------------------------------------------------------------------+
| covid19.h              |Headers, structs and other definitions module for covid19_main.c             |
|                        |                                                                             |
|                        |                                                                             |
+------------------------------------------------------------------------------------------------------+
| Authors: Joao Barreiros C. Rodrigues (Joao-Ex-Machina) nº99968, Henrique "Delfas" Delfino            |
| Date: 09 May 2021                                                                                    |
+-----------------------------------------------------------------------------------------------------*/
#ifndef COVID19_H_INCLUDED
#define COVID19_H_INCLUDED
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct country_list{
char name[30];
char acronymn[4];
char continent[15];
long population;
struct week_list *week_pointer;
struct country_list *next;
}country_list;

typedef struct week_list{
long InfectedWeekly, DeathWeekly, InfectedTotal, DeathTotal; 
double InfectedRatio, DeathRatio; 
struct week_list *next;
}week_list;

char** readfile(char* _filename);
#endif