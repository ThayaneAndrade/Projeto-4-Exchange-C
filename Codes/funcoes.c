#include <stdio.h>
#include "funcoes.h"
#include <string.h>
#include <stdlib.h>
 
void registrar(lista *Lista) { //a função registro ainda não é necessária para o projeto final, porém decidimos implementar apenas para ilustrar melhor o funcionamento do código.
    FILE *arquivo = fopen("usuarios.bin", "wb"); //abre o arquivo em modo de escrita binaria
 
    usuario u1 = {"53406698824", "Kaique", 12345, 1000.0, 0.2344, 47.5, 20.0}; //cria dois usuários provisórios conforme a struct Usuario
    usuario u2 = {"24889660435","Thayane", 54321, 2000.0, 1.2345, 55, 10}; //cria dois usuários provisórios conforme a struct Usuario
 
    fwrite(&u1, sizeof(usuario), 1, arquivo);
    fwrite(&u2, sizeof(usuario), 1, arquivo); //adiciona ambos os usuarios no arquivo
 
    fclose(arquivo);
    carregar_usuarios(Lista); //carrega os usuarios no vetor da lista
 
}
 
int login(lista *Lista) {
    char cpfDigitado[12]; //armazena 11 digitos do cpf + 1 para o '\0' no ato do login
    int senhaDigitada; //armazena a senha digitada pelo usuário no ato do login
 
    printf("Digite seu CPF: ");
    scanf("%s", cpfDigitado);
    printf("Digite sua senha: ");
    scanf("%d", &senhaDigitada);
 
    for (int i = 0; i < Lista->qtd; i++) {
        if (strcmp(Lista->vetor[i]->cpf, cpfDigitado) == 0 &&
            Lista->vetor[i]->senha == senhaDigitada) { //compara o cpf e a senha digitados com os armazenados no vetor de usuarios
            printf("\nLogin realizado com sucesso! Bem vindo(a), %s!\n", Lista->vetor[i]->nome);
            return i;
        }
    }
    printf("\nCPF ou senha incorretos.\n");
    return -1;
}
 
int solicita_senha(lista Lista, int indice_logado) { //função comum usada frequentemente sempre que for solicitado a senha do usuário.
    int senha;
    printf("\nDigite sua senha: ");
    scanf("%d", &senha);
    if (senha == Lista.vetor[indice_logado]->senha) { //compara a senha digitada com a senha armazenada no vetor de usuarios
        return 1; //retorna positivo se bem sucedida
    } else {
        printf("\nSenha incorreta!\n");
        printf("\nENTER para continuar"); //caso contrário, exibe uma mensagem e aguarda uma confirmação do usuário.
        getchar(); //limpa o buffer
        getchar(); //aguarda o usuário pressionar ENTER
        return 0;
    }
}
    
int inserir_usuario(lista *Lista, usuario *user){ //funçao responsável por inserir os usuários no vetor de ponteiros, ou "lista de usuários"
    if(Lista->qtd == 100){ //verifica se o vetor já atingiu o limite de 100 ponteiros.
        printf("Lista atingiu a capacidade maxima!\n");
        return 0;
    }
    Lista->vetor[Lista->qtd] = user; //coloca o usuario criado no vetor, no índice relativo a quantidade atual de usuários existentes
    Lista->qtd++; //incrimenta a quantidade de ponteiros no vetor (usuarios na lista)
    return 0;
}
 
 
void menuprincipal(lista *Lista, int *indice_logado) { //função que roda o menu principal em loop, enquanto um usuário estiver logado.
    printf("\n-----Bem vindo(a) à CryptoSpy 2.0------\n");
    int opcao;
 
    while (*indice_logado != -1) {
        printf("\nO que deseja fazer a seguir, %s?\n", Lista->vetor[*indice_logado]->nome); //exibe o nome do usuário logado
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
 
        switch (opcao) { //metodo switch para manipular as opções do menu
            case 1:
                printf("*Deposito\n");
                break; //utilizar um break após cada case para evitar que o código continue rodando após o case atual (fallthrough)
            case 2:
                printf("*Saque\n");
                break;
            case 3:
                saldo(Lista, *indice_logado);
                break;
            case 9:
                printf("\n*Saindo...\n");
                *indice_logado = -1;
                break;
            default:
                printf("Opção inválida.\n");
        }
    }
}
 
 
 
void debug_imprimir_lista(lista *l) { //função provisória criada para verificar se os usuários estão posicionados corretamente no vetor de ponteiros.
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
    while (fread(u, sizeof(usuario), 1, arquivo) == 1) { //leitura do arquivo
        inserir_usuario(Lista, u); //insere o usuário lido no vetor de ponteiros
        u = malloc(sizeof(usuario));
    }
    free(u); //libera o espaço alocado para o último usuário, que não foi adicionado ao vetor
    fclose(arquivo); 
}
 
void saldo(lista *Lista, int indice_logado) { //função que exibe o saldo do usuário logado.
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
    getchar(); //limpa o buffer
    getchar();
    return;
}