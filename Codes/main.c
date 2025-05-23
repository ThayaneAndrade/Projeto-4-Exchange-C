#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "funcoes.h"

int main(void) {
    int indice_logado = -1;                  //indica indice do usuario logado
    lista *Lista = malloc(sizeof(lista));    //declara lista de usuarios
    Lista->qtd = 0;
    verificaadmin(Lista);

    Coins cc;
    cc.qtd = 0;                              //inicia sem criptomoedas
    for (int i = 0; i < 10; i++)
        cc.vetor[i] = NULL;
    carregar_cryptos(&cc);                   //carrega cryptos de arquivo

    printf("\n\n----- Bem vindo a CryptoSpy 2.0 -----\n");
    while (indice_logado == -1) {            //enquanto nao logado
        printf("1. Login\n");
        printf("2. Sair\n");
        printf("3. Debug\n");
        int opcao = userinput(3);

        if (opcao == 1) {
            if ((indice_logado = login(Lista)) != -1) {
                menuprincipal(Lista, &indice_logado, &cc);
            }
        } else if (opcao == 2) {
            printf("\nDesligando...\n");
            break;
        } else if (opcao == 3) {
            debug_imprimir_lista(Lista);
        } else {
            printf("Opcao invalida. Tente novamente.\n");
        }
    }

    //libera memoria de cryptos
    for (int i = 0; i < cc.qtd; i++)
        free(cc.vetor[i]);
    //libera memoria de usuarios
    for (int i = 0; i < Lista->qtd; i++)
        free(Lista->vetor[i]);
    free(Lista);

    return 0;
}
