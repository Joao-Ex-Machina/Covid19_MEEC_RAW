/*-----------------------------------------------------------------------------------------------------+
| covid19_main.c         |Main module for The Programming Curricular Unit final Project- "Covid19"     |
|                        |Directives can be found here:                                                |
|                        |                                                                             |
+------------------------------------------------------------------------------------------------------+
| Authors: Joao Barreiros C. Rodrigues (Joao-Ex-Machina) nº99968, Henrique "Delfas" Delfino            |
| Date: 09 May 2021                                                                                    |
+-----------------------------------------------------------------------------------------------------*/
#include "covid19.h"

int main(int argc, char *argv[]){
 country_list *header, *aux;
    int oflag = FALSE, iflag = FALSE, Lflag = FALSE, Sflag = FALSE, Dflag = FALSE, Pflag = FALSE, InputDat_flag=FALSE, OutputDat_flag=FALSE, opt, length;
    char  *In_filename = NULL, *continent = NULL, controlsflag[4] = {'\0'}, *Out_filename = NULL, *selectiondatapointer = NULL, rescrictpointer[50] = {'\0'} ;
    long year, week;

    while((opt = getopt(argc, argv, OPTION_LIST)) != -1)
    {
        switch (opt)
        {
        case 'i': // opção com argumentos obrigatórios
            iflag = TRUE;
            length=strlen(optarg);
            //sscanf(optarg, " %s", &aux_reader);
            if(optarg[length-4]=='.'&& optarg[length-3]=='d'&& optarg[length-2]=='a'&& optarg[length-1]=='t')
                InputDat_flag=TRUE;
            In_filename = optarg;
        break;
        case 'o':
            oflag = TRUE;
            length=strlen(optarg);
            //sscanf(optarg, " %s", &aux_reader2);
            if(optarg[length-4]=='.'&& optarg[length-3]=='d' && optarg[length-2]=='a' && optarg[length-1]=='t')
                OutputDat_flag=TRUE;
            Out_filename  = optarg;
        break;
        case 'L':
            Lflag = TRUE;
            continent = optarg;
        break;
        case 'S':
            Sflag = TRUE;
            //sscanf(optarg, "%s", &aux_reader3);
            if (optarg[0]=='a'&& optarg[1]=='l' && optarg[2]=='f' && optarg[3]=='a')
                strcpy(controlsflag,"alfa");
            if (optarg[0]=='p' && optarg[1]=='o' && optarg[2]=='p')
                strcpy(controlsflag,"pop");
             if (optarg[0]=='i' && optarg[1]=='n' && optarg[2]=='f'){
                strcpy(controlsflag,"inf");
                sscanf(optarg, "inf %ld-%ld",&year,&week);
            }
            if (optarg[0]=='d' && optarg[1]=='e' && optarg[2]=='a'){
                strcpy(controlsflag,"dea");
                sscanf(optarg, "dea %ld-%ld",&year,&week);
            }

        break;


        case 'D': // opção com argumento opcional
            Dflag = TRUE;
            selectiondatapointer = optarg;
            break;
        case 'P':
            if (optarg == NULL)
                break;
            Pflag = TRUE;
            optind--;
           int contagemp = 0;
            for(; optind < argc && *argv[optind] != '-'; optind++)
            {
                strcat(rescrictpointer,argv[optind]);
                strcat(rescrictpointer," ");
                contagemp = contagemp + 1;
            }
            break;

        case 1:
            help(1, 'B');
        case ':':
            if (optopt == 'i')

        case '?':
            if (isprint (optopt))
                help(1, 'A');
        }
    }

if (InputDat_flag==TRUE && (Lflag != FALSE || Sflag != FALSE || Dflag != FALSE|| Pflag != FALSE))
    help(1, 'C');
if(Lflag == FALSE)
    continent = "all";
if(Sflag == FALSE)
    strcpy(controlsflag,"alfa");
if(iflag==FALSE || oflag==FALSE)


header = (country_list *)malloc(1*(sizeof(country_list)));
if (InputDat_flag==FALSE)
header = readfile(In_filename, header, continent);
if (InputDat_flag==TRUE)
header = readDATfile(In_filename, header);

aux = header;

if(Dflag!= FALSE)
    dataselection(aux,selectiondatapointer);

if(Pflag != FALSE)
    restricting(aux,rescrictpointer);

if(strcmp(controlsflag,"alfa")==0)
    aux=alphabetic_sorter(aux);
if(strcmp(controlsflag,"pop")==0)
    aux=population_sorter(aux);
if(strcmp(controlsflag,"inf")==0 || strcmp(controlsflag,"dea")==0)
    aux=CumulativeValue_sorter(aux, controlsflag,year,week);
printlist_tofile (aux, Out_filename, OutputDat_flag);

return 0;
}
