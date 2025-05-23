#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "funcoes.h"


 void menuprincipal(lista *Lista, int *indice_logado, Coins *cc) {
    printf("\n-----Bem vindo(a) à CryptoSpy 2.0------\n");
    printf("Quantidade de criptomoedas atuais: %d\n", cc->qtd);
 
    while (*indice_logado != -1) {
        printf("\nO que deseja fazer a seguir, %s?\n", Lista->vetor[*indice_logado]->nome);
        printf("1. Deposito\n");
        printf("2. Saque\n");
        printf("3. Saldo\n");
        printf("4. Extrato\n");
        printf("5. Comprar Crypto\n");
        printf("6. Vender Crypto\n");
        printf("7. Mostrar Cotação\n");
        printf("8. Atualizar Cotação\n");
        printf("9. Sair\n");
        int opcao = userinput(9);
        switch (opcao) {
            case 1:
                deposito(Lista, *indice_logado);
                break;
            case 2:
                saque(Lista, *indice_logado);
                break;
            case 3:
                saldo(Lista, *indice_logado);
                break;
            case 4:
                extrato(Lista, *indice_logado);
                break;
            case 5:
                compra_crypto(Lista, *indice_logado, cc);
                break;
            case 6:
                vender_crypto(Lista, *indice_logado, cc);
                break;
            case 7:
                mostrar_cotacao(cc);
                break;
            case 8:
                atualizar_cotacao(cc);
                break;
            case 9:
                printf("\nSaindo...\n");
                *indice_logado = -1;
                break;
            default:
                printf("Opção inválida.\n");
        }
    }
}

void debug_imprimir_lista(lista *l) {
    printf("\n---- DEBUG: Usuários na lista ----\n");
    for (int i = 0; i < l->qtd; i++) {
        printf("Usuário %d:\n", i + 1);
        printf("  Nome:  %s\n", l->vetor[i]->nome);
        printf("  CPF:  %s\n", l->vetor[i]->cpf);
        printf("  Senha: %d\n", l->vetor[i]->senha);
        printf("  Saldo: %.2f\n", l->vetor[i]->saldo);
        printf("  BTC:   %.5f\n", l->vetor[i]->btc);
        printf("  ETH:   %.3f\n", l->vetor[i]->eth);
        printf("  XRP:   %.2f\n", l->vetor[i]->xrp);
        printf("\n");
    }
}