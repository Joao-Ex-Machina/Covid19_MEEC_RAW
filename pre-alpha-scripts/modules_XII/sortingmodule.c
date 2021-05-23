/*-----------------------------------------------------------------------------------------------------+
| sortingmodule.c        |Sorting Module. All Bubble_sort based functions can be found here            |
|                        |                                                                             |
|                        |                                                                             |
+------------------------------------------------------------------------------------------------------+
| Authors: Joao Barreiros C. Rodrigues (Joao-Ex-Machina) nº99968, Henrique "Delfas" Delfino            |
| Date: 19 May 2021                                                                                    |
+-----------------------------------------------------------------------------------------------------*/
#include "covid19.h"

/*Function Name: switcher
  Input: Two pointers to a struct of type country_list
  Output: Modified pointer to struct "right" of type country_list
  Date Created: 19 May 2021
  Last Revised: 20 May 2021
  Definition: Basic function to switch the order of two adjacent nodes
*/
country_list *switcher(country_list *left,country_list *right ){
    left->next=right->next;
    right->next=left;
    return right;
}
/*Function Name: alphabetic_sorter
  Input: pointer to a struct of type country_list, in this case the header of the list
  Output: Header to Sorted struct "right"
  Date Created: 19 May 2021
  Last Revised: 20 May 2021
  Definition: Bubble sort based function based on the chars of the string "country" of a country_list type struct.
  Treat this chars as integers in order to get their ASCII code. Sort them according to the ASCII value in order to get a alphabetically
  sorted list
*/
country_list *alphabetic_sorter(country_list *header){
    int letter=0, switcher_aux= TRUE;
    country_list *left, *right, *aux_head, aux_node;
    aux_head=&aux_node;
    aux_head->next =header;
    if ((header!=NULL) && (header->next !=NULL)){
        while(switcher_aux){
            switcher_aux=FALSE;
            left=aux_head;
            right=aux_head->next;
            while (right->next!= NULL){
                while((right->/*(int)*/country[letter]) == (right->next->/*(int)*/country[letter])){
                    ++letter;
                }
                if (right->/*(int)*/country[letter] > right->next->/*(int)*/country[letter]){
                    left->next= switcher(right, right->next);
                    switcher_aux=TRUE;
                }
                left =right;
                if(right->next !=NULL)
                    right=right->next;
                letter=0;
            }

        }
    }
    right=aux_head->next;
    return right;
}
/*Function Name: population_sorter
  Input: pointer to a struct of type country_list, in this case the header of the list
  Output: Header to Sorted struct "right"
  Date Created: 19 May 2021
  Last Revised: 20 May 2021
  Definition: Bubble sort based function based on the value of the long integer "population" of a country_list type struct.
  Sort them according value in order to get a decrescent sorted list
*/
country_list *population_sorter(country_list *header){
    int switcher_aux= TRUE;
    country_list *left, *right, *aux_head, aux_node;
    aux_head=&aux_node;
    aux_head->next = alphabetic_sorter(header); //start with alphabetic sorting
    if ((header!=NULL) && (header->next !=NULL)){
        while(switcher_aux){
            switcher_aux=FALSE;
            left=aux_head;
            right=aux_head->next;
            while (right->next!= NULL){
                if (right->population < right->next->population){
                    left->next= switcher(right, right->next);
                    switcher_aux=TRUE;
                }
                left =right;
                if(right->next !=NULL)
                    right=right->next;
            }

        }
    }
    right=aux_head->next;
    return right;
}

/*Function Name: population_sorter
  Input: pointer to a struct of type country_list, in this case the header of the list
  Output: Header to Sorted struct "right"
  Date Created: 19 May 2021
  Last Revised: 20 May 2021
  Definition: Bubble sort based function based on the value of the long integer "population" of a country_list type struct.
  Sort them according value in order to get a decrescent sorted list
*/
country_list *CumulativeValue_sorter(country_list *header, char indicator[4] , long aux_year, long aux_week){
    int switcher_aux= TRUE;
    country_list *left, *right,*next_to_right, *aux_head, aux_node;
    week_list *nxt_right_week, *right_week;
    aux_head=&aux_node;
    aux_head->next = alphabetic_sorter(header); //start with alphabetic sorting
    if ((header!=NULL) && (header->next !=NULL)){
        while(switcher_aux){
            switcher_aux=FALSE;
            left=aux_head;
            right=aux_head->next;
            next_to_right=right->next;
            nxt_right_week=next_to_right->week_pointer;
            right_week=right->week_pointer;
            while(nxt_right_week->week != aux_week || nxt_right_week->year !=aux_year){
                nxt_right_week=nxt_right_week->next;
            }
            while(right_week->week != aux_week || right_week->year !=aux_year){
                right_week=right_week->next;
            }
            while (right->next!= NULL){
                if (!(strcmp(indicator, "inf"))){
                    if (right_week->infected_cumulative_count < nxt_right_week->infected_cumulative_count){
                        left->next= switcher(right, right->next);
                        switcher_aux=TRUE;
                    }
                    left =right;
                    if(right->next !=NULL)
                        right=nxt_right_week;
                }
                if (!(strcmp(indicator, "dea"))){
                    if (right_week->death_cumulative_count < nxt_right_week->death_cumulative_count){
                        left->next= switcher(right, right->next);
                        switcher_aux=TRUE;
                    }
                    left =right;
                    if(right->next !=NULL)
                        right=nxt_right_week;
                }
            }

        }
    }
    right=aux_head->next;
    return right;
}
