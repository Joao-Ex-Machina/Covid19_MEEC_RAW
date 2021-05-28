/*-----------------------------------------------------------------------------------------------------+
| Freemodules.c          |Free memory module for covid19_main.c                                        |
|                        |All free memory related functions can be found here.                         |
|                        |                                                                             |
+------------------------------------------------------------------------------------------------------+
| Authors: Joao Barreiros C. Rodrigues nº99968, Henrique Ramos Delfino nº99957                         |
|          MEEC-IST                                                                                    |
| Date: 09 May 2021                                                                                    |
+-----------------------------------------------------------------------------------------------------*/
#include "covid19.h"

/*Function Name: free_node
  Input: pointer to a struct of type country_list, in this case the struct that should be free'd
  Output: None
  Date Created: 19 May 2021
  Last Revised: 26 May 2021
  Definition: Start with freeing all nodes of the sublist of the main node.Free sublist header. Free main node
*/
void free_node(country_list *freepointer){


    week_list *weekpointer = NULL, *weekpointer2 = NULL;

    weekpointer = freepointer->week_pointer;
    weekpointer2 = weekpointer->next;

    while(weekpointer2 != NULL) //Free loop in order to free all sublist nodes.
    {
        weekpointer->next = weekpointer2->next;
        weekpointer2->next = NULL;
        free(weekpointer2);
        weekpointer2 = weekpointer->next;
    }
    free(weekpointer); //free "header" of the sublist, the week_pointer of the country_list node
    free(freepointer); //free the main node
}
/*Function Name: free_list
  Input: pointer to a struct of type country_list, in this case the header of the main list
  Output: None
  Date Created: 19 May 2021
  Last Revised: 26 May 2021
  Definition: Function based on free_node function. Make the pointer next to the listhead the new listhead, free the previous listhead. Repeat until listhead is different from NULL
*/
void free_list(country_list *listhead)
{
    country_list *auxfree;
    auxfree = listhead;
    while ( listhead != NULL)
    {
        auxfree = listhead;
        listhead = listhead->next;
        free_node(auxfree);
    }
}

