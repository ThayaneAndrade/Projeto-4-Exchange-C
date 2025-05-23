#include "funcoes.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>



void verificaadmin(lista *Lista){
    carregar_usuarios(Lista);

    // abre arquivo so para verificar se existe
    FILE *arquivo = fopen("usuarios.bin","rb");
    int achou = 0;  // 0 = nao achou, 1 = achou

    if(arquivo != NULL){
        for(int i = 0; i < Lista->qtd; i++){
            if(strcmp(Lista->vetor[i]->cpf, "12345678910") == 0){
                achou = 1;
                return;
            }
        }
        fclose(arquivo);
    }

    if(achou){
        printf("Admin ja cadastrado\n");
        return;
    }

    //cria novo admin apos varrer toda a lista
    printf("Admin nao encontrado, criando novo admin...\n");
    usuario *admin = malloc(sizeof(usuario));
    strcpy(admin->cpf, "12345678910");
    strcpy(admin->nome, "admin");
    admin->senha = 54321;
    Lista->vetor[Lista->qtd] = admin;
    Lista->qtd++;

    arquivo = fopen("usuarios.bin","ab");
    if(arquivo){
        fwrite(admin, sizeof(usuario), 1, arquivo);
        fclose(arquivo);
    }
    printf("Admin criado com sucesso\n");
}

void menuadmin(lista *Lista){
    while(1){
        //menu do admin, ainda não implementado
        printf("----- Menu Admin -----\n");
        printf("1. Listar usuários\n");
        printf("2. Registrar usuário\n");
        printf("3. Excluir usuário\n");
        printf("4. Sair\n");
        int opcao = userinput(4);
        switch (opcao) {
            case 1:
                debug_imprimir_lista(Lista);
                break;
            case 2:
                registrar(Lista);
                break;
            case 3:
                return;
            case 4:
                printf("Saindo do menu admin...\n");
                return;
            default:
                printf("Opção inválida.\n");
                break;
        }
    }
}

int loginadmin(lista *Lista, usuario *adm){  //atua similar a função de login, porém só permite a entrada com as informações do adm
    char cpfDigitado[12];
    int senhaDigitada;
    printf("Digite seu CPF: ");
    scanf("%s", cpfDigitado);
    if (strlen(cpfDigitado) != 11) {
        printf("CPF inválido. Deve conter 11 dígitos.\n");
        return 0;
    }
    printf("Digite sua senha");
    senhaDigitada = userinput(99999);
    if (strcmp(cpfDigitado, adm->cpf) == 0 && senhaDigitada == adm->senha) {
        printf("\nLogin realizado com sucesso! Bem vindo(a), %s!\n", adm->nome);
        return 1;
    } else {
        printf("\nCPF ou senha incorretos.\n");
        return 0;
    }
    printf("Pressione ENTER para continuar\n");
    getchar();
    getchar();
    return 1;
}
    