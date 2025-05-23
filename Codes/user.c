#include <stdio.h>
#include "funcoes.h"
#include <string.h>
#include <stdlib.h>
#include <time.h>



void registrar(lista *Lista) { //função para registrar usuários, pede somente nome cpf e senha, os valores iniciais de moedas são 0.
    FILE *arquivo = fopen("usuarios.bin", "ab");
    printf("----- Cadastro -----\n");
    usuario *user = malloc(sizeof(usuario));
    user->qtdTransacoes = 0;
    printf("Digite seu nome: ");
    scanf("%s", user->nome);
    printf("Digite seu CPF (somente números):");
    scanf("%s", user->cpf);
    if (strlen(user->cpf) != 11) {
        printf("CPF inválido. Deve conter 11 dígitos.\n");
        free(user);
        fclose(arquivo);
        return;
    }
    //verifica se o CPF já existe
    for (int i = 0; i < Lista->qtd; i++) {
        if (strcmp(Lista->vetor[i]->cpf, user->cpf) == 0) {
            printf("CPF já cadastrado. Tente novamente.\n");
            free(user);
            fclose(arquivo);
            return;
        }
    }
    printf("Digite sua senha (somente números)");
    user->senha = userinput(99999);
    printf("Cadastro realizado com sucesso!\n");
    Lista->vetor[Lista->qtd] = user;
    Lista->qtd++;
    fwrite(user, sizeof(usuario), 1, arquivo);
    fclose(arquivo);
    printf("Pressione ENTER para continuar\n");
    getchar();
    getchar();
}

int login(lista *Lista) {
    char cpfDigitado[12];
    int senhaDigitada;
    printf("Digite seu CPF: ");
    scanf("%s", cpfDigitado);
    if (strlen(cpfDigitado) != 11) {
        printf("CPF inválido. Deve conter 11 dígitos.\n");
        return -1;
    }
    printf("Digite sua senha: ");
    senhaDigitada = userinput(99999);

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

int inserir_usuario(lista *Lista, usuario *user) {
    if (Lista->qtd == 100) {
        printf("Lista atingiu a capacidade maxima!\n");
        return 0;
    }
    Lista->vetor[Lista->qtd] = user;
    Lista->qtd++;
    return 0;
}

int solicita_senha(lista Lista, int indice_logado) {
    printf("\nDigite sua senha: ");
    int senha = userinput(99999);
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

void carregar_usuarios(lista *Lista) {
    FILE *arquivo = fopen("usuarios.bin", "rb");
    if (arquivo == NULL) {
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

double uservalor(){
    while(1){
        printf("\nValor: ");
        double valor;
        if(scanf("%lf",&valor)!=1){
            printf("digite apenas numeros.");
            while((valor = getchar()) != '\n' && valor != EOF);
        }
        else if(valor<=0) {
            printf("valor invalido.");
        }else{
            return valor;
        }
    }
}

int userinput(int maxopcoes){ //pega a entrada do jogador e verifica se é válida
    int escolha;
    int resultado;

    while (1) {
        printf("\nEntrada: ");
        resultado = scanf("%d", &escolha);  //tenta ler um número inteiro

        //verifica se o input não é um número
        if (resultado != 1) {
            while (getchar() != '\n');  //limpa o buffer
            printf("\nEntrada inválida. Por favor, digite um número.\n");
        } else if (escolha < 1 || escolha > maxopcoes) {  //verifica se o número está fora do intervalo
            printf("\nEntrada Inválida. Digite um número entre 1 e %d.\n", maxopcoes);
        } else {
            return escolha;  //retorna a escolha válida
        }
    }
}
