#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "funcoes.h"

int main() {
    int indice_logado = -1;
    int senhalogada;
    int logado = 0;
    lista *Lista = malloc(sizeof(lista));

    
    printf("\n\n-----Bem vindo(a) a CryptoSpy 2.0-----\n");
    int opcao;
    while (1) {
        if (!logado){
            printf("\n1. Registrar\n");
            printf("2. Login\n");
            printf("3. Sair\n");
            printf("4. Debug\n");
            printf("\nEntrada: ");
            scanf("%d", &opcao);
            if(opcao == 1){
                logado = 0;
                registrar(Lista);
            }else if(opcao == 2){
                if ((indice_logado = login(Lista)) != -1) {
                logado = 1;
                menuprincipal(Lista, &logado, indice_logado);
                }
            }else if(opcao == 3){
                logado = 0;
                printf("\nDesligando...\n");
                break;
            }else if(opcao == 4){
                logado = 0;
                debug_imprimir_lista(Lista);
            }else{
                printf("Opção inválida. Tente novamente.\n");
            }
    } 
}
return 0;    
}