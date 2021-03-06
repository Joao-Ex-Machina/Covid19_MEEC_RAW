/*-----------------------------------------------------------------------------------------------------+
| Help_ErrorCodes.c      |Help and Error detection module for covid19_main.c                           |
|                        |                                                                             |
|                        |                                                                             |
+------------------------------------------------------------------------------------------------------+
| Authors: Joao Barreiros C. Rodrigues (Joao-Ex-Machina) n?99968, Henrique "Delfas" Delfino            |
| Date: 19 May 2021                                                                                    |
+-----------------------------------------------------------------------------------------------------*/
#include "covid19.h"

void help(int Primary_ErrorCode,char Secondary_ErrorCode){
    if (Primary_ErrorCode !=0)
        printf("Error type %d %c", Primary_ErrorCode, Secondary_ErrorCode);
    switch (Primary_ErrorCode){
        case 0:
            perror(HELP_MESSAGE);
            exit(0);
        break;
        case 1:
            perror(" Command Prompt Argument Error-");
            switch (Secondary_ErrorCode){
                case 'A':
                    perror(" Unknown Argument");
                    exit(101);
                    break;
                case 'B':
                    perror(" Missing Argument");
                    exit(102);
                    break;
                case 'C':
                    perror(" Argument Overflow");
                    exit(103);
                    break;
            }
        break;
        case 2:
            perror(" Read File Error-");
            switch (Secondary_ErrorCode){
                case 'A':
                    perror(" Wrong Format on File");
                    exit(201);
                    break;
                case 'B':
                    perror(" Missing Data on File");
                    exit(202);
                case 'C':
                    perror(" Overflow Data on File");
                    exit(203);

        break;

            }
    }
}
int DotDat_Argument_Overflow(int argc, char *argv[]){
    int length =0, i=0, DotDat_flag=FALSE, Overf_flag=FALSE, Primary_ErrorCode=0;
    char Secondary_ErrorCode='\0';
    for(i=0; i< argc; i++ ){
        length= strlen(argv[i]);
        if(argv[i][0]=='-'&& argv[i][1]=='i'&& argv[i][length-3]=='.'&& argv[i][length-2]=='d'&& argv[i][length-1]=='a'&& argv[i][length]=='t') // check if the -i argument is a _filename.dat
            DotDat_flag = TRUE;
        if(argv[i][0]=='-' && (argv[i][1]!='o' || argv[i][1]!='i')) //check if there is any other argument other than -o or -i
            Overf_flag = TRUE;
        if(DotDat_flag == TRUE && Overf_flag == TRUE ){
            Primary_ErrorCode = 1;
            Secondary_ErrorCode ='C';
            help(Primary_ErrorCode, Secondary_ErrorCode);
        }
    }
    return DotDat_flag;
}
void Missing_Arguments(int argc, char *argv[]){
    int MissI_flag=TRUE, MissO_flag=TRUE,i=0 ,Primary_ErrorCode=0;
    char Secondary_ErrorCode='\0';
    for(i=0; i< argc; i++ ){
        if(argv[i][0]=='-'&& argv[i][1]=='i') // check if the -i argument is present
            MissI_flag = FALSE;
        if(argv[i][0]=='-' && (argv[i][1]!='o')) //check if the -o argument is present
            MissO_flag = FALSE;
    }
    if(MissI_flag == TRUE || MissO_flag == TRUE ){
            Primary_ErrorCode = Argument_Error;
            Secondary_ErrorCode = Missing_Argument;
            help(Primary_ErrorCode, Secondary_ErrorCode);
        }
}

void DataNumber_On_File(int number_commas){
   int Primary_ErrorCode=0;
   char Secondary_ErrorCode='\0';
   if(number_commas !=8){
    Primary_ErrorCode=2;
    if(number_commas < 8)
        Secondary_ErrorCode='B';
    if(number_commas > 8)
        Secondary_ErrorCode='C';
    help(Primary_ErrorCode, Secondary_ErrorCode);
   }
}
