#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct cdi{
	char* micro;
	char* penis;
	int nota;
	struct cdi* next;

} pimentel;
void printalista(pimentel *head){
pimentel *temporary = head;

while (temporary != NULL){
        printf("ola amaral");
    printf(" %s %s %d \n", temporary->micro, temporary->penis, temporary->nota);
    temporary = temporary->next;
}
printf("\n");

}
void liberta(pimentel *head){
pimentel *auxilio;

while(head != NULL){
auxilio = head;
head = auxilio->next;
free(auxilio->micro);
free(auxilio->penis);
free(auxilio);
}

}

pimentel *criar_novo_cdi(char *micro, char *penis, int nota){
    pimentel *resultado = (pimentel*)malloc(sizeof(pimentel));
    resultado->micro = (char *)malloc((strlen(micro)+1)*sizeof(char));
    resultado->penis = (char *)malloc((strlen(penis)+1)*sizeof(char));
    strcpy(resultado->micro,micro);
    strcpy(resultado->penis,penis);
    resultado->nota = nota;
    resultado->next = NULL;
    return resultado;

}
int main()
{
    pimentel *head;
    pimentel *tmp;

    head = criar_novo_cdi("joaquim", "ze", 32);
    tmp = head;
    //while
    tmp->next = criar_novo_cdi("submeta_da_proxima", "oke", 22);
    tmp = tmp->next;
    tmp->next = criar_novo_cdi("meio homossexual", "punheta", 12);


    printalista(head);
    liberta(head);



    return 0;
}
