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
