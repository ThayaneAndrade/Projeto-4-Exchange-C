#include <stdio.h>
#include <string.h>
#include "funcoes.h"

int main() {
    int opcao;
    while (1) {
        printf("-----Bem vindo a CryptoSpy 2.0-----\n");
        printf("1. Registrar\n");
        printf("2. Login\n");
        printf("3. Sair\n");
        printf("Entrada: ");
        scanf("%d", &opcao);
        if(opcao == 1){
            registrar();
        }else if(opcao == 2){
            login();
        }else if(opcao == 3){
            printf("Desligando\n");
            break;
        }
    }
   

    return 0;
}