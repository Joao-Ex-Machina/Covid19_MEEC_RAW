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
//GetOpt defines
#include <ctype.h>
#include <getopt.h>
#define LISTA_OPCOES "-:i:o:L:S:D:P:"

// Constant Definitions
#define MAX_WEEKS 52
//boolean defines
#define TRUE 1
#define FALSE 0

#define COMPLETED 2
//Help and ErrorCodes defines
#define User_Called_Help 0
#define Argument_Error 1
#define Unknown_Argument 'A'
#define Missing_Argument 'B'
#define Argument_Overflow 'C'
#define Read_Error 2
#define Wrong_Format_On_File 'A'
#define Missing_Data_On_File 'B'
#define HELP_MESSAGE "Help!"


typedef struct country_list{
char country[30];
char country_code[4];
char continent[15];
long population;
struct week_list *week_pointer;
struct country_list *next;
}country_list;

typedef struct week_list{
long death_Weekly_count, death_cumulative_count, infected_Weekly_count, infected_cumulative_count, year, week;
double death_rate_14_day, infected_rate_14_day;
char indicator[30];
struct week_list *next;

}week_list;
country_list* readfile(char* _filename, country_list* header, char *chosen_continent);
void dataselection(country_list *heade, char *selection);
void restricting(country_list *heade, char *string);


#endif
