#include "funcoes.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>


int main(void) {
    Coins cc;
    cc.qtd = 0;
    carregar_cryptos(&cc);
    lista *Lista = malloc(sizeof(lista));
    Lista->qtd = 0;
    verificaadmin(Lista);
    if(loginadmin(Lista, Lista->vetor[0])==1){
        menuadmin(Lista, &cc);
    } else {
        printf("\nAcesso Negado.\n");
    }
    for(int i=0;i<cc.qtd;i++) free(cc.vetor[i]);
    return 0;
}