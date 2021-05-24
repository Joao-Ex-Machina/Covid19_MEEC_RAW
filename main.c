/*-----------------------------------------------------------------------------------------------------+
| covid19_main.c         |Main module for The Programming Curricular Unit final Project- "Covid19"     |
|                        |Directives can be found here:                                                |
|                        |                                                                             |
+------------------------------------------------------------------------------------------------------+
| Authors: Joao Barreiros C. Rodrigues (Joao-Ex-Machina) nº99968, Henrique "Delfas" Delfino            |
| Date: 09 May 2021                                                                                    |
+-----------------------------------------------------------------------------------------------------*/
#include "covid19.h"

//-i f_texto1.csv -L all -S inf 2020-27 -D inf -P max 5000 -o f_dados.dat

int main(int argc, char *argv[]){
int oflag = 0, iflag = 0, Lflag = 0, Sflag = 0, Dflag = 0, Pflag = 0;
char  *filename = NULL, *continent = NULL, controlsflag[50] = {'\0'}, *filewrite = NULL, *selectiondatapointer = NULL, rescrictpointer[50] = {'\0'} ;
int index;
int opt;

    while((opt = getopt(argc, argv, LISTA_OPCOES)) != -1)
        // -1 quando não há mais opções para processar
        // optstring : para indicar que a opção requer um parametro
        // optstring :: para indicar que o parametro da opção é opcional, o parametro deve estar junto à opção sem espaço
        // optstring - no começo quando se pretende processar os argumentos sem opção no loop while
    {
        printf(">optind %d %s %c\n",optind, optarg, opt);
        switch (opt)
        {
        case 'i': // opção com argumentos obrigatórios
            iflag = 1;
            filename = optarg;
            break;
        case 'o':
            oflag = 1;
        filewrite  = optarg;
        break;
        case 'L': // opção com argumento opcional
            Lflag = 1;
            printf("devia ser all mas nao sou %s\n", optarg);
            continent = optarg;
            printf ("%s\n", continent);
            break;
        case 'S':
            if (optarg == NULL)
                break;
            Sflag = 1;
            optind--;
           int contagem = 0;
            for(; optind < argc && *argv[optind] != '-'; optind++)
            {
                strcat(controlsflag,argv[optind]);
               strcat(controlsflag," ");
                contagem = contagem + 1;
                printf ("%d", contagem);
                printf("istu aki é %d\n", optind);
                printf(">> Vários Argumentos: %s\n",argv[optind]);
            }
            break;
        case 'D': // opção com argumento opcional
            Dflag = 1;
            selectiondatapointer = optarg;
            break;
        case 'P':
            if (optarg == NULL)
                break;
            Pflag = 1;
            optind--;
           int contagemp = 0;
            for(; optind < argc && *argv[optind] != '-'; optind++)
            {
                strcat(rescrictpointer,argv[optind]);
               strcat(rescrictpointer," ");
                contagemp = contagemp + 1;
                printf ("%d", contagemp);
                printf("istu aki é %d\n", optind);
                printf(">> Vários Argumentos: %s\n",argv[optind]);
            }
            break;

        case 1:
            printf("Argumento sem opção %s\n",optarg);
            break;
        case ':':
            if (optopt == 'i')
                fprintf (stderr, "> a opcao -%c requere um argumento.\n", optopt);
            return 1;
        case '?':
            if (isprint (optopt))
                fprintf (stderr, "> opcao `-%c' desconhecida. v2\n", optopt);
            return 1;
        }
    }
    printf("oflag = %d, filewrite  = %s iflag = %d, filename = %s, Lflag = %d, continent = %s, Sflag = %d, controlsflag = %s, Dflag = %d e seleção = %s, Pflag= %d e restricao = %s\n",
           oflag, filewrite , iflag, filename, Lflag, continent, Sflag, controlsflag, Dflag, selectiondatapointer, Pflag, rescrictpointer);
if(Lflag == 0)
    continent = "all";
if(Sflag == 0)
    strcpy(controlsflag,"alfa");
if(Dflag== 0)
    selectiondatapointer = "ok";
/*if(Pflag == 0)
    strcpy(rescrictpointer,NULL);*/

 country_list *header, *aux;
 week_list *auxweek;
 header = (country_list *)malloc(1*(sizeof(country_list)));
    header->next = NULL;

header = readfile(filename, &header, continent);
aux = header;
printf("antes do data selection");
dataselection(aux,selectiondatapointer);
restricting(aux,rescrictpointer);
}
