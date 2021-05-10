#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct _country_name
{
    char country[30];
    char country_code[4];
    char continent[15];
    int population;
    char indicator[15];
    struct _country_name *next;
} country_name;
int main()
{
    FILE *fp = fopen("covid19_w_t01.txt","r");
    country_name *header, *aux;
    char string[300];
    char country[30];
    char country_code[4];
    char continent[15];
    int population, weekly_count, cumulative_count, year, week;
    float rate_14_day;
    char indicator[15];
    printf("%x\n", fp);
    fgets(string,150,fp);

    header = (country_name *)malloc(1*(sizeof(country_name)));
    header->next = NULL;
    aux = header;

    //separate the strings into their own variables
    while (fgets(string,300,fp)!=0)
    {
        sscanf(string, "%[a-zA-Z ],%[a-zA-Z ],%[a-zA-Z ],%d,%[a-zA-Z ],%d,%d-%d,%f,%d ", country,country_code,continent, &population, indicator, &weekly_count, &year, &week, &rate_14_day,&cumulative_count );
        printf("%s %s %s %d %s %d %d %d %f %d\n",country,country_code,continent, population, indicator, weekly_count, year, week, rate_14_day,cumulative_count);

    }
}
