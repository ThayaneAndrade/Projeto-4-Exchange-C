#include <stdio.h>
#include "funcoes.h"
#include <string.h>
#include <stdlib.h>

void registrar() {
    FILE *arquivo = fopen("usuarios.bin", "ab");
    usuario *user = malloc(sizeof(usuario));
    if (user == NULL) {
        printf("Erro ao alocar memória.\n");
        fclose(arquivo);
        return;
    }
    char *nome = "Kaique";
    int senha = 1234;
    strcpy(user->nome, nome);
    user->senha = senha;
    fwrite(user, sizeof(usuario), 1, arquivo);
    printf("\n***Usuário registrado com sucesso!***\n");
    free(user);
    fclose(arquivo);
    return;
}

int login(char *usuariologado, int *senhalogada)
{
    FILE *arquivo = fopen("usuarios.bin", "rb");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 0;
    }
    usuario *user = malloc(sizeof(usuario));
    if (user == NULL) {
        printf("Erro ao alocar memória.\n");
        fclose(arquivo);
        return 0;
    }
    printf("Digite seu nome: ");
    scanf("%s", user->nome);
    printf("Digite sua senha: ");
    scanf("%d", &user->senha);

    usuario *user2 = malloc(sizeof(usuario)); //
    if (user2 == NULL) {
        printf("Erro ao alocar memória.\n");
        free(user);
        fclose(arquivo);
        return 0;
    }
    while (fread(user2, sizeof(usuario), 1, arquivo) == 1) {
        if (strcmp(user->nome, user2->nome) == 0 && user->senha == user2->senha) {
            printf("\n\nLogin bem-sucedido!\n");
            strcpy(usuariologado, user->nome);
            *senhalogada = user->senha;
            free(user);
            free(user2);
            fclose(arquivo);
            return 1;
        }
    }
    printf("\nNome ou senha incorretos.\n");
    free(user);
    free(user2);
    fclose(arquivo);
}
    
void menuprincipal(char *usuariologado, int *senhalogada, int *logado){
    printf("\n\n-----Bem vindo(a) à CryptoSpy 2.0------\n");
    int opcao;
    while(*logado == 1){
    printf("O que deseja fazer a seguir, %s?\n\n", usuariologado);
    printf("1. Deposito\n");
    printf("2. Saque\n");
    printf("3. Saldo\n");
    printf("4. Extrato\n");
    printf("5. Comprar Crypto\n");
    printf("6. Vender Crypto\n");
    printf("7. Mostrar Cotação\n");
    printf("8. Atualizar Cotação\n");
    printf("9. Sair\n");
    printf("\nEntrada: ");
    scanf("%d", &opcao);
    switch (opcao) {
        case 1:
            printf("*Deposito\n");
            break;
        case 2:
            printf("*Saque\n");
            break;
        case 3:
            printf("*Saldo\n");
            break;
        case 4:
            printf("*Extrato\n");
            break;
        case 5:
            printf("*Comprar Crypto\n");
            break;
        case 6:
            printf("*Vender Crypto\n");
            break;
        case 7:
            printf("*Mostrar Cotação\n");
            break;
        case 8:
            printf("*Atualizar Cotação\n");
            break;
        case 9:
            printf("\n*Saindo...\n");
            *logado = 0;
            break;
        default:
            printf("Opção inválida.\n");
        }
    }return;
}