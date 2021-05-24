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
    int oflag = FALSE, iflag = FALSE, Lflag = FALSE, Sflag = FALSE, Dflag = FALSE, Pflag = FALSE, InputDat_flag=FALSE, OutputDat_flag=FALSE, index, opt, length;
    char  *In_filename = NULL, *continent = NULL, controlsflag[4] = {'\0'}, *Out_filename = NULL, *selectiondatapointer = NULL, rescrictpointer[50] = {'\0'}, aux_reader[50]= {'\0'}, aux_reader2[50]= {'\0'}, aux_reader3[50]= {'\0'} ;
    long year, week;

    while((opt = getopt(argc, argv, OPTION_LIST)) != -1)
    {
        switch (opt)
        {
        case 'i': // opção com argumentos obrigatórios
            iflag = TRUE;
            length=strlen(optarg);
            sscanf(optarg, " %s", &aux_reader);
            if(aux_reader[length-4]=="."&& aux_reader[length-3]=="d"&& aux_reader[length-2]=="a"&& aux_reader[length-1]=="t")
                InputDat_flag=TRUE;
            In_filename = optarg;
        break;
        case 'o':
            oflag = TRUE;
            length=strlen(optarg);
            sscanf(optarg, " %s", &aux_reader2);
            if(aux_reader2[7]=="."&& aux_reader2[8]=="d" && aux_reader2[9]=="a" && aux_reader2[10]=="t")
                OutputDat_flag=TRUE;
            Out_filename  = optarg;
        break;
        case 'L':
            Lflag = TRUE;
            continent = optarg;
        break;
        case 'S':
            Sflag = TRUE;
            sscanf(optarg, " %s", &aux_reader3);
            if (aux_reader3[0]=="a"&& aux_reader3[1]=="l" && aux_reader3[2]=="f" && aux_reader3[3]=="a")
                strcpy(controlsflag,"alfa");
            if (aux_reader3[0]=="p"&& aux_reader3[1]=="o" && aux_reader3[2]=="p")
                strcpy(controlsflag,"pop");
             if (aux_reader3[0]=="i"&& aux_reader3[1]=="n" && aux_reader3[2]=="f"){
                strcpy(controlsflag,"inf");
                sscanf(optarg, "inf %ld-%ld",&year,&week);
            }
            if (aux_reader3[0]=="d"&& aux_reader3[1]=="e" && aux_reader3[2]=="a"){
                strcpy(controlsflag,"dea");
                sscanf(optarg, "dea %ld-%ld",&year,&week);
            }



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
    alphabetic_sorter(aux);
if(strcmp(controlsflag,"pop")==0)
    population_sorter(aux);
if(strcmp(controlsflag,"inf")==0 || strcmp(controlsflag,"dea")==0)
    CumulativeValue_sorter(aux, controlsflag,year,week);
printlist_tofile (aux, Out_filename, OutputDat_flag);

}
