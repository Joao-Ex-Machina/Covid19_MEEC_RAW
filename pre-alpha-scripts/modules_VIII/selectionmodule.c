/*-----------------------------------------------------------------------------------------------------+
| selectionmodule.c      |Data Selection Module for covid19_main.c                                     |
|                        |                                                                             |
|                        |                                                                             |
+------------------------------------------------------------------------------------------------------+
| Authors: Joao Barreiros C. Rodrigues (Joao-Ex-Machina) nº99968, Henrique "Delfas" Delfino            |
| Date: 19 May 2021                                                                                    |
+-----------------------------------------------------------------------------------------------------*/
#include "covid19.h"
void dataselection(country_list *heade){
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
