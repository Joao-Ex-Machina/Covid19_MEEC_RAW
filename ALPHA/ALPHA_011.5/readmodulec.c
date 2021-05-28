/*-----------------------------------------------------------------------------------------------------+
| covid19_read_module.c  |Read module for covid19_main.c                                               |
|                        |                                                                             |
|                        |                                                                             |
+------------------------------------------------------------------------------------------------------+
| Authors: Joao Barreiros C. Rodrigues (Joao-Ex-Machina) nº99968, Henrique "Delfas" Delfino            |
| Date: 09 May 2021                                                                                    |
+-----------------------------------------------------------------------------------------------------*/
#include "covid19.h"

/*Function Name:create_new_country(
  Input: 3 chars and one long with the fix information of the country
  Output:a poiter to the new country
  Date Created: 13 May 2021
  Last Revised: 15 May 2021
  Definition:create a node for a country
*/
country_list *create_new_country(char name[120], char country_code[4], char continent[25],long population)
{
    country_list *new_country = (country_list*)malloc(sizeof(country_list));
    strcpy(new_country->country, name);
    strcpy(new_country->country_code, country_code);
    strcpy(new_country->continent, continent);
    new_country->population = population;
    new_country->next = NULL;
    new_country->week_pointer = NULL;

    return new_country;

}
/*Function Name:complete_week
  Input: two chars, two longs and two ints with information related to the week and a pointer 
  Output: a pointer to the week completed
  Date Created: 15 May 2021
  Last Revised: 18 May 2021
  Definition:complete the information of the week
*/
week_list *complete_week(char indicator[15], long weekly_count,int year,int week,float rate_14_day,long cumulative_count, week_list *auxweek)
{
    week_list *pog_week = auxweek;
    if (strcmp(indicator,"cases") == 0)
    {
        pog_week->infected_Weekly_count = weekly_count;
        pog_week->year = year;
        pog_week->week = week;
        pog_week->infected_rate_14_day = rate_14_day;
        pog_week->infected_cumulative_count = cumulative_count;
        return pog_week;
    }

    if (strcmp(indicator,"deaths") == 0)
    {
        pog_week->death_Weekly_count = weekly_count;
        pog_week->year = year;
        pog_week->week = week;
        pog_week->death_rate_14_day = rate_14_day;
        pog_week->death_cumulative_count = cumulative_count;
        return pog_week;
    }
    return pog_week;
}
/*Function Name:create_new_week
  Input: two chars, two longs and two ints with information related to the week
  Output: a pointer to the new week
  Date Created: 13 May 2021
  Last Revised: 15 May 2021
  Definition:create a node for a new week
*/
week_list *create_new_week(char indicator[15], long weekly_count,int year,int week,float rate_14_day,long cumulative_count)
{
    week_list *new_week = (week_list*)malloc(sizeof(week_list));
    if (strcmp(indicator,"cases") == 0)
    {
        new_week->infected_Weekly_count = weekly_count;
        new_week->year = year;
        new_week->week = week;
        new_week->infected_rate_14_day = rate_14_day;
        new_week->infected_cumulative_count = cumulative_count;
        new_week->death_rate_14_day = 0;
        new_week->death_cumulative_count = 0;
        new_week->death_Weekly_count = 0;
        new_week->next = NULL;
        return new_week;
    }
    if (strcmp(indicator,"deaths") == 0)
    {
        new_week->death_Weekly_count = weekly_count;
        new_week->year = year;
        new_week->week = week;
        new_week->death_rate_14_day = rate_14_day;
        new_week->death_cumulative_count = cumulative_count;
        new_week->infected_Weekly_count = 0;
        new_week->infected_rate_14_day = 0;
        new_week->infected_cumulative_count = 0;
        new_week->next = NULL;
        return new_week;
    }

    return new_week;
}
/*Function Name:le_valor
  Input:5 pointers to the first char of  5 strings, 5 pointers to 5 longs, 2 pointers to 2 double precision integers
  Output:No Return.
  Date Created: 13 May 2021
  Last Revised: 15 May 2021
  Definition:Auxiliary function to readfile function. Works as a more specific strtok, reading the extracted data directly to the respective variables
*/
void le_valor (char *linha,char *name,char *country_code,char *continent,long *population,char *indicator,long *weekly_count,long *year,long *week,double *rate_14_day,long *cumulative_count){

    char valor[500] = "";
    int i= 0;
    int posicao = 1;
    while (i <= strlen(linha))
    {

        if (linha[i] == ',' || i == strlen(linha)) //string separation and value saving based on separator comma
        {


            switch (posicao)
            {
            case 1:
                strcpy (name,valor);
                break;
            case 2:
                strcpy (country_code, valor);
                break;
            case 3:
                strcpy (continent, valor);
                break;
            case 4:
                sscanf(valor,"%ld", *&population);
                break;
            case 5:
                strcpy(indicator,valor);
                break;
            case 6:
                sscanf(valor,"%ld", *&weekly_count);
                break;
            case 7:
                sscanf(valor,"%ld-%ld", *&year, *&week);
                break;
            case 8:
                sscanf(valor,"%lf", *&rate_14_day);
                break;
            case 9:
                sscanf(valor, "%ld", *&cumulative_count);
                break;
            }
            posicao++;
            valor[0] = '\0';
        }
        else
        {
            strncat (valor, &linha[i],1);
        }

        i++;
    }
    if (posicao != 10) //fail-safe conditions. Call help
    {
        if (posicao < 10)
            help(2, Missing_Data_On_File);
        if (posicao > 10)
            help(2, Overflow_Data_On_File);
    }
}

/*Function Name:readfile
  Input: 2 pointers to the first char of a string(filename and Chosen_continent), pointer to a node of type country_list (header of the list)
  Output:Pointer to a node of type country_list (header)
  Date Created: 13 May 2021
  Last Revised: 15 May 2021
  Definition:Core reading function for.csv and other extensions files.
*/
country_list* readfile(char* _filename,country_list* heade,char *chosen_continent){
    FILE *fp = fopen(_filename,"r");
    if (fp ==NULL)
       help(Read_Error,File_Not_Found);
    char string[500] = {'\0'};
    char name[30] = {'\0'};
    char country_code[4] = {'\0'};
    char continent[15] = {'\0'};
    long population = 0, weekly_count = 0, cumulative_count = 0, year = 0, week = 0;
    double rate_14_day=0;
    country_list *header = NULL, *aux = NULL, *aux2 = NULL;
    week_list *auxweek = NULL, *auxweek2 = NULL;
    char indicator[15]= {'\0'};
    fgets(string,400,fp);
    while (strcmp(continent,chosen_continent) != 0 && fgets(string,400,fp) != NULL)
    {
        name[0] = '\0'; //reset
        country_code[0] = '\0';
        continent[0] = '\0';
        indicator[0] = '\0';
        rate_14_day = 0;
        population = 0, weekly_count = 0, cumulative_count = 0, year = 0, week = 0;
        le_valor (string, name, country_code, continent, &population, indicator, &weekly_count, &year, &week, &rate_14_day, &cumulative_count);
        string_validity(name, country_code, continent);
        //(debug prinf) printf ("%s %s %s %ld %s %ld %ld %ld %lf %ld\n", name, country_code, continent, population, indicator, weekly_count, year, week, rate_14_day, cumulative_count);


        if (strcmp(chosen_continent,"all") == 0)
        {
            break;
        }
    }
    //if condition to prevent the program from reading the last element of the list in case the chosen continent does not correspond to "all" or to another continent
    if (strcmp(continent,chosen_continent) == 0 || strcmp(chosen_continent,"all") == 0)
    {
        header = create_new_country(name, country_code, continent, population);
        header->week_pointer = create_new_week(indicator, weekly_count, year, week, rate_14_day,cumulative_count);
        auxweek = header->week_pointer;
        aux = header;
        aux2 = header;
    }


    while (fgets(string,400,fp)!=0) //functions as an while until EOF
    {
        name[0] = '\0'; //reset strings
        country_code[0] = '\0';
        continent[0] = '\0';
        indicator[0] = '\0';
        rate_14_day = 0;
        population = 0, weekly_count = 0, cumulative_count = 0, year = 0, week = 0;
        le_valor (string, name, country_code, continent, &population, indicator, &weekly_count, &year, &week, &rate_14_day, &cumulative_count);
        string_validity(name, country_code, continent);
        if (strcmp(continent,chosen_continent) == 0 || strcmp(chosen_continent,"all") == 0)
        {
            aux2 = header;
            while(aux2 != NULL)
            {
                if (strcmp(aux2->country,name) == 0)
                {
                    auxweek2 = aux2->week_pointer;
                    while(auxweek2->year != year || auxweek2->week != week) //verify if the week is different
                    {
                        if (auxweek2->next == NULL)
                        {
                            break;
                        }
                        auxweek2 = auxweek2->next;


                    }
                    if(auxweek2->year == year && auxweek2->week == week)
                    {
                        auxweek = auxweek2;
                        auxweek = complete_week(indicator, weekly_count, year, week, rate_14_day,cumulative_count, auxweek);
                        break;
                    }
                    if(auxweek2->year != year || auxweek2->week != week)
                    {
                        auxweek = auxweek2;
                        auxweek->next = create_new_week(indicator, weekly_count, year, week, rate_14_day,cumulative_count);
                        auxweek = auxweek->next;
                        break;
                    }

                }
                aux = aux2;
                aux2 = aux2->next;
            }

            if (strcmp(aux->country,name) != 0 && aux->next == NULL)
            {

                aux->next = create_new_country(name, country_code, continent, population);
                aux = aux->next;
                aux2 = aux;
                aux->week_pointer = create_new_week(indicator, weekly_count, year, week, rate_14_day,cumulative_count );
                auxweek = aux->week_pointer;
                aux->week_pointer = auxweek;

            }



        }
    }


    fclose(fp);
    return header;
}
/*Function Name:create_new_weekDAT()
  Input:long death_Weekly_count,long death_cumulative_count,long infected_Weekly_count,long infected_cumulative_count,long year,long week,double death_rate_14_day,double infected_rate_14_day (data in a week_list struct type)
  Output: pointer to a struct of type week_list
  Date Created: 22 May 2021
  Last Revised: 23 May 2021
  Definition: Used during the reading of a .dat File in order to create a new week node with the desired data. It is a simpler version of the create_new_week function
 */
week_list *create_new_weekDAT(long death_Weekly_count,long death_cumulative_count,long infected_Weekly_count,long infected_cumulative_count,long year,long week,double death_rate_14_day,double infected_rate_14_day)
{
    week_list *new_week = (week_list*)malloc(sizeof(week_list));
        new_week->infected_Weekly_count = infected_Weekly_count;
        new_week->year = year;
        new_week->week = week;
        new_week->infected_rate_14_day = infected_rate_14_day;
        new_week->infected_cumulative_count = infected_cumulative_count;
        new_week->death_rate_14_day = death_rate_14_day;
        new_week->death_cumulative_count = death_cumulative_count;
        new_week->death_Weekly_count = death_Weekly_count;
        new_week->next = NULL;
        return new_week;
}
/*Function Name:readDAT()
  Input: pointer to the first char of a string (filename) and a pointer to a country_list node (the header of the list).
  Output: pointer to a struct of type week_list
  Date Created: 22 May 2021
  Last Revised: 23 May 2021
  Definition:  since the way the data is stored its known and can be directly loaded into a nodes
*/
country_list* readDATfile(char* _filename,country_list* heade){
    country_list *header = heade, *aux = NULL, *temporary = NULL;
    week_list *temporary2 = NULL,*aux_week = NULL;
    FILE *fp = fopen(_filename,"rb");
    if (fp ==NULL)
       help(Read_Error,File_Not_Found);
    char country[30];
    char country_code[4];
    char continent[15];
    long population=0;
    long death_Weekly_count=0,death_cumulative_count=0,infected_Weekly_count=0,infected_cumulative_count=0, year=0,week=0;
    double death_rate_14_day=0,infected_rate_14_day=0;
    fread(country,sizeof(temporary->country), 1, fp); //lines 371 to 380 obligatory read and load of the first node
    fread(country_code,sizeof(temporary->country_code), 1, fp);
    fread(continent,sizeof(temporary->continent), 1, fp);
    fread(&population,sizeof(temporary->population), 1, fp);
    fread(&year,sizeof(temporary2->year), 1, fp);
    fread(&week,sizeof(temporary2->week), 1, fp);
    fread(&death_Weekly_count,sizeof(temporary2->death_Weekly_count), 1, fp);
    fread(&death_cumulative_count,sizeof(temporary2->death_cumulative_count), 1, fp);
    fread(&infected_Weekly_count,sizeof(temporary2->infected_Weekly_count), 1, fp);
    fread(&infected_cumulative_count,sizeof(temporary2->infected_cumulative_count), 1, fp);
    fread(&infected_rate_14_day,sizeof(temporary2->infected_rate_14_day), 1, fp);
    fread(&death_rate_14_day,sizeof(temporary2->death_rate_14_day), 1, fp);
    header=create_new_country(country,country_code,continent, population);
    aux=header;
    aux->week_pointer=create_new_weekDAT(death_Weekly_count, death_cumulative_count, infected_Weekly_count, infected_cumulative_count, year, week, death_rate_14_day,infected_rate_14_day);
    aux_week=aux->week_pointer;
    while(feof(fp) == 0){
        fread(country,sizeof(temporary->country), 1, fp);
        fread(country_code,sizeof(temporary->country_code), 1, fp);
        fread(continent,sizeof(temporary->continent), 1, fp);
        fread(&population,sizeof(temporary->population), 1, fp);
        fread(&year,sizeof(temporary2->year), 1, fp);
        fread(&week,sizeof(temporary2->week), 1, fp);
        fread(&death_Weekly_count,sizeof(temporary2->death_Weekly_count), 1, fp);
        fread(&death_cumulative_count,sizeof(temporary2->death_cumulative_count), 1, fp);
        fread(&infected_Weekly_count,sizeof(temporary2->infected_Weekly_count), 1, fp);
        fread(&infected_cumulative_count,sizeof(temporary2->infected_cumulative_count), 1, fp);
        fread(&infected_rate_14_day,sizeof(temporary2->infected_rate_14_day), 1, fp);
        fread(&death_rate_14_day,sizeof(temporary2->death_rate_14_day), 1, fp);
        if (strcmp(country, aux->country)==0){ //check if the node is related to the country previous loaded node. In affirmative case create only a new week_list and discard the fixed value, loading tha variable data into the week_list node
            aux_week->next=create_new_weekDAT(death_Weekly_count, death_cumulative_count, infected_Weekly_count, infected_cumulative_count, year, week, death_rate_14_day,infected_rate_14_day);
            aux_week=aux_week->next;
        }
        else{ //if not create a new country_list type node load fixed data AND a new week_list node from the week_pointer of the created country node
            aux->next=create_new_country(country,country_code,continent, population);
            aux=aux->next;
            aux->week_pointer=create_new_weekDAT(death_Weekly_count, death_cumulative_count, infected_Weekly_count, infected_cumulative_count, year, week, death_rate_14_day,infected_rate_14_day);
            aux_week=aux->week_pointer;
        }
    }
    fclose(fp);
    return header;
}




