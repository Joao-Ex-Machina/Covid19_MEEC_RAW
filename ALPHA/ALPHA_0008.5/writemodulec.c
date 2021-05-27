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
  Input: Two pointers to structs of type country_list and week_list, pointer to File, integer Indicator_To_print, integer Dflag (selection flag), string selection pointer
  Output:No return. Strings printed to file
  Date Created: 19 May 2021
  Last Revised: 20 May 2021
  Definition:Used to print a node to a .csv or .txt file. Depending on the restriction type the lines related to "cases" or "deaths" can be ommited
*/
void printnode_tofile (country_list *node, week_list *auxweek,FILE *fp,int Indicator_To_print,int Dflag, char selectiondatapointer[20]){
    country_list *temporary = node;
    week_list *temporary2 = auxweek;
    if(Indicator_To_print==0 && (Dflag==FALSE || (Dflag== TRUE && (strcmp(selectiondatapointer,"inf") == 0 ||strcmp(selectiondatapointer,"racioinf") == 0 ))))
    fprintf(fp, "%s,%s,%s,%ld,cases,%ld,%ld-%ld,%lf,%ld\n", temporary->country, temporary->country_code, temporary->continent, temporary->population,temporary2->infected_Weekly_count, temporary2->year, temporary2->week, temporary2->infected_rate_14_day, temporary2->infected_cumulative_count);
    if(Indicator_To_print==1 && (Dflag==FALSE || (Dflag== TRUE && (strcmp(selectiondatapointer,"dea") == 0 ||strcmp(selectiondatapointer,"raciodea") == 0 ))))
    fprintf(fp, "%s,%s,%s,%ld,deaths,%ld,%ld-%ld,%lf,%ld\n", temporary->country, temporary->country_code, temporary->continent, temporary->population,temporary2->death_Weekly_count, temporary2->year, temporary2->week, temporary2->death_rate_14_day, temporary2->death_cumulative_count);

}
/*Function Name:printnode_toDATfile_test
  Input:Two nodes (one of type country_list and one of type week_list). File pointer to the file to write in
  Output:None. Binary Write to file.
  Date Created: 19 May 2021
  Last Revised: 20 May 2021
  Definition:Through fwrite write the variable associated with each node. Used to write into a .dat file

*/
void printnode_toDATfile_test (country_list *node, week_list *auxweek,FILE *fp){
    country_list *temporary = node;
    week_list *temporary2 = auxweek;
    fwrite(temporary->country,sizeof(temporary->country), 1, fp);
    fwrite(temporary->country_code,sizeof(temporary->country_code), 1, fp);
    fwrite(temporary->continent,sizeof(temporary->continent), 1, fp);
    fwrite(&temporary->population,sizeof(temporary->population), 1, fp);
    fwrite(&temporary2->year,sizeof(temporary2->year), 1, fp);
    fwrite(&temporary2->week,sizeof(temporary2->week), 1, fp);
    fwrite(&temporary2->death_Weekly_count,sizeof(temporary2->death_Weekly_count), 1, fp);
    fwrite(&temporary2->death_cumulative_count,sizeof(temporary2->death_cumulative_count), 1, fp);
    fwrite(&temporary2->infected_Weekly_count,sizeof(temporary2->infected_Weekly_count), 1, fp);
    fwrite(&temporary2->infected_cumulative_count,sizeof(temporary2->infected_cumulative_count), 1, fp);
    fwrite(&temporary2->infected_rate_14_day,sizeof(temporary2->infected_rate_14_day), 1, fp);
    fwrite(&temporary2->death_rate_14_day,sizeof(temporary2->death_rate_14_day), 1, fp);

}
/*Function Name:printlist_tofile
  Input:
  Output:
  Date Created: 20 May 2021
  Last Revised: 21 May 2021
  Definition:
*/
void printlist_tofile (country_list *header, char* out_filename, int DotDat_flag, int Dflag, char *selectiondatapointer){
    country_list *aux = header;
    week_list *auxweek = NULL;
    int Indicator_To_print =0;
    FILE *fp = fopen(out_filename,"w");
    if (fp ==NULL)
       help(Write_Error,Cannot_Reach_File);
    if(DotDat_flag!=TRUE){
       fprintf(fp, "country,country_code,continent,population,indicator,weekly_count,year_week,rate_14_day,cumulative_count\n");
    }


    do {
            auxweek  = aux->week_pointer;
        do {
                if(DotDat_flag==TRUE){
                    printnode_toDATfile_test(aux,auxweek,fp);
                    Indicator_To_print = COMPLETED;
                }
                else{
                    printnode_tofile(aux, auxweek,fp, Indicator_To_print, Dflag, selectiondatapointer);
                    auxweek  = auxweek->next;
                    if (auxweek == NULL){
                        ++Indicator_To_print;
                    if (Indicator_To_print < COMPLETED)
                    auxweek  = aux->week_pointer;
                }
                }
                if(DotDat_flag==TRUE)
                auxweek  = auxweek->next;
            } while (auxweek != NULL);
            Indicator_To_print=0;
            aux  = aux->next;
        }while (aux != NULL);
    fclose(fp);
}
