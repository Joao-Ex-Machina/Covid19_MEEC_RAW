/*-----------------------------------------------------------------------------------------------------+
| sortingmodule.c        |Sorting Module. All Bubble_sort based functions can be found here            |
|                        |                                                                             |
|                        |                                                                             |
+------------------------------------------------------------------------------------------------------+
| Authors: Joao Barreiros C. Rodrigues (Joao-Ex-Machina) nº99968, Henrique "Delfas" Delfino            |
| Date: 19 May 2021                                                                                    |
+-----------------------------------------------------------------------------------------------------*/
country_list *switcher(country_list *left,country_list *right ){
    left->next=right->next;
    right->next=left;
    return right;
}
