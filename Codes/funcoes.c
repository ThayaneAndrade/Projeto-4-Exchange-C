#include <stdio.h>
#include "funcoes.h"
#include <string.h>
#include <stdlib.h>

void registrar(lista *Lista) {
    FILE *arquivo = fopen("usuarios.bin", "wb"); //abre o arquivo em modo de escrita binaria

    usuario u1 = {"53406698824", "Kaique", 12345, 1000.0};
    usuario u2 = {"24889660435","Thayane", 54321, 2000.0}; //cria dois usuários provisórios conforme a struct Usuario

    fwrite(&u1, sizeof(usuario), 1, arquivo);
    fwrite(&u2, sizeof(usuario), 1, arquivo); //adiciona ambos os usuarios no arquivo

    fclose(arquivo);
    carregar_usuarios(Lista); //carrega os usuarios no vetor da lista

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

    
int inserir_usuario(lista *Lista, usuario *user){
    FILE *arquivo = fopen("usuarios.bin", "wb");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 0;
    }   
    if(Lista->qtd == 100){
        printf("Lista atingiu a capacidade maxima!\n");
        fclose(arquivo);
        return 0;
    }
    Lista->vetor[Lista->qtd] = user;
    fwrite(Lista->vetor[Lista->qtd], sizeof(usuario), 1, arquivo);
    Lista->qtd++;
    return 0;
}


void menuprincipal(lista *Lista, int *logado, int indice_logado){
    printf("\n-----Bem vindo(a) à CryptoSpy 2.0------\n");
    int opcao;
    while(*logado == 1){
    printf("\nO que deseja fazer a seguir, %s?\n", Lista->vetor[indice_logado]->nome);
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

void carregar_usuarios(lista *Lista) { //lê usuários armazenados no arquivo e coloca no vetor de ponteiros.
    Lista->qtd = 0; //reseta a quantidade de usuários na lista
    FILE *arquivo = fopen("usuarios.bin", "rb");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de usuários.\n");
        return;
    }

    usuario *u = malloc(sizeof(usuario));
    while (fread(u, sizeof(usuario), 1, arquivo) == 1) {
        Lista->vetor[Lista->qtd++] = u;
        u = malloc(sizeof(usuario)); // só aloca se leitura foi ok
    }
    free(u);  // último que não foi usado
    fclose(arquivo);
}

