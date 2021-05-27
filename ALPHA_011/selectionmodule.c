/*-----------------------------------------------------------------------------------------------------+
| selectionmodule.c      |Data Selection Module for covid19_main.c                                     |
|                        |                                                                             |
|                        |                                                                             |
+------------------------------------------------------------------------------------------------------+
| Authors: Joao Barreiros C. Rodrigues (Joao-Ex-Machina) nº99968, Henrique "Delfas" Delfino            |
| Date: 19 May 2021                                                                                    |
+-----------------------------------------------------------------------------------------------------*/
#include "covid19.h"
/*Function Name: dataselection
  Input:pointer for the header of the list, 20 char string
  Output:void function
  Date Created: 19 May 2021
  Last Revised: 23 May 2021
  Definition:F
*/
country_list *dataselection(country_list *heade,char data_selection[20]){

    country_list  *aux = NULL;
    week_list *auxweek = NULL, *auxweek2 = NULL;
    aux = heade;
       //if the data selection is inf
    if (strcmp(data_selection,"inf") == 0)
    {
		  //while cicle to check all countries
        while (aux != NULL)
        {
            
            auxweek = aux->week_pointer;
            auxweek2 = auxweek->next;
              //checks for each country if the infected weekly count is bigger than the next
            while (auxweek->next != NULL)
            {
                if (auxweek->infected_Weekly_count > auxweek2->infected_Weekly_count)//see which of the weeks has the highest number of infected
                {
                    
                    auxweek->next = auxweek2->next;
                    auxweek2->next = NULL;
                    free(auxweek2);
                    auxweek2 = auxweek->next;
                    aux->week_pointer = auxweek;
                }
                else if (auxweek->infected_Weekly_count < auxweek2->infected_Weekly_count)
                {
           
                    auxweek->next = NULL;
                    aux->week_pointer = auxweek2;
                    free(auxweek);
                    auxweek = auxweek2;
                    auxweek2 = auxweek2->next;
                }
                else if (auxweek->infected_Weekly_count == auxweek2->infected_Weekly_count)
                {
                      
                    auxweek->next = auxweek2->next;
                    aux->week_pointer = auxweek;
                    auxweek2->next = NULL;
                    free(auxweek2);
                    auxweek2 = auxweek->next;
                }
             

            }
              //put all data related with deaths in 0 because we only want data related with cases
            auxweek->death_rate_14_day = 0;
            auxweek->death_Weekly_count = 0;
            auxweek->death_cumulative_count = 0;
            aux = aux->next;
        }


    }
    //if the data selection is dea
    else if (strcmp(data_selection,"dea") == 0)
    {
		//while cicle to check all countries
        while (aux != NULL)
        {
            auxweek = aux->week_pointer;
            auxweek2 = auxweek->next;
            //checks for each country if the death weekly count is bigger than the next
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
             //put all data related with causes in 0 because we only want data related with deaths
            auxweek->infected_rate_14_day = 0;
            auxweek->infected_Weekly_count = 0;
            auxweek->infected_cumulative_count = 0;
            aux = aux->next;
        }



    }
     //if the data selection is racioinf
    else if (strcmp(data_selection,"racioinf") == 0)
    {
		//checks all countries
        while (aux != NULL)
        {
            auxweek = aux->week_pointer;
            auxweek2 = auxweek->next;
             //checks for each country if the infected week racio is bigger than the next
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
             //put all data related with deaths in 0 because we only want data related with cases
            auxweek->death_rate_14_day = 0;
            auxweek->death_Weekly_count = 0;
            auxweek->death_cumulative_count = 0;
            aux = aux->next;
        }



    }
        //if the data selection is raciodea
    else if (strcmp(data_selection,"raciodea") == 0)
    {    
		 //while cicle to check all countries
        while (aux != NULL)
        {
            auxweek = aux->week_pointer;
            auxweek2 = auxweek->next;
              //checks for each country if the racio death is bigger than the next
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
              //put all data related with causes in 0 because we only want data related with deaths
            auxweek->infected_rate_14_day = 0;
            auxweek->infected_Weekly_count = 0;
            auxweek->infected_cumulative_count = 0;
            aux = aux->next;
        }
    }


return heade;

}
