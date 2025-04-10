#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "funcoes.h"
 
int main() {
    int indice_logado = -1; //índica dinamicamente qual usuário está conectado, baseado no seu índice no vetor de usuarios (EX: 1 = Kaique, 2 = Thayane, 3 = ...)
    lista *Lista = malloc(sizeof(lista)); //declara a lista de usuarios
    registrar(Lista); //chama a função de registro, que cria dois usuários provisórios e os armazena no arquivo usuarios.bin
 
    printf("\n\n-----Bem vindo(a) a CryptoSpy 2.0-----\n"); //título
    int opcao;
    while (indice_logado == -1) { //enquanto o usuário não estiver logado, entrará na tela de login.
            printf("\n1. Registrar\n");
            printf("2. Login\n");
            printf("3. Sair\n");
            printf("4. Debug\n");
            printf("\nEntrada: ");
            scanf("%d", &opcao);
            if(opcao == 1){
                registrar(Lista);
            }else if(opcao == 2){
                if ((indice_logado = login(Lista)) != -1) { //tenta fazer login, se bem sucedido, armazena o índice do usuário conectado, se não, índice -1 (ninguém)
                menuprincipal(Lista, &indice_logado);
                }
            }else if(opcao == 3){
                printf("\nDesligando...\n");
                break;
            }else if(opcao == 4){
                debug_imprimir_lista(Lista);
            }else{
                printf("Opção inválida. Tente novamente.\n");
            }
}
return 0;    
}