#include "funcoes.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>


void main() {  
    lista *Lista = malloc(sizeof(lista)); //declara a lista de usuarios
    verificaadmin(Lista);
    if (loginadmin(Lista, Lista->vetor[0]) == 1) {
        menuadmin(Lista);
    } else {
        printf("\nAcesso Negado.\n");
        return;
    }

}