/*-----------------------------------------------------------------------------------------------------+
| covid19_read_module.c  |Read module for covid19_main.c                                               |
|                        |                                                                             |
|                        |                                                                             |
+------------------------------------------------------------------------------------------------------+
| Authors: Joao Barreiros C. Rodrigues (Joao-Ex-Machina) nº99968, Henrique "Delfas" Delfino            |
| Date: 09 May 2021                                                                                    |
+-----------------------------------------------------------------------------------------------------*/
#include "covid19.h"
//created 13/05
void printlist (country_list *head){
country_list *temporary = head;
printf(" %s %s %s %d \n", temporary->name, temporary->acronymn, temporary->continent, temporary->population);

}

//created 13/05
country_list *create_new_country(char name[120], char acronymn[4], char continent[25],int population){
    country_list *new_country = (country_list*)malloc(sizeof(country_list));
    strcpy(new_country->name, name);
    strcpy(new_country->acronymn, acronymn);
    strcpy(new_country->continent, continent);
    new_country->population = population;
    new_country->next = NULL;
    new_country->week_pointer = NULL;

    return new_country;

}

char** readfile(char* _filename){
   FILE *fp = fopen(_filename,"r");
    char string[500] = {'\0'};
    char name[500] = {'\0'};
    char acronymn[500] = {'\0'};
    char continent[500] = {'\0'};
    char chosen_continent[500] = {'\0'};
    int population = 0, weekly_count = 0, cumulative_count = 0, year = 0, week = 0;
    float rate_14_day;
    country_list *header = NULL, *aux = NULL, *aux2 = NULL;
    char indicator[15];
   fgets(string,400,fp);
   scanf("%s", &chosen_continent);
    while (strcmp(continent,chosen_continent) != 0){
    fgets(string,400,fp);
    sscanf(string, "%[a-zA-Z ],%[a-zA-Z ],%[a-zA-Z ],%d,%[a-zA-Z ],%d,%d-%d,%f,%d ", name,acronymn,continent, &population, indicator, &weekly_count, &year, &week, &rate_14_day,&cumulative_count );
    if (strcmp(chosen_continent,"all") == 0){
        break;
    }
    }
    header = create_new_country(name, acronymn, continent, population);
    printlist(header);
    aux = header;


   while (fgets(string,400,fp)!=0)
   {
    sscanf(string, "%[a-zA-Z ],%[a-zA-Z ],%[a-zA-Z ],%d,%[a-zA-Z ],%d,%d-%d,%f,%d ", name,acronymn,continent, &population, indicator, &weekly_count, &year, &week, &rate_14_day,&cumulative_count );
    if (strcmp(continent,chosen_continent) == 0 || strcmp(chosen_continent,"all") == 0){
    aux->next = create_new_country(name, acronymn, continent, population);
    aux = aux->next;
    printlist(aux);}
   }

}

