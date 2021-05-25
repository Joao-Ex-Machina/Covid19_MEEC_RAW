/*-----------------------------------------------------------------------------------------------------+
| Freemodules.c          |Free memory module for covid19_main.c                                        |
|                        |All free memory related functions can be found here.                         |
|                        |                                                                             |
+------------------------------------------------------------------------------------------------------+
| Authors: Joao Barreiros C. Rodrigues (Joao-Ex-Machina) nº99968, Henrique "Delfas" Delfino            |
| Date: 09 May 2021                                                                                    |
+-----------------------------------------------------------------------------------------------------*/
#include "covid19.h"
void freesublist(country_list *freepointer){


    week_list *weekpointer = NULL, *weekpointer2 = NULL;

    weekpointer = freepointer->week_pointer;
    weekpointer2 = weekpointer->next;

    while(weekpointer2 != NULL)
    {
        weekpointer->next = weekpointer2->next;
        weekpointer2->next = NULL;
        free(weekpointer2);
        weekpointer2 = weekpointer->next;
    }
    free(weekpointer);
    free(freepointer);
}
void free_list(country_list *listhead)
{
    country_list *auxfree;
    auxfree = listhead;
    while ( listhead != NULL)
    {
        auxfree = listhead;
        listhead = listhead->week_pointer; //???
        free(auxfree->next);
        free(auxfree);
    }
}

