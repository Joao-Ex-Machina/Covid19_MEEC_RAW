/*-----------------------------------------------------------------------------------------------------+
| covid19.h              |Headers, structs and other definitions module for covid19_main.c             |
|                        |                                                                             |
|                        |                                                                             |
+------------------------------------------------------------------------------------------------------+
| Authors: Joao Barreiros C. Rodrigues (Joao-Ex-Machina) n?99968, Henrique "Delfas" Delfino            |
| Date: 09 May 2021                                                                                    |
+-----------------------------------------------------------------------------------------------------*/
#ifndef COVID19_H_INCLUDED
#define COVID19_H_INCLUDED
// Included Libraries
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <getopt.h>

// Constant Definitions
#define MAX_WEEKS 52
#define MIN_WEEKS 1
#define MAX_YEAR 2050
#define MIN_YEAR 2019
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
#define File_Not_Found '0'
#define Wrong_Format_On_File 'A'
#define Missing_Data_On_File 'B'
#define Missing_Data_On_File 'B'
#define Write_Error 3
#define Cannot_Reach_File '0'
#define HELP_MESSAGE "Help!"
//GetOpt defines
#define OPTION_LIST "i:o:L:D:S:P:"


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
struct week_list *next;

}week_list;

//Read Module
country_list* readfile(char* _filename,country_list* heade,char *chosen_continent);
void printlist (country_list *head, week_list *auxweek);
country_list *create_new_country(char name[120], char country_code[4], char continent[25],long population);
week_list *create_new_week(char indicator[15], long weekly_count,int year,int week,float rate_14_day,long cumulative_count);
void le_valor (char *linha,char *name,char *country_code,char *continent,long *population,char *indicator,long *weekly_count,long *year,long *week,double *rate_14_day,long *cumulative_count);
country_list* readDATfile(char* _filename,country_list* heade);
//Help and ErrorCodes Module
void help(int Primary_ErrorCode,char Secondary_ErrorCode);
int DotDat_Argument_Overflow(int argc, char *argv[]);
void Missing_Arguments(int argc, char *argv[]);
//Sorting Module
country_list *population_sorter(country_list *header);
country_list *alphabetic_sorter(country_list *header);
country_list *switcher(country_list *left,country_list *right);
country_list *CumulativeValue_sorter(country_list *header, char indicator[4] , long aux_year, long aux_week);
//Selection Module
country_list *dataselection(country_list *heade,char data_selection[20]);
//Restriction Module
country_list *restricting(country_list *heade, char *string);
//Write Module
void printlist_tofile (country_list *header, char* out_filename, int DotDat_flag, int Dflag, char *selectiondatapointer);
void printnode_tofile (country_list *node, week_list *auxweek,FILE *fp,int Indicator_To_print,int Dflag, char selectiondatapointer[20]);
void printnode_toDATfile_test (country_list *node ,week_list *auxweek,FILE *fp);
//Free Module
void free_node(country_list *freepointer);
void free_list(country_list *listhead);
#endif
