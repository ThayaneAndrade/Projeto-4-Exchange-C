#include <stdio.h>
#include "funcoes.h"
#include <string.h>
#include <stdlib.h>

void registrar(lista *Lista) {
    FILE *arquivo = fopen("usuarios.bin", "wb");
    usuario u1 = {"53406698824", "Kaique", 12345, 1000.0, 0.2344, 47.5, 20.0};
    usuario u2 = {"24889660435", "Thayane", 54321, 2000.0, 1.2345, 55, 10};
    fwrite(&u1, sizeof(usuario), 1, arquivo);
    fwrite(&u2, sizeof(usuario), 1, arquivo);
    fclose(arquivo);
    carregar_usuarios(Lista);
}

int login(lista *Lista) {
    char cpfDigitado[12];
    int senhaDigitada;
    printf("Digite seu CPF: ");
    scanf("%s", cpfDigitado);
    printf("Digite sua senha: ");
    scanf("%d", &senhaDigitada);

    for (int i = 0; i < Lista->qtd; i++) {
        if (strcmp(Lista->vetor[i]->cpf, cpfDigitado) == 0 &&
            Lista->vetor[i]->senha == senhaDigitada) {
            printf("\nLogin realizado com sucesso! Bem vindo(a), %s!\n", Lista->vetor[i]->nome);
            return i;
        }
    }
    printf("\nCPF ou senha incorretos.\n");
    return -1;
}

int solicita_senha(lista Lista, int indice_logado) {
    int senha;
    printf("\nDigite sua senha: ");
    scanf("%d", &senha);
    if (senha == Lista.vetor[indice_logado]->senha) {
        return 1;
    } else {
        printf("\nSenha incorreta!\n");
        printf("\nENTER para continuar");
        getchar();
        getchar();
        return 0;
    }
}

int inserir_usuario(lista *Lista, usuario *user) {
    if (Lista->qtd == 100) {
        printf("Lista atingiu a capacidade maxima!\n");
        return 0;
    }
    Lista->vetor[Lista->qtd] = user;
    Lista->qtd++;
    return 0;
}

void menuprincipal(lista *Lista, int *indice_logado) {
    printf("\n-----Bem vindo(a) à CryptoSpy 2.0------\n");
    int opcao;

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
        printf("\nEntrada: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                deposito(Lista, *indice_logado);
                break;
            case 2:
                printf("*Saque\n");
                break;
            case 3:
                saldo(Lista, *indice_logado);
                break;
            case 9:
                arquivar_usuarios(Lista, *indice_logado);
                printf("\n*Saindo...\n");
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
    }
}

void carregar_usuarios(lista *Lista) {
    Lista->qtd = 0;
    FILE *arquivo = fopen("usuarios.bin", "rb");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de usuários.\n");
        return;
    }

    usuario *u = malloc(sizeof(usuario));
    while (fread(u, sizeof(usuario), 1, arquivo) == 1) {
        inserir_usuario(Lista, u);
        u = malloc(sizeof(usuario));
    }
    free(u);
    fclose(arquivo);
}

void arquivar_usuarios(lista *Lista, int indice_logado) {
    FILE *arquivo = fopen("usuarios.bin", "wb");
    for (int i = 0; i < Lista->qtd; i++) {
        fwrite(Lista->vetor[i], sizeof(usuario), 1, arquivo);
    }
    fclose(arquivo);
}

void saldo(lista *Lista, int indice_logado) {
    if (solicita_senha(*Lista, indice_logado) == 0) {
        return;
    }
    printf("\n-------Saldo-------\n");
    printf("\nNome: %s\n", Lista->vetor[indice_logado]->nome);
    printf("CPF: %s\n", Lista->vetor[indice_logado]->cpf);
    printf("\nSeu saldo é: \n\n%.2f BRL\n", Lista->vetor[indice_logado]->saldo);
    printf("%.5f BTC\n", Lista->vetor[indice_logado]->btc);
    printf("%.3f ETH\n", Lista->vetor[indice_logado]->eth);
    printf("%.2f XRP\n", Lista->vetor[indice_logado]->xrp);
    printf("\nENTER para continuar");
    getchar();
    getchar();
}

void deposito(lista *Lista, int indice_logado) {
    if (solicita_senha(*Lista, indice_logado) == 0) {
        return;
    }
    float valor;
    printf("\nDigite o valor a ser depositado: ");
    scanf("%f", &valor); 
    if (valor <= 0) {
        printf("Valor inválido.\n");
        return;
    }
    Lista->vetor[indice_logado]->saldo += valor;
    printf("Depósito realizado com sucesso! Seu novo saldo é: %.2f\n", Lista->vetor[indice_logado]->saldo);
}
