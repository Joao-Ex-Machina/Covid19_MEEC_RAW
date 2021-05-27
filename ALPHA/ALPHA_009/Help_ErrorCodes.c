/*-----------------------------------------------------------------------------------------------------+
| Help_ErrorCodes.c      |Help manager module for covid19_main.c                                       |
|                        |                                                                             |
|                        |                                                                             |
+------------------------------------------------------------------------------------------------------+
| Authors: Joao Barreiros C. Rodrigues (Joao-Ex-Machina) nº99968, Henrique "Delfas" Delfino            |
| Date: 19 May 2021                                                                                    |
+-----------------------------------------------------------------------------------------------------*/
#include "covid19.h"

void help(int Primary_ErrorCode,char Secondary_ErrorCode){
    if (Primary_ErrorCode !=0)
        printf("Error type %d%c \n", Primary_ErrorCode, Secondary_ErrorCode);
    switch (Primary_ErrorCode){
        case 0:
            printf(HELP_MESSAGE); //user called help
            exit(0);
        break;
        case 1:
            printf(" Command Prompt Argument Error:");
            switch (Secondary_ErrorCode){
                case 'A':
                    printf ("Unknown Argument");
                    exit(101);
                    break;
                case 'B':
                    printf(" Missing Argument");
                    exit(102);
                    break;
                case 'C':
                    printf(" Argument Overflow");
                    exit(103);
                    break;

            }
        break;
        case 2:
            printf(" Read File Error:");
            switch (Secondary_ErrorCode){
                case '0':
                    printf(" Unable to open file to read.\n Check if the desired file is in the same directory as the .out, remember that the program is case and extension sensitive ");
                    exit(200);
                    break;
                case 'A':
                    printf(" Wrong Format on File");
                    exit(201);
                    break;
                case 'B':
                    printf(" Missing Data on File");
                    exit(202);
                    break;
                case 'C':
                    printf(" Overflow Data on File");
                    exit(203);
                    break;


            }
        break;
        case 3:
            switch (Secondary_ErrorCode){
                case '0':
                    perror(" Write File Error:");
                    exit(300);
                    break;


            }
            break;
    }
}

void string_validity(char country[30],char country_code[4],char continent[15]){
    int i=0;
    for(i=0; i<30; ++i){
        if(isdigit(country[i])!=0)
            help(Read_Error, Wrong_Format_On_File);
    }
    for(i=0; i<4; ++i){
        if(isdigit(country_code[i])!=0)
            help(Read_Error, Wrong_Format_On_File);
    }
    for(i=0; i<15; ++i){
        if(isdigit(country_code[i])!=0)
            help(Read_Error, Wrong_Format_On_File);
    }


}



