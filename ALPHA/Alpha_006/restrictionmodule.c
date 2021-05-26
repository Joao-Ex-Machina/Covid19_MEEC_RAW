/*-----------------------------------------------------------------------------------------------------+
| Restrictionmodules.c   |Free memory module for covid19_main.c                                        |
|                        |All free memory related functions can be found here.                         |
|                        |                                                                             |
+------------------------------------------------------------------------------------------------------+
| Authors: Joao Barreiros C. Rodrigues (Joao-Ex-Machina) nº99968, Henrique "Delfas" Delfino            |
| Date: 09 May 2021                                                                                    |
+-----------------------------------------------------------------------------------------------------*/
#include "covid19.h"
/*Function Name: restricting
  Input:a pointer for the header of the list and a pointer for the command line string
  Output:void function
  Date Created: 19 May 2021
  Last Revised: 23 May 2021
  Definition:restrict the list
*/
country_list *restricting(country_list *heade, char *string)
{
    country_list *aux = NULL, *aux2 = NULL;
    week_list *auxweek = NULL, *auxweek2 = NULL;
    aux = heade;
    aux2 = aux->next;
    long min_valor = 0, max_valor = 0, ano = 0, mes = 0, ano2 = 0, mes2 = 0;
    int variaveis_lidas = -1;
    variaveis_lidas = sscanf(string, "min %ld", &min_valor);
    // verify if the string on the command line was min n,
    if (variaveis_lidas == 1)
    {
        printf ("min %ld ",min_valor);
        min_valor = min_valor*1000;
        //while the population of the header is smaller than n*1000 the country will be deleted
        while(heade->population <= min_valor)
        {
            aux = aux->next;
            aux2 = heade;
           free_node(aux2);
            heade = aux;
        }
        //while cicle to verify if all countries got a population bigger than n*1000
        while (aux->next != NULL)
        {
            //if the population is bigger than n*1000 the cicle will verify the next country, else the country will be deleted
            if (aux->next->population > min_valor)
            {
                aux = aux->next;
            }
            else
            {
                aux2 = aux->next;
                aux->next = aux->next->next;
                free_node(aux2);

            }
        }
        //if the last country got a population <= than n*1000 the country will be deleted
        if (aux->population <= min_valor)
        {
            printf("estou a apagar %s\n", aux->country);
            free_node(aux);
        }


    }

    variaveis_lidas = sscanf(string, "max %ld", &max_valor);
    //in case if the flag is "max n"
    if (variaveis_lidas == 1)
    {
        printf ("max %ld ",max_valor);
        max_valor = max_valor*1000;
           //while the population of the header is bigger than n*1000 the country will be deleted
        while(heade->population >= max_valor)
        {
            aux = aux->next;
            aux2 = heade;
            printf("estou a apagar %s\n", aux2->country);
            free_node(aux2);
            heade = aux;
        }
          //while cicle to verify if all countries got a population smaller than n*1000
        while (aux->next != NULL)
        {
             //if the population is smaller than n*1000 the cicle will verify the next country, else the country will be deleted
            if (aux->next->population < max_valor)
            {
                aux = aux->next;
            }
            else
            {
                aux2 = aux->next;
                aux->next = aux->next->next;
                free_node(aux2);

            }
        }
        //if the last country got a population >= than n*1000 the country will be deleted
        if (aux->population >= max_valor)
        {
            free_node(aux);
        }

    }
    variaveis_lidas = sscanf(string, "date %ld-%ld", &ano, &mes);
      //in case of the respective flag is "date yyyy-ww"
    if (variaveis_lidas == 2)
    {
        country_list *beforecountry = NULL;
        aux = heade;
        auxweek = aux->week_pointer;
        //condition for the head
        while(aux != NULL)
        {
            //verify all weeks of the respective country
            while (aux->week_pointer != NULL)
            {   //if the week is the same of the week we declared on the comand line, that week will be the unique week of the respective country
                if (aux->week_pointer->year == ano && aux->week_pointer->week == mes)
                {
                    printf ("encontrei a semana %s %ld %ld\n", aux->country,aux->week_pointer->year, aux->week_pointer->week);

                    auxweek = aux->week_pointer;
                    auxweek = auxweek->next;
                    aux->week_pointer->next = NULL;

                    //delete all the weeks that we dont want since we found the week we want with the if cause of line 108
                    while(auxweek != NULL)
                    {
                        auxweek2 = auxweek;
                        auxweek = auxweek->next;
                        auxweek2->next = NULL;
                        free(auxweek2);
                    }
                    break;
                }
                auxweek = aux->week_pointer;
                aux->week_pointer = aux->week_pointer->next;
                auxweek->next = NULL;
                free(auxweek);
            }
            //if the head has no week the head will be deleted else the auxiliar pointers for the countries will advance on the list
            if (heade->week_pointer == NULL)
            {
                aux2 = heade;
                heade = heade->next;
                aux = heade;
                beforecountry = heade; //
                free(aux2);
            }
            else
            {
                aux = heade->next;
                beforecountry = heade;
                break;
            }


        }
        //condition for the next country
        while(aux != NULL)
        {
            //verify if exist any week for the country we are pointing with aux
            while (aux->week_pointer != NULL)
            {
                //if the week is the same we declared on the command line we will delete all weeks forward on the list
                if (aux->week_pointer->year == ano && aux->week_pointer->week == mes)
                {

                    auxweek = aux->week_pointer;
                    auxweek = auxweek->next;
                    aux->week_pointer->next = NULL;

                    while(auxweek != NULL)
                    {

                        auxweek2 = auxweek;
                        auxweek = auxweek->next;
                        auxweek2->next = NULL;
                        free(auxweek2);
                    }
                    break;
                }
                auxweek = aux->week_pointer;
                aux->week_pointer = aux->week_pointer->next;
                auxweek->next = NULL;
                free(auxweek);
            }
            //if theres no week for the respective country the country will be deleted
            if (aux->week_pointer == NULL)
            {
                aux2 = aux;
                aux = aux->next;
                beforecountry->next = aux; //
                aux2->next = NULL;
                free(aux2);
            }
            else
            {
                beforecountry = aux;
                aux = aux->next;

            }


        }

      //  printf ("date %ld-%ld ",ano,mes);
    }
    //in case of the respective flag is "dates yyyy-ww yyyy-ww"
    variaveis_lidas = sscanf(string, "dates %ld-%ld %ld-%ld\n", &ano, &mes, &ano2, &mes2);
    if (variaveis_lidas == 4)
    {
        long maxvalue = 0, minvalue = 0;
        aux = heade;
        //all verify what date is recent
        if(ano < ano2)
        {
            maxvalue = ano2*100 + mes2;
            minvalue = ano*100 + mes;
        }
        else if (ano > ano2)
        {
            maxvalue = ano*100 + mes;
            minvalue = ano2*100 + mes2;
        }
        else if(mes < mes2)
        {
            maxvalue = ano2*100 + mes2;
            minvalue = ano*100 + mes;
        }
        else if(mes > mes2)
        {
            maxvalue = ano*100 + mes;
            minvalue = ano2*100 + mes2;
        }
        week_list *beforeweek = NULL; //creation of an auxiliar pointer for weeks
       // while cicle to verify if all the countries respect the restriction
        while( aux != NULL)
        {
            auxweek = aux->week_pointer;
            //while cycle to verify which weeks are between the weeks we pretend
            while (auxweek != NULL)
            {
                long totalvalueweek = 0, totalvalueaux = 0;
                totalvalueaux = aux->week_pointer->week + aux->week_pointer->year*100;
                totalvalueweek = auxweek->week + auxweek->year*100;
                //verify if the week we are reading is between the weeks we pretend
                if (  minvalue > totalvalueaux || maxvalue < totalvalueaux)
                {
                  //  printf ("o totalvalueaux é %ld\n", totalvalueaux);
                    auxweek2 = aux->week_pointer;
                    aux->week_pointer = aux->week_pointer->next;
                    auxweek = aux->week_pointer;
                    auxweek2->next = NULL;
                    free(auxweek2);
                }
                else if(minvalue > totalvalueweek || maxvalue < totalvalueweek)
                {
                    printf ("o totalvalueweek é %ld\n", totalvalueweek );
                    beforeweek->next = auxweek->next;
                    auxweek2 = auxweek;
                    auxweek = auxweek->next;
                    auxweek2->next = NULL;
                    free(auxweek2);
                }
                else
                {
                    beforeweek = auxweek;
                    auxweek = auxweek->next;
                }
            }
            aux = aux->next;
        }
        aux = heade;
        country_list *beforecountry = NULL;
        //while cycle to verify if exist at least 1 week for the respective country, if not the country will be deleted
        while(aux != NULL)
        {
            if (heade->week_pointer == NULL)
            {
                aux2 = heade;
                heade = heade->next;
                aux = heade;
                aux->next = NULL;
                free(aux2);
            }
            else if(aux->week_pointer == NULL)
            {
            aux2 = aux;
            aux = aux->next;
            beforecountry->next = aux;
            aux2->next = NULL;
            free(aux2);
            }
            else
            {
                beforecountry = aux;
                aux = aux->next;
            }
        }

    }

  /* aux = heade;
    do
    {
        printf ("pais %s \n", aux->country);
        // escreve a semana
        auxweek  = aux->week_pointer;
        do
        {
            //printf ("semana %d-%d \n", auxweek->year, auxweek->week);
            printlist(aux, auxweek);
            auxweek  = auxweek->next; //saltamos para a proxima semana
        }
        while (auxweek != NULL);

        aux  = aux->next;
    }
    while (aux != NULL);*/
return heade;
}
