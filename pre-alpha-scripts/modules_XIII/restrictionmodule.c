/*-----------------------------------------------------------------------------------------------------+
| Restrictionmodules.c   |Free memory module for covid19_main.c                                        |
|                        |All free memory related functions can be found here.                         |
|                        |                                                                             |
+------------------------------------------------------------------------------------------------------+
| Authors: Joao Barreiros C. Rodrigues (Joao-Ex-Machina) nº99968, Henrique "Delfas" Delfino            |
| Date: 09 May 2021                                                                                    |
+-----------------------------------------------------------------------------------------------------*/
#include "covid19.h"
void restricting(country_list *heade, char *string)
{
    country_list *aux = NULL, *aux2 = NULL;
    week_list *auxweek = NULL, *auxweek2 = NULL;
    aux = heade;
    aux2 = aux->next;
    long min_valor = 0, max_valor = 0, ano = 0, mes = 0, ano2 = 0, mes2 = 0;
    int variaveis_lidas = -1;
    //in case of the flag be "min n"
    variaveis_lidas = sscanf(string, "min %ld", &min_valor);
    // printf("variaveis lidas para min %d\n",variaveis_lidas);
    if (variaveis_lidas == 1)
    {
        printf ("min %ld ",min_valor);
        while(heade->population <= min_valor)
        {
            aux = aux->next;
            aux2 = heade;
            printf("estou a apagar %s\n", aux2->country);
            freesublist(aux2);
            heade = aux;
        }
        while (aux->next != NULL)
        {
            if (aux->next->population > min_valor)
            {
                aux = aux->next;
            }
            else
            {
                aux2 = aux->next;
                aux->next = aux->next->next;
                printf("estou a apagar %s\n", aux2->country);
                freesublist(aux2);

            }
        }
        if (aux->population <= min_valor)
        {
            printf("estou a apagar %s\n", aux->country);
            freesublist(aux);
        }


    }
    //in case if the flag is "max n"
    variaveis_lidas = sscanf(string, "max %ld", &max_valor);
   // printf("variaveis lidas para max %d\n",variaveis_lidas);
    if (variaveis_lidas == 1)
    {
        printf ("max %ld ",max_valor);
        while(heade->population >= max_valor)
        {
            aux = aux->next;
            aux2 = heade;
            printf("estou a apagar %s\n", aux2->country);
            freesublist(aux2);
            heade = aux;
        }
        while (aux->next != NULL)
        {
            if (aux->next->population < max_valor)
            {
                aux = aux->next;
            }
            else
            {
                aux2 = aux->next;
                aux->next = aux->next->next;
                printf("estou a apagar %s\n", aux2->country);
                freesublist(aux2);

            }
        }
        if (aux->population >= max_valor)
        {
            printf("estou a apagar %s\n", aux->country);
            freesublist(aux);
        }

    }
    //in case of the respective flag is "date yyyy-ww"
    variaveis_lidas = sscanf(string, "date %ld-%ld", &ano, &mes);
   // printf("variaveis lidas %d\n",variaveis_lidas );
    if (variaveis_lidas == 2)
    {
        country_list *beforecountry = NULL;
        aux = heade;
        auxweek = aux->week_pointer;
        //condition for the head
        while(aux != NULL)
        {
            printf ("eu antes era %s e agora sou %s\n", beforecountry->country, aux->country);

            while (aux->week_pointer != NULL)
            {
                printf ("estou a ler %s %ld %ld\n", aux->country,aux->week_pointer->year, aux->week_pointer->week  );
                if (aux->week_pointer->year == ano && aux->week_pointer->week == mes)
                {
                    printf ("encontrei a semana %s %ld %ld\n", aux->country,aux->week_pointer->year, aux->week_pointer->week);

                    auxweek = aux->week_pointer;
                    auxweek = auxweek->next;
                    aux->week_pointer->next = NULL;
                    // printf("quero apagar a semana %ld",auxweek->week);

                    while(auxweek != NULL)
                    {

                        printf ("estou a apagar %s %ld %ld\n",aux->country,auxweek->year, auxweek->week);
                        auxweek2 = auxweek;
                        auxweek = auxweek->next;
                        auxweek2->next = NULL;
                        free(auxweek2);
                    }
                    break;
                }
                auxweek = aux->week_pointer;
                printf ("estou a apagar do pais %s a semana %ld %ld\n", aux->country, auxweek->year, auxweek->week);
                aux->week_pointer = aux->week_pointer->next;
                auxweek->next = NULL;
                free(auxweek);
            }
            if (heade->week_pointer == NULL)
            {
                printf ("estou a apagar o pais %s\n", heade->country);
                aux2 = heade;
                heade = heade->next;
                aux = heade;
                beforecountry = heade; //
                free(aux2);
                printf("o heade agora é %s\n", heade->country);
            }
            else
            {
                aux = heade->next;
                beforecountry = heade;
                break;
            }


        }
        //condition for the next
        while(aux != NULL)
        {
            while (aux->week_pointer != NULL)
            {
                printf ("estou a ler %s %ld %ld\n", aux->country,aux->week_pointer->year, aux->week_pointer->week  );
                if (aux->week_pointer->year == ano && aux->week_pointer->week == mes)
                {
                    printf ("encontrei a semana %s %ld %ld\n", aux->country,aux->week_pointer->year, aux->week_pointer->week);

                    auxweek = aux->week_pointer;
                    auxweek = auxweek->next;
                    aux->week_pointer->next = NULL;
                    //     printf("quero apagar a semana %ld",auxweek->week);

                    while(auxweek != NULL)
                    {

                        printf ("estou a apagar %s %ld %ld\n",aux->country,auxweek->year, auxweek->week);
                        auxweek2 = auxweek;
                        auxweek = auxweek->next;
                        auxweek2->next = NULL;
                        free(auxweek2);
                    }
                    break;
                }
                auxweek = aux->week_pointer;
                printf ("estou a apagar do pais %s a semana %ld %ld\n", aux->country, auxweek->year, auxweek->week);
                aux->week_pointer = aux->week_pointer->next;
                auxweek->next = NULL;
                free(auxweek);
            }
            if (aux->week_pointer == NULL)
            {
                printf ("estou a apagar o pais %s\n", aux->country);
                aux2 = aux;
                aux = aux->next;
                beforecountry->next = aux; //
                aux2->next = NULL;
                free(aux2);
                printf("o aux agora é %s\n", aux->country);
            }
            else
            {
                beforecountry = aux;
                aux = aux->next;

            }


        }

        printf ("date %ld-%ld ",ano,mes);
    }
    //in case of the respective flag is "dates yyyy-ww yyyy-ww"
    variaveis_lidas = sscanf(string, "dates %ld-%ld %ld-%ld\n", &ano, &mes, &ano2, &mes2);
      printf("variaveis lidas para as dates %d\n",variaveis_lidas );
    if (variaveis_lidas == 4)
    {
        long maxvalue = 0, minvalue = 0;
        aux = heade;
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
        week_list *beforeweek = NULL; //creation of an auxiliar pointer
        printf (" o minvalue e o mauxvalue são respetivamente %ld %ld", minvalue, maxvalue);
        while( aux != NULL)
        {
            auxweek = aux->week_pointer;
            while (auxweek != NULL)
            {
                long totalvalueweek = 0, totalvalueaux = 0;
                totalvalueaux = aux->week_pointer->week + aux->week_pointer->year*100;
                totalvalueweek = auxweek->week + auxweek->year*100;
                printf("o valor total do head é %ld e o da semana normal é %ld no pais %s\n",totalvalueaux, totalvalueweek, aux->country );
                if (  minvalue > totalvalueaux || maxvalue < totalvalueaux)
                {
                    printf ("o totalvalueaux é %ld\n", totalvalueaux);
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
                   // printf ("estou a nextar, antes era asemana %ld %ld agora sou %ld %ld\n",beforeweek->year, beforeweek->week, auxweek->year, auxweek->week);
                }
            }
            aux = aux->next;
        }
        aux = heade;
        country_list *beforecountry = NULL;
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








    aux = heade;
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
    while (aux != NULL);

}
