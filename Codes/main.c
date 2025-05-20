#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "funcoes.h"
#include <time.h>

int main() {
    int indice_logado = -1; //índica dinamicamente qual usuário está conectado, baseado no seu índice no vetor de usuarios (EX: 1 = Kaique, 2 = Thayane, 3 = ...)
    lista *Lista = malloc(sizeof(lista)); //declara a lista de usuarios
    carregar_usuarios(Lista); //carrega os usuarios do arquivo para o vetor de ponteiros

    //declaração das criptomoedas;
    cryptomoeda *bitcoin = malloc(sizeof(cryptomoeda));
    strcpy(bitcoin->nome, "BTC");
    bitcoin->valor = 467458.20;
    bitcoin->taxa_compra = 0.03;
    bitcoin->taxa_venda = 0.02;

    cryptomoeda *ethereum = malloc(sizeof(cryptomoeda));
    strcpy(ethereum->nome, "ETH");
    ethereum->valor = 9264.65;
    ethereum->taxa_compra = 0.01;
    ethereum->taxa_venda = 0.02;

    cryptomoeda *ripple = malloc(sizeof(cryptomoeda));
    strcpy(ripple->nome, "XRP");
    ripple->valor = 11.77;
    ripple->taxa_compra = 0.01;
    ripple->taxa_venda = 0.01;
 
    printf("\n\n-----Bem vindo(a) a CryptoSpy 2.0-----\n"); //título
    while (indice_logado == -1) { //enquanto o usuário não estiver logado, entrará na tela de login.
            printf("\n1. Registrar\n");
            printf("2. Login\n");
            printf("3. Sair\n");
            printf("4. Debug\n");
            int opcao = userinput(4);
            if(opcao == 1){
                registrar(Lista);
            }else if(opcao == 2){
                if ((indice_logado = login(Lista)) != -1) { //tenta fazer login, se bem sucedido, armazena o índice do usuário conectado, se não, índice -1 (ninguém)
                menuprincipal(Lista, &indice_logado, bitcoin, ethereum, ripple); //se o login for bem sucedido, chama o menu principal
                }
            }else if(opcao == 3){
                printf("\nDesligando...\n");
                break;
            }else if(opcao == 4){
                debug_imprimir_lista(Lista);
            }else{
                printf("Opção inválida. Tente novamente.\n");
            }
            }return 0;
}
 
