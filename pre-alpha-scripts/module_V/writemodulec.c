/*-----------------------------------------------------------------------------------------------------+
| writemodule.c          |Write Module for covid19_main.c                                              |
|                        |All Output files related functions can be found in this module               |
|                        |                                                                             |
+------------------------------------------------------------------------------------------------------+
| Authors: Joao Barreiros C. Rodrigues (Joao-Ex-Machina) nº99968, Henrique "Delfas" Delfino            |
| Date: 19 May 2021                                                                                    |
+-----------------------------------------------------------------------------------------------------*/
#include "covid19.h"

void printnode_tofile (country_list *head, week_list *auxweek,FILE *fp)
{
    country_list *temporary = head;
    week_list *temporary2 = auxweek;
    fprintf(fp, " %s,%s,%s,%ld,cases,%ld-%ld,%ld,%lf,%ld\n", temporary->country, temporary->country_code, temporary->continent, temporary->population,temporary2->year, temporary2->week, temporary2->infected_Weekly_count,temporary2->infected_rate_14_day, temporary2->infected_cumulative_count);
    fprintf(fp, " %s,%s,%s,%ld,deaths,%ld-%ld,%ld,%lf,%ld\n", temporary->country, temporary->country_code, temporary->continent, temporary->population,temporary2->year, temporary2->week, temporary2->death_Weekly_count,temporary2->death_rate_14_day, temporary2->death_cumulative_count);
}
void printlist_tofile (country_list *header, char* out_filename){
    country_list *aux = header;
    week_list *auxweek = NULL;
    FILE *fp = fopen(out_filename,"w+");
        do {
            auxweek  = aux->week_pointer;
            do {
                printnode_tofile(aux, auxweek,fp);
                auxweek  = auxweek->next;
            } while (auxweek != NULL);
            aux  = aux->next;
        }while (aux != NULL);
    fclose(fp);
}
