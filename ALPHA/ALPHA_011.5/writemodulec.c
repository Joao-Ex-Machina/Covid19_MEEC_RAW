/*-----------------------------------------------------------------------------------------------------+
| writemodule.c          |Write Module for covid19_main.c                                              |
|                        |All Output files related functions can be found in this module               |
|                        |                                                                             |
+------------------------------------------------------------------------------------------------------+
| Authors: Joao Barreiros C. Rodrigues nº99968, Henrique Ramos Delfino nº99957                         |
|          MEEC-IST                                                                                    |
| Date: 17 May 2021                                                                                    |
+-----------------------------------------------------------------------------------------------------*/
#include "covid19.h"
/*Function Name:printnode_tofile
  Input: Two pointers to nodes of type country_list and week_list, pointer to File, integer Indicator_To_print(print cases or deaths), integer Dflag (selection flag), string selection pointer
  Output:No return. Strings printed to file
  Date Created: 17 May 2021
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
  Input:Two pointer to  nodes (one of type country_list and one of type week_list). File pointer to the file to write in
  Output:No Return. Binary Write to file.
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
  Input: Pointer to the header of the list (node), 2 pointers to the first char of a string (file name and type of selection), 2 integers DotDAt_flag (.dat flag) and DFlag (selection flag)
  Output:No return. File written
  Date Created: 17 May 2021
  Last Revised: 21 May 2021
  Definition:Main function to print, depending on the DotDat_flag calls one or another function to print a node to file
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
    if(aux==NULL){ //fail-safe
        fclose(fp);
        return;
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
                    if (auxweek == NULL){ //reaches the end of the week_list
                        ++Indicator_To_print;
                    if (Indicator_To_print < COMPLETED)
                    auxweek  = aux->week_pointer; //reset starting pointer if not completed( write both deaths and cases)
                }
                }
                if(DotDat_flag==TRUE)
                auxweek  = auxweek->next;
            } while (auxweek != NULL); //run for all week nodes
            Indicator_To_print=0; //reset indicator to print
            aux  = aux->next;
        }while (aux != NULL);
    fclose(fp);
}

/* **Function Name:
  Input: printnode_toTerminal
  Output: No Return
  Date Created: 11 May 2021
  Last Revised: 13 May 2021
  Definition:This function was used in debugging stages of the program. The two other printnode functions are direct descendents from this function

void printnode_toTerminal (country_list *head, week_list *auxweek)
{
    country_list *temporary = head;
    week_list *temporary2 = auxweek;
    printf(" %s %s %s %ld cases %ld %ld %ld %lf %ld ", temporary->country, temporary->country_code, temporary->continent, temporary->population,temporary2->year, temporary2->week, temporary2->infected_Weekly_count,temporary2->infected_rate_14_day, temporary2->infected_cumulative_count);
    printf("deaths %ld %lf %ld \n", temporary2->death_Weekly_count,temporary2->death_rate_14_day, temporary2->death_cumulative_count);
}
** */
