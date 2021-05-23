/*-----------------------------------------------------------------------------------------------------+
| writemodule.c          |Write Module for covid19_main.c                                              |
|                        |All Output files related functions can be found in this module               |
|                        |                                                                             |
+------------------------------------------------------------------------------------------------------+
| Authors: Joao Barreiros C. Rodrigues (Joao-Ex-Machina) nº99968, Henrique "Delfas" Delfino            |
| Date: 19 May 2021                                                                                    |
+-----------------------------------------------------------------------------------------------------*/
#include "covid19.h"
/*Function Name:printnode_tofile
  Input: Two pointers to structs of type country_list and week_list, pointer to File, integer Indicator_To_print
  Output:No return. Strings printed to file
  Date Created: 19 May 2021
  Last Revised: 20 May 2021
  Definition:
*/
void printnode_tofile (country_list *head, week_list *auxweek,FILE *fp,int Indicator_To_print){
    country_list *temporary = head;
    week_list *temporary2 = auxweek;
    if(Indicator_To_print==0)
    fprintf(fp, "%s,%s,%s,%ld,cases,%ld,%ld-%ld,%lf,%ld\n", temporary->country, temporary->country_code, temporary->continent, temporary->population,temporary2->infected_Weekly_count, temporary2->year, temporary2->week, temporary2->infected_rate_14_day, temporary2->infected_cumulative_count);
    if(Indicator_To_print==1)
    fprintf(fp, "%s,%s,%s,%ld,deaths,%ld,%ld-%ld,%lf,%ld\n", temporary->country, temporary->country_code, temporary->continent, temporary->population,temporary2->death_Weekly_count, temporary2->year, temporary2->week, temporary2->death_rate_14_day, temporary2->death_cumulative_count);

}
/*Function Name:
  Input:
  Output:
  Date Created: 19 May 2021
  Last Revised: 20 May 2021
  Definition:
*/
/*void printnode_toDATfile (country_list *head, week_list *auxweek,FILE *fp, int Indicator_To_print){
    country_list *temporary = head;
    week_list *temporary2 = auxweek;
    int aux_char_counter=0;
    char aux_str[150]="";
    if(Indicator_To_print==0)
        sprintf(&aux_str, "%s,%s,%s,%ld,cases,%ld,%ld-%ld,%lf,%ld\n", temporary->country, temporary->country_code, temporary->continent, temporary->population,temporary2->infected_Weekly_count, temporary2->year, temporary2->week, temporary2->infected_rate_14_day, temporary2->infected_cumulative_count);
    if(Indicator_To_print==1)
        sprintf(&aux_str, "%s,%s,%s,%ld,deaths,%ld,%ld-%ld,%lf,%ld\n", temporary->country, temporary->country_code, temporary->continent, temporary->population,temporary2->death_Weekly_count, temporary2->year, temporary2->week, temporary2->death_rate_14_day, temporary2->death_cumulative_count);
    while(aux_str[aux_char_counter]!=00){
        ++aux_char_counter;
    }
    fwrite(&aux_str, aux_char_counter*sizeof(char), 1, fp);
}*/
void printnode_toDATfile_test (country_list *head, week_list *auxweek,FILE *fp){
    country_list *temporary = head;
    week_list *temporary2 = auxweek;
    fwrite(&temporary->country,sizeof(temporary->country), 1, fp);
    fwrite(&temporary->country_code,sizeof(temporary->country_code), 1, fp);
    fwrite(&temporary->continent,sizeof(temporary->continent), 1, fp);
    fwrite(&temporary->population,sizeof(temporary->population), 1, fp);
    fwrite(&temporary2->death_Weekly_count,sizeof(temporary2->death_Weekly_count), 1, fp);
    fwrite(&temporary2->death_cumulative_count,sizeof(temporary2->death_cumulative_count), 1, fp);
    fwrite(&temporary2->infected_Weekly_count,sizeof(temporary2->infected_Weekly_count), 1, fp);
    fwrite(&temporary2->infected_cumulative_count,sizeof(temporary2->infected_cumulative_count), 1, fp);
    fwrite(&temporary2->infected_rate_14_day,sizeof(temporary2->infected_rate_14_day), 1, fp);
    fwrite(&temporary2->death_rate_14_day,sizeof(temporary2->death_rate_14_day), 1, fp);

}
/*Function Name:
  Input:
  Output:
  Date Created: 20 May 2021
  Last Revised: 21 May 2021
  Definition:
*/
void printlist_tofile (country_list *header, char* out_filename, int DotDat_flag){
    country_list *aux = header;
    week_list *auxweek = NULL;
    int Indicator_To_print =0;
    FILE *fp;
    if(DotDat_flag==TRUE){
        fp = fopen(out_filename,"wb+");
    }
    else{
        fp = fopen(out_filename,"w+");
        fprintf(fp, "country,country_code,continent,population,indicator,weekly_count,year_week,rate_14_day,cumulative_count");
    }

    do {
            auxweek  = aux->week_pointer;
        do {
                if(DotDat_flag==TRUE){
                    printnode_toDATfile_test(aux,auxweek,fp);
                }
                else{
                    printnode_tofile(aux, auxweek,fp, Indicator_To_print);
                }
                auxweek  = auxweek->next;
                if (auxweek == NULL){
                    ++Indicator_To_print;
                    if (Indicator_To_print < COMPLETED)
                    auxweek  = aux->week_pointer;
                }
            } while (auxweek != NULL && Indicator_To_print < COMPLETED);
            Indicator_To_print=0;
            aux  = aux->next;
        }while (aux != NULL);
    fclose(fp);
}
