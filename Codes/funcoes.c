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
    printf("Usuário registrado com sucesso!\n");
    free(user);
    fclose(arquivo);
}

void login(){
    FILE *arquivo = fopen("dados.bin", "rb");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }
    usuario *user = malloc(sizeof(usuario));
    if (user == NULL) {
        printf("Erro ao alocar memória.\n");
        fclose(arquivo);
        return;
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
        return;
    }
    while (fread(user2, sizeof(usuario), 1, arquivo) == 1) {
        if (strcmp(user->nome, user2->nome) == 0 && user->senha == user2->senha) {
            printf("Login bem-sucedido!\n");
            free(user);
            free(user2);
            fclose(arquivo);
            return;
        }
    }
    printf("Nome ou senha incorretos.\n");
    free(user);
    free(user2);
    fclose(arquivo);
}
    