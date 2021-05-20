/*-----------------------------------------------------------------------------------------------------+
| sortingmodule.c        |Sorting Module. All Bubble_sort based functions can be found here            |
|                        |                                                                             |
|                        |                                                                             |
+------------------------------------------------------------------------------------------------------+
| Authors: Joao Barreiros C. Rodrigues (Joao-Ex-Machina) nº99968, Henrique "Delfas" Delfino            |
| Date: 19 May 2021                                                                                    |
+-----------------------------------------------------------------------------------------------------*/

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
  sorted struct
*/
country_list alphabetic_sorter(country_list *header){
    int letter=0, switcher= TRUE;
    country_list *left, *right, *aux_head, aux_node;
    aux_head=&aux_node;
    aux_head->next =header;
    if ((header!=NULL) && (header->next !=NULL)){
        while(switcher){
            switcher=FALSE;
            left=head;
            right=head->next;
            while (right->next!= NULL){
                while(right->(int)country[letter] == right->next->(int)country[letter]){
                    ++letter;
                }
                if (right->(int)country[letter] > right->next->(int)country[letter]){
                    left->next= switcher(right, right->next);
                    switcher=TRUE;
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
country_list population_sorter(country_list *header){
    int switcher= TRUE;
    country_list *left, *right, *aux_head, aux_node;
    aux_head=&aux_node;
    aux_head->next = alphabetic_sorter(header); //start with alphabetic sorting
    if ((header!=NULL) && (header->next !=NULL)){
        while(switcher){
            switcher=FALSE;
            left=head;
            right=head->next;
            while (right->next!= NULL){
                if (right->population > right->next->population){
                    left->next= switcher(right, right->next);
                    switcher=TRUE;
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
