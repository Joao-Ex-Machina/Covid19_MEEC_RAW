/*-----------------------------------------------------------------------------------------------------+
| covid19_read_module.c  |Read module for covid19_main.c                                               |
|                        |                                                                             |
|                        |                                                                             |
+------------------------------------------------------------------------------------------------------+
| Authors: Joao Barreiros C. Rodrigues (Joao-Ex-Machina) nº99968, Henrique "Delfas" Delfino            |
| Date: 09 May 2021                                                                                    |
+-----------------------------------------------------------------------------------------------------*/
#include "covid19.h"

/*Function Name:
  Input:
  Output:
  Date Created: 13 May 2021
  Last Revised: 15 May 2021
  Definition:
*/
void printlist (country_list *head, week_list *auxweek, int indicator[15]){
country_list *temporary = head;
week_list *temporary2 = auxweek;
if (strcmp(indicator,"cases")){
printf(" %s %s %s %d %s %d %d %d %f %d\n", temporary->country, temporary->country_code, temporary->continent, temporary->population,indicator, temporary2->Infected_Weekly_count, temporary2->year, temporary2->week, temporary2->Infected_rate_14_day, temporary2->Infected_cumulative_count);
}else if (strcmp(indicator,"deaths")){
printf(" %s %s %s %d %s %d %d %d %f %d\n", temporary->country, temporary->country_code, temporary->continent, temporary->population,indicator, temporary2->Death_Weekly_count, temporary2->year, temporary2->week, temporary2->Death_rate_14_day, temporary2-> Death_cumulative_count);

}
}

/*Function Name:
  Input:
  Output:
  Date Created: 13 May 2021
  Last Revised: 15 May 2021
  Definition:
*/
country_list *create_new_country(char name[120], char country_code[4], char continent[25],int population){
    country_list *new_country = (country_list*)malloc(sizeof(country_list));
    strcpy(new_country->country, name);
    strcpy(new_country->country_code, country_code);
    strcpy(new_country->continent, continent);
    new_country->population = population;
    new_country->next = NULL;
    new_country->week_pointer = NULL;

    return new_country;

}
/*Function Name:
  Input:
  Output:
  Date Created: 13 May 2021
  Last Revised: 15 May 2021
  Definition:
*/
week_list *create_new_week(int indicator[15], int weekly_count,int year,int week,float rate_14_day,int cumulative_count){
    week_list *new_week = (week_list*)malloc(sizeof(week_list));
    if (strcmp(indicator,"cases") == 0) // rever se não é só strcmp(indicator,"cases") !!!
        {
            new_week->Infected_Weekly_count = weekly_count;
            new_week->year = year;
            new_week->week = week;
            new_week->Infected_rate_14_day = rate_14_day;
            new_week->Infected_cumulative_count = cumulative_count;
            new_week->next = NULL;
        }else if (strcmp(indicator,"deaths"))
            {
                new_week->Death_Weekly_count = weekly_count;
                new_week->year = year;
                new_week->week = week;
                new_week->Death_rate_14_day =  rate_14_day;
                new_week->Death_cumulative_count =  cumulative_count;
                new_week->next = NULL;
            }
        return new_week;
}

/*Function Name:
  Input:
  Output:
  Date Created: 13 May 2021
  Last Revised: 15 May 2021
  Definition:
*/
char** readfile(char* _filename){
   FILE *fp = fopen(_filename,"r");
    char string[500] = {'\0'};
    char name[30] = {'\0'};
    char country_code[4] = {'\0'};
    char continent[15] = {'\0'};
    char chosen_continent[15] = {'\0'};
    long population = 0, weekly_count = 0, cumulative_count = 0, year = 0, week = 0;
    double rate_14_day;
    country_list *header = NULL, *aux = NULL, *aux2 = NULL;
    week_list *auxweek = NULL;
    char indicator[15];
   fgets(string,400,fp);
   scanf("%s", &chosen_continent); //rudimentar continent reader restriction
   // while (strcmp(continent,chosen_continent) != 0){
    fgets(string,400,fp);
    sscanf(string, "%[a-zA-Z ],%[a-zA-Z ],%[a-zA-Z ],%d,%[a-zA-Z ],%d,%d-%d,%lf,%ld ", name,country_code,continent, &population, indicator, &weekly_count, &year, &week, &rate_14_day, &cumulative_count );
    printf("%s %s %s %d %s %d %d %d %lf %ld \n", name, country_code,continent, population, indicator, weekly_count, year, week, rate_14_day, cumulative_count);
    fgets(string,400,fp);
    sscanf(string, "%[a-zA-Z ],%[a-zA-Z ],%[a-zA-Z ],%d,%[a-zA-Z ],%d,%d-%d,%lf,%ld ", name,country_code,continent, &population, indicator, &weekly_count, &year, &week, &rate_14_day, &cumulative_count );
    printf("%s %s %s %d %s %d %d %d %f %ld \n", name, country_code,continent, population, indicator, weekly_count, year, week, rate_14_day, cumulative_count);
   /* if (strcmp(chosen_continent,"all") == 0){
        break;
    }
    }
    header = create_new_country(name, country_code, continent, population);
    header->week_pointer = create_new_week(indicator, weekly_count, year, week, rate_14_day,cumulative_count );
    auxweek = header->week_pointer;
    printlist(header, auxweek, indicator);
    aux = header;


   while (fgets(string,400,fp)!=0)
   {
    sscanf(string, "%[a-zA-Z ],%[a-zA-Z ],%[a-zA-Z ],%d,%[a-zA-Z ],%d,%d-%d,%f,%d ", name,country_code,continent, &population, indicator, &weekly_count, &year, &week, &rate_14_day,&cumulative_count );
    if (strcmp(continent,chosen_continent) == 0 || strcmp(chosen_continent,"all") == 0){
            if (strcmp(aux->country,name) == 0){
                auxweek->next = create_new_week(indicator, weekly_count, year, week, rate_14_day,cumulative_count );
                auxweek = auxweek->next;
            }else{
            aux->next = create_new_country(name, country_code, continent, population);
            aux = aux->next;
            auxweek->next = create_new_week(indicator, weekly_count, year, week, rate_14_day,cumulative_count );
            auxweek = auxweek->next;
            }
    printlist(header, auxweek, indicator);
   }
   }*/

}
