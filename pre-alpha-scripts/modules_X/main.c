/*-----------------------------------------------------------------------------------------------------+
| covid19_main.c         |Main module for The Programming Curricular Unit final Project- "Covid19"     |
|                        |Directives can be found here:                                                |
|                        |                                                                             |
+------------------------------------------------------------------------------------------------------+
| Authors: Joao Barreiros C. Rodrigues (Joao-Ex-Machina) nº99968, Henrique "Delfas" Delfino            |
| Date: 09 May 2021                                                                                    |
+-----------------------------------------------------------------------------------------------------*/
#include "covid19.h"

int main(){
 country_list *header, *aux;
 header = (country_list *)malloc(1*(sizeof(country_list)));
    header->next = NULL;
    header = readfile("covid19_w_t01.txt", &header);
    aux = header;
    /*dataselection(aux);*/
    //aux = CumulativeValue_sorter(aux, "inf" , 2020, 13);
    printlist_tofile (aux, "teste32.csv", FALSE);
}
