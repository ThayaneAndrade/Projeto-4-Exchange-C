#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "funcoes.h"

int main() {
    char usuariologado[50];
    int senhalogada;
    int logado = 0;
    
    printf("\n\n-----Bem vindo(a) a CryptoSpy 2.0-----\n");
    int opcao;
    while (1) {
        if (!logado){
            printf("\n1. Registrar\n");
            printf("2. Login\n");
            printf("3. Sair\n");
            printf("\nEntrada: ");
            scanf("%d", &opcao);
            if(opcao == 1){
                registrar();
            }else if(opcao == 2){
                if(login(usuariologado, &senhalogada) == 1){
                    logado = 1;
                    menuprincipal(usuariologado, &senhalogada, &logado);    
                }else{
                    logado = 0;
                }
            }else if(opcao == 3){
                printf("\nDesligando...\n");
                break;
            }else{
                printf("Opção inválida. Tente novamente.\n");
            }
    }
} 
return 0;
}