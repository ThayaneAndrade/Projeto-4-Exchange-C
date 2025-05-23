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

void menuadmin(lista *Lista, Coins *cc){
    while(1){
        //menu do admin, ainda não implementado
        printf("----- Menu Admin -----\n");
        printf("1. Listar usuários\n");
        printf("2. Registrar usuário\n");
        printf("3. Excluir usuário\n");
        printf("4. Criar criptomoeda\n");
        printf("5. Excluir criptomoeda\n");
        printf("6. Mostrar criptomoedas\n");
        printf("7. Sair\n");
        printf("\nQUANTIDADE DE CRIPTOMOEDAS ATUAIS: %d\n", cc->qtd);
        int opcao = userinput(7);
        switch (opcao) {
            case 1:
                debug_imprimir_lista(Lista);
                break;
            case 2:
                registrar(Lista);
                break;
            case 3:
                excluiruser(Lista);
                break;
            case 4:
                criarcrypto(cc);
                break;
            case 5:
                excluircrypto(cc);
                break;
            case 6:
                mostrar_cryptos(cc);
                break;
            case 7:
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
    
void excluiruser(lista *Lista){
    char cpf[12];
    printf("Digite o CPF do usuario a ser excluido: ");
    scanf("%s", cpf);
    for(int i = 0; i < Lista->qtd; i++){
        //verifica se o cpf pertence ao admin, e encerra a remoção
        if(strcmp(cpf, "12345678910") == 0){
            printf("Não é possivel remover o administrador.\n");
            printf("Pressione ENTER para continuar\n");
            getchar();
            getchar();
            return;
        }

        if(strcmp(Lista->vetor[i]->cpf, cpf) == 0){
            printf("\nUsuário encontrado: %s\n", Lista->vetor[i]->nome);
            printf("  Nome:  %s\n", Lista->vetor[i]->nome);
            printf("  CPF:  %s\n", Lista->vetor[i]->cpf);
            printf("  Senha: %d\n", Lista->vetor[i]->senha);
            printf("  Saldo: %.2f\n", Lista->vetor[i]->saldo);
            printf("\n");
            printf("Deseja continuar com a exclusão?\n");
            printf("1. Sim\n");
            printf("2. Não\n");
            int confirmacao = userinput(2);
            if (confirmacao != 1) {
                printf("Exclusão cancelada.\n");
                printf("Pressione ENTER para continuar\n");
                getchar();
                getchar();
                return;
            }
            free(Lista->vetor[i]);
            for(int j = i; j < Lista->qtd - 1; j++){
                Lista->vetor[j] = Lista->vetor[j + 1];
            }
            Lista->qtd--;
            printf("Usuario %s excluido com sucesso!\n", cpf);
            arquivar_usuarios(Lista);
            return;
        }
    }
    printf("Usuario %s nao encontrado!\n", cpf);
}

void criarcrypto(Coins *cc){
    if (cc->qtd >= 10) {
        printf("Limite de criptomoedas atingido.\n");
        return;
    }
    char nome[5];
    printf("Digite o nome da nova criptomoeda: ");
    scanf("%4s", nome);
    for (int i = 0; i < cc->qtd; i++) {    //verifica duplicata
        if (strcmp(cc->vetor[i]->nome, nome) == 0) {
            printf("Criptomoeda ja existe.\n");
            return;
        }
    }
    cryptomoeda *c = malloc(sizeof(cryptomoeda));
    strcpy(c->nome, nome);
    printf("Digite o valor da nova criptomoeda: ");
    c->valor = uservalor();
    printf("Digite a taxa de compra: ");
    c->taxa_compra = uservalor();
    printf("Digite a taxa de venda: ");
    c->taxa_venda = uservalor();
    cc->vetor[cc->qtd++] = c; //guarda no array de ponteiros
    printf("Criptomoeda %s criada com sucesso!\n", nome);
    getchar(); getchar();
    arquivar_cryptos(cc);
}

void mostrar_cryptos(Coins *cc){
    printf("\n----- Criptomoedas -----\n");
    for(int i = 0; i < cc->qtd; i++){
        cryptomoeda *c = cc->vetor[i];
        printf("Moeda: %s\n", c->nome);
        printf("Valor: %.2f\n", c->valor);
        printf("Taxa compra: %.2f%%\n", c->taxa_compra*100);
        printf("Taxa venda: %.2f%%\n\n", c->taxa_venda*100);
    }
    printf("Pressione ENTER para continuar");
    getchar();
    getchar();
}

void excluircrypto(Coins *cc){
    char nome[5];
    printf("Digite o nome da criptomoeda a ser excluida: ");
    scanf("%4s", nome);
    for (int i = 0; i < cc->qtd; i++) {
        if (strcmp(cc->vetor[i]->nome, nome) == 0) {
            free(cc->vetor[i]);
            for (int j = i; j < cc->qtd - 1; j++) {
                cc->vetor[j] = cc->vetor[j + 1];
            }
            cc->qtd--;
            cc->vetor[cc->qtd] = NULL; // Limpa o último ponteiro
            arquivar_cryptos(cc);
            printf("Criptomoeda %s excluida com sucesso!\n", nome);
            getchar();
            getchar();
            return;
        }
    }
    printf("Criptomoeda %s nao encontrada!\n", nome);
}