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
void printlist (country_list *head, week_list *auxweek)
{
    country_list *temporary = head;
    week_list *temporary2 = auxweek;
    printf(" %s,%s,%s,%ld,cases,%ld-%ld,%ld,%lf,%ld\n", temporary->country, temporary->country_code, temporary->continent, temporary->population,temporary2->year, temporary2->week, temporary2->infected_Weekly_count,temporary2->infected_rate_14_day, temporary2->infected_cumulative_count);
    printf(" %s,%s,%s,%ld,deaths,%ld-%ld,%ld,%lf,%ld\n", temporary->country, temporary->country_code, temporary->continent, temporary->population,temporary2->year, temporary2->week, temporary2->death_Weekly_count,temporary2->death_rate_14_day, temporary2->death_cumulative_count);
}

/*Function Name:
  Input:
  Output:
  Date Created: 13 May 2021
  Last Revised: 15 May 2021
  Definition:
*/
/*void free_list(country_list *listhead)
{
    country_list *auxfree;
    auxfree = listhead;
    while ( listhead != NULL)
    {
        auxfree = listhead;
        listhead = listhead->week_pointer;
        free(auxfree->next);
        free(auxfree);
    }
}*/



/*Function Name:
  Input:
  Output:
  Date Created: 13 May 2021
  Last Revised: 15 May 2021
  Definition:
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
/*Function Name:
  Input:
  Output:
  Date Created: 15 May 2021
  Last Revised: 18 May 2021
  Definition:
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
/*Function Name:
  Input:
  Output:
  Date Created: 13 May 2021
  Last Revised: 15 May 2021
  Definition:
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


}

void le_valor (char *linha,char *name,char *country_code,char *continent,long *population,char *indicator,long *weekly_count,long *year,long *week,double *rate_14_day,long *cumulative_count)
{

    char valor[500] = "";
    // printf ("Vamos interpretar a string: %s comp: %d\n", linha, strlen(linha));
    int i= 0;
    int posicao = 1;
    while (i <= strlen(linha))
    {

        if (linha[i] == ',' || i == strlen(linha))
        {
            // printf ("\n p%d:%s \n",posicao,valor);

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
                // printf ("%ld %ld", year, week);
                break;
            case 8:
                sscanf(valor,"%lf", *&rate_14_day);
                //printf("%lf",rate_14_day );
                break;
            case 9:
                sscanf(valor, "%ld", *&cumulative_count);
                // printf("%ld",cumulative_count);
                break;
            }

            posicao++;
            valor[0] = '\0';
        }
        else
        {
            //guardamos caracter a caracter na variavel valor
            strncat (valor, &linha[i],1);
            //printf ("%c", s[i]);
        }

        i++;
    }
    if (posicao != 10)
    {
        printf("non suported line format!!!\n");
    }
}

/*Function Name:
  Input:
  Output:
  Date Created: 13 May 2021
  Last Revised: 15 May 2021
  Definition:
*/
country_list* readfile(char* _filename,country_list* heade )
{
    FILE *fp = fopen(_filename,"r");
    char string[500] = {'\0'};
    char name[30] = {'\0'};
    char country_code[4] = {'\0'};
    char continent[15] = {'\0'};
    char chosen_continent[15] = {'\0'};
    long population = 0, weekly_count = 0, cumulative_count = 0, year = 0, week = 0;
    double rate_14_day;
    country_list *header = NULL, *aux = NULL, *aux2 = NULL;
    week_list *auxweek = NULL, *auxweek2 = NULL; //auxiliar pointer for weeks
    char indicator[15];
    fgets(string,400,fp);
    printf("insert the continent");
    scanf("%s", &chosen_continent); //rudimentar continent reader restriction
    while (strcmp(continent,chosen_continent) != 0 && fgets(string,400,fp) != NULL)
    {
        name[500] = "";
        country_code[4] = "";
        continent[15] = "";
        indicator[15] = "";
        rate_14_day = 0;
        population = 0, weekly_count = 0, cumulative_count = 0, year = 0, week = 0;
        le_valor (string, name, country_code, continent, &population, indicator, &weekly_count, &year, &week, &rate_14_day, &cumulative_count);
        //printf para confirmar se ta tudo bem  printf ("%s %s %s %ld %s %ld %ld %ld %lf %ld\n", name, country_code, continent, population, indicator, weekly_count, year, week, rate_14_day, cumulative_count);


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
        //  printf("estou a criar o primeiro node");
        //printlist(header, auxweek);
        aux = header;
        aux2 = header;
    }


    while (fgets(string,400,fp)!=0)
    {
        name[500] = "";
        country_code[4] = "";
        continent[15] = "";
        indicator[15] = "";
        rate_14_day = 0;
        population = 0, weekly_count = 0, cumulative_count = 0, year = 0, week = 0;
        le_valor (string, name, country_code, continent, &population, indicator, &weekly_count, &year, &week, &rate_14_day, &cumulative_count);
        if (strcmp(continent,chosen_continent) == 0 || strcmp(chosen_continent,"all") == 0)
        {
            aux2 = header;
            while(aux2 != NULL)
            {
                if (strcmp(aux2->country,name) == 0)
                {
                    //  printf("encontrei o pais %s %s\n",aux2->country, name);
                    auxweek2 = aux2->week_pointer;
                    // printf("%ld %ld    %ld %ld\n", year, week, auxweek2->year, auxweek2->week);
                    while(auxweek2->year != year || auxweek2->week != week) //a semana nao é a mesma??
                    {
                        if (auxweek2->next == NULL)
                        {
                            // printf("breakou\n");
                            break;
                        }
                        //printf("tou a acabar %ld %ld\n ", auxweek2->year, auxweek2->week);
                        auxweek2 = auxweek2->next;
                        // printf (" semana - %ld %ld \n", auxweek2->year, auxweek2->week);

                    }
                    //printf("estamos na semana %ld %ld e no pais %s", auxweek2->year, auxweek2->week, aux2->country);
                    if(auxweek2->year == year && auxweek2->week == week)
                    {
                        auxweek = auxweek2;
                        //  printf("estou a completar a semana \na");
                        auxweek = complete_week(indicator, weekly_count, year, week, rate_14_day,cumulative_count, auxweek);
                        break;
                    }
                    if(auxweek2->year != year || auxweek2->week != week)
                    {
                        auxweek = auxweek2;
                        auxweek->next = create_new_week(indicator, weekly_count, year, week, rate_14_day,cumulative_count);
                        auxweek = auxweek->next;
                        // printf ("criar nova semana %ld %ld", auxweek->year, auxweek2->year);
                        //  printf("estou a criar uma semana nova %ld %ld", year, week);
                        break;
                    }

                }
                aux = aux2;
                aux2 = aux2->next;
            }
//printf("ronaldu %s  %s\n", aux2->country, aux->country);

            if (strcmp(aux->country,name) != 0 && aux->next == NULL)
            {

                // printf("estou a criar um novo pais %s %s\n ", aux->country, name);
                aux->next = create_new_country(name, country_code, continent, population);
                aux = aux->next;
                aux2 = aux;
                aux->week_pointer = create_new_week(indicator, weekly_count, year, week, rate_14_day,cumulative_count );
                auxweek = aux->week_pointer;
                aux->week_pointer = auxweek;

            }
            // printf( "aux %s e aux2 %s\n",aux->country, aux2->country);


        }
    }

//free_list(header);
// primeira posicao

    aux = header;
     //função para o teste
     do {
      printf ("pais %s \n", aux->country);
         // escreve a semana
         auxweek  = aux->week_pointer;
         do {
             //printf ("semana %d-%d \n", auxweek->year, auxweek->week);
             printlist(aux, auxweek);
             auxweek  = auxweek->next; //saltamos para a proxima semana
             } while (auxweek != NULL);

      aux  = aux->next;
     } while (aux != NULL);
    return header;
}

//Seleção de dados
void dataselection(country_list *heade)
{
    char data_selection[20] = {'\0'};
    country_list *header = NULL, *aux = NULL, *aux2 = NULL;
    week_list *auxweek = NULL, *auxweek2 = NULL;
    aux = heade;

    printf("diz ai os mortos brou\n");
    scanf("%s",data_selection);
    if (strcmp(data_selection,"inf") == 0)
    {
        while (aux != NULL)
        {
            // printf("sim");
            // printf("pais novo %s\n", aux->country);
            auxweek = aux->week_pointer;
            auxweek2 = auxweek->next;
            while (auxweek->next != NULL)
            {
                // printf("chouriço");
                if (auxweek->infected_Weekly_count > auxweek2->infected_Weekly_count)//see which of the weeks has the highest number of infected
                {
                    //  printf ("o axweek e maior que o auxweek2 %ld %ld\n",auxweek->infected_Weekly_count, auxweek2->infected_Weekly_count);
                    auxweek->next = auxweek2->next;
                    auxweek2->next = NULL;
                    free(auxweek2);
                    auxweek2 = auxweek->next;
                    aux->week_pointer = auxweek;
                }
                else if (auxweek->infected_Weekly_count < auxweek2->infected_Weekly_count)
                {
                    //   printf (" o axweek e menor que o auxweek2 %ld %ld\n",auxweek->infected_Weekly_count, auxweek2->infected_Weekly_count);
                    auxweek->next = NULL;
                    aux->week_pointer = auxweek2;
                    free(auxweek);
                    auxweek = auxweek2;
                    auxweek2 = auxweek2->next;
                }
                else if (auxweek->infected_Weekly_count == auxweek2->infected_Weekly_count)
                {
                    // printf ("eles sao iguais brou\n");
                    auxweek->next = auxweek2->next;
                    aux->week_pointer = auxweek;
                    auxweek2->next = NULL;
                    free(auxweek2);
                    auxweek2 = auxweek->next;
                }
                // printf("atao ma nah somas?\n");

            }
            //  printf("ok entao %ld %ld\n",auxweek->year, auxweek->week);
            // printlist(aux, auxweek);
            // printf("sapateira");
            aux2 = aux;
            aux = aux->next;
        }
        aux = heade;
          do {
      printf ("pais %s \n", aux->country);
         // escreve a semana
         auxweek  = aux->week_pointer;
         do {
             //printf ("semana %d-%d \n", auxweek->year, auxweek->week);
             printlist(aux, auxweek);
             auxweek  = auxweek->next; //saltamos para a proxima semana
             } while (auxweek != NULL);

      aux  = aux->next;
     } while (aux != NULL);

    }
    else if (strcmp(data_selection,"dea") == 0)
    {
        while (aux != NULL)
        {
            auxweek = aux->week_pointer;
            auxweek2 = auxweek->next;
            while (auxweek->next != NULL)
            {
                if (auxweek->death_Weekly_count > auxweek2->death_Weekly_count)//see which of the weeks has the highest number of infected
                {
                    auxweek->next = auxweek2->next;
                    auxweek2->next = NULL;
                    free(auxweek2);
                    auxweek2 = auxweek->next;
                    aux->week_pointer = auxweek;
                }
                else if (auxweek->death_Weekly_count < auxweek2->death_Weekly_count)
                {
                    auxweek->next = NULL;
                    aux->week_pointer = auxweek2;
                    free(auxweek);
                    auxweek = auxweek2;
                    auxweek2 = auxweek2->next;
                }
                else if (auxweek->death_Weekly_count == auxweek2->death_Weekly_count)
                {
                    auxweek->next = auxweek2->next;
                    aux->week_pointer = auxweek;
                    auxweek2->next = NULL;
                    free(auxweek2);
                    auxweek2 = auxweek->next;
                }

            }
            aux2 = aux;
            aux = aux->next;
        }
        aux = heade;
          do {
      printf ("pais %s \n", aux->country);
         // escreve a semana
         auxweek  = aux->week_pointer;
         do {
             //printf ("semana %d-%d \n", auxweek->year, auxweek->week);
             printlist(aux, auxweek);
             auxweek  = auxweek->next; //saltamos para a proxima semana
             } while (auxweek != NULL);

      aux  = aux->next;
     } while (aux != NULL);


    }
    else if (strcmp(data_selection,"racioinf") == 0)
    {
        while (aux != NULL)
        {
            auxweek = aux->week_pointer;
            auxweek2 = auxweek->next;
            while (auxweek->next != NULL)
            {
                if (auxweek->infected_rate_14_day > auxweek2->infected_rate_14_day)//see which of the weeks has the highest number of infected
                {
                    auxweek->next = auxweek2->next;
                    auxweek2->next = NULL;
                    free(auxweek2);
                    auxweek2 = auxweek->next;
                    aux->week_pointer = auxweek;
                }
                else if (auxweek->infected_rate_14_day < auxweek2->infected_rate_14_day)
                {
                    auxweek->next = NULL;
                    aux->week_pointer = auxweek2;
                    free(auxweek);
                    auxweek = auxweek2;
                    auxweek2 = auxweek2->next;
                }
                else if (auxweek->infected_rate_14_day == auxweek2->infected_rate_14_day)
                {
                    auxweek->next = auxweek2->next;
                    aux->week_pointer = auxweek;
                    auxweek2->next = NULL;
                    free(auxweek2);
                    auxweek2 = auxweek->next;
                }

            }
            aux2 = aux;
            aux = aux->next;
        }
        aux = heade;
          do {
      printf ("pais %s \n", aux->country);
         // escreve a semana
         auxweek  = aux->week_pointer;
         do {
             //printf ("semana %d-%d \n", auxweek->year, auxweek->week);
             printlist(aux, auxweek);
             auxweek  = auxweek->next; //saltamos para a proxima semana
             } while (auxweek != NULL);

      aux  = aux->next;
     } while (aux != NULL);
    }else if (strcmp(data_selection,"raciodea") == 0)
    {
        while (aux != NULL)
        {
            auxweek = aux->week_pointer;
            auxweek2 = auxweek->next;
            while (auxweek->next != NULL)
            {
                if (auxweek->death_rate_14_day > auxweek2->death_rate_14_day)//see which of the weeks has the highest number of infected
                {
                    auxweek->next = auxweek2->next;
                    auxweek2->next = NULL;
                    free(auxweek2);
                    auxweek2 = auxweek->next;
                    aux->week_pointer = auxweek;
                }
                else if (auxweek->death_rate_14_day < auxweek2->death_rate_14_day)
                {
                    auxweek->next = NULL;
                    aux->week_pointer = auxweek2;
                    free(auxweek);
                    auxweek = auxweek2;
                    auxweek2 = auxweek2->next;
                }
                else if (auxweek->death_rate_14_day == auxweek2->death_rate_14_day)
                {
                    auxweek->next = auxweek2->next;
                    aux->week_pointer = auxweek;
                    auxweek2->next = NULL;
                    free(auxweek2);
                    auxweek2 = auxweek->next;
                }

            }
            aux2 = aux;
            aux = aux->next;
        }
        aux = heade;
          do {
      printf ("pais %s \n", aux->country);
         // escreve a semana
         auxweek  = aux->week_pointer;
         do {
             //printf ("semana %d-%d \n", auxweek->year, auxweek->week);
             printlist(aux, auxweek);
             auxweek  = auxweek->next; //saltamos para a proxima semana
             } while (auxweek != NULL);

      aux  = aux->next;
     } while (aux != NULL);



    }



}
