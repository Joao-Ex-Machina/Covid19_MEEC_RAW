/*-----------------------------------------------------------------------------------------------------+
|main.c                  |Main module for The Programming Curricular Unit final Project- "Covid19"     |
|                        |Directives can be found here:                                                |
|                        |                                                                             |
+------------------------------------------------------------------------------------------------------+
| Authors: Joao Barreiros C. Rodrigues nº99968, Henrique Ramos Delfino nº99957                         |
|          MEEC-IST                                                                                    |
| Date: 09 May 2021                                                                                    |
+-----------------------------------------------------------------------------------------------------*/
#include "covid19.h"

int main(int argc, char *argv[]){
 country_list *header=NULL, *aux=NULL;
    int oflag = FALSE, iflag = FALSE, Lflag = FALSE, Sflag = FALSE, Dflag = FALSE, Pflag = FALSE, InputDat_flag=FALSE, OutputDat_flag=FALSE, opt, length;
    char  *In_filename = NULL, *continent = NULL, controlsflag[4] = {'\0'}, *Out_filename = NULL, *selectiondatapointer = NULL, rescrictpointer[50] = {'\0'},Sorting_aux[50] = {'\0'} ;
    long year, week;

    while((opt = getopt(argc, argv, OPTION_LIST)) != -1)
    {
        switch (opt)
        {
         case 'h':
          help(User_Called_Help, '0');
          break;
         case 'i': // opção com argumentos obrigatórios
            if (optarg == NULL)
                help(Argument_Error, Missing_Argument);
            iflag = TRUE;
            length=strlen(optarg);
            //sscanf(optarg, " %s", &aux_reader);
            if(optarg[length-4]=='.'&& optarg[length-3]=='d'&& optarg[length-2]=='a'&& optarg[length-1]=='t')
                InputDat_flag=TRUE;
            In_filename = optarg;
        break;
         case 'o':
            if (optarg == NULL)
                help(Argument_Error, Missing_Argument);
            oflag = TRUE;
            length=strlen(optarg);
            //sscanf(optarg, " %s", &aux_reader2);
            if(optarg[length-4]=='.'&& optarg[length-3]=='d' && optarg[length-2]=='a' && optarg[length-1]=='t')
                OutputDat_flag=TRUE;
            Out_filename  = optarg;
        break;
         case 'L':
            if (optarg == NULL)
                help(Argument_Error, Missing_Argument);
            Lflag = TRUE;
            continent = optarg;
        break;
         case 'S':
            if (optarg == NULL)
                help(Argument_Error, Missing_Argument);
            Sflag = TRUE;
            optind--;
            for(; optind < argc && *argv[optind] != '-'; optind++)
            {
                strcat(Sorting_aux,argv[optind]);
                strcat(Sorting_aux," ");
            }
            //sscanf(optarg, "%s", &aux_reader3);
            if (optarg[0]=='a'&& optarg[1]=='l' && optarg[2]=='f' && optarg[3]=='a')
                strcpy(controlsflag,"alfa");
            else if (optarg[0]=='p' && optarg[1]=='o' && optarg[2]=='p')
                strcpy(controlsflag,"pop");
             else if (optarg[0]=='i' && optarg[1]=='n' && optarg[2]=='f'){
                strcpy(controlsflag,"inf");
                sscanf(Sorting_aux, " inf %ld-%ld ",&year,&week);
            }
            else if (optarg[0]=='d' && optarg[1]=='e' && optarg[2]=='a'){
                 strcpy(controlsflag,optarg);
                strcpy(controlsflag,"dea");
                sscanf(Sorting_aux, " dea %ld-%ld ",&year,&week);
            }
            else{
                help(Argument_Error,Unknown_Argument);
            }

        break;


        case 'D':
            if (optarg == NULL)
                help(Argument_Error, Missing_Argument);
            Dflag = TRUE;
            selectiondatapointer = optarg;
            Dargument_validity(selectiondatapointer);
            break;
        case 'P':
            Pflag = TRUE;
            optind--;
           int contagemp = 0;
            for(; optind < argc && *argv[optind] != '-'; optind++)
            {
                strcat(rescrictpointer,argv[optind]);
                strcat(rescrictpointer," ");
                contagemp = contagemp + 1;
            }
            if (contagemp < 2)
                help(Argument_Error, Missing_Argument);
            if (contagemp >3)
                help(Argument_Error, Argument_Overflow);
            break;

        case 1:
            help(Argument_Error, Missing_Argument);
        case ':':
            help(Argument_Error, Missing_Argument);

        case '?':
            if (isprint (optopt))
                help(Argument_Error, Unknown_Argument);
        }
    }

if (InputDat_flag==TRUE && (Lflag != FALSE || Sflag != FALSE || Dflag != FALSE|| Pflag != FALSE))
    help(Argument_Error, Argument_Overflow);
if(Lflag == FALSE)
    continent = "all";
if(Sflag == FALSE)
    strcpy(controlsflag,"alfa");
if(iflag==FALSE || oflag==FALSE)
    help(Argument_Error, Missing_Argument);


// header = (country_list *)malloc(1*(sizeof(country_list)));  MALLOC CUJA NECESSIDADE TEM QUE SER VERIFICADA!!-> Provavelmente não é preciso!
if (InputDat_flag==FALSE)
header = readfile(In_filename, header, continent);
if (InputDat_flag==TRUE)
header = readDATfile(In_filename, header);

aux = header;

if(Dflag!= FALSE)
    aux=dataselection(aux,selectiondatapointer);

if(Pflag != FALSE)
    aux=restricting(aux,rescrictpointer);

if(strcmp(controlsflag,"alfa")==0 && InputDat_flag== FALSE)
    aux=alphabetic_sorter(aux);
if(strcmp(controlsflag,"pop")==0)
    aux=population_sorter(aux);
if(strcmp(controlsflag,"inf")==0 || strcmp(controlsflag,"dea")==0)
    aux=CumulativeValue_sorter(aux, controlsflag,year,week);
printlist_tofile (aux, Out_filename, OutputDat_flag, Dflag, selectiondatapointer);
free_list(aux);
return 0;
}
