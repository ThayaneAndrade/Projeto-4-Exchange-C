#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "funcoes.h"

void deposito(lista *Lista, int indice_logado) {
    if (solicita_senha(*Lista, indice_logado) == 0) {
        return;
    }
    printf("\nDigite o valor a ser depositado: ");
    float valor = uservalor(); 
    if (valor <= 0) {
        printf("Valor inválido.\n");
        return;
    }
    Lista->vetor[indice_logado]->saldo += valor;
    printf("Depósito realizado com sucesso! Seu novo saldo é: %.2f\n", Lista->vetor[indice_logado]->saldo);
    registra_transacao(Lista, indice_logado, 'D', valor, 0.0, "" , 0.0); // Adiciona a transação de depósito;
    salvar_extrato_arquivo(Lista, indice_logado); //salva o extrato em arquivo
}
 
void saque(lista *Lista, int indice_logado) {
    if (solicita_senha(*Lista, indice_logado) == 0) {
        return;
    }
    printf("\nDigite o valor a ser sacado: ");
    float valor = uservalor();
    if (valor <= 0) {
        printf("\nValor inválido.\n");
        printf("Pressione ENTER para continuar\n");
        getchar();
        getchar();
        return;
    } else if (valor > Lista->vetor[indice_logado]->saldo) {
        printf("\nSaldo Insuficiente! \n");
        printf("Pressione ENTER para continuar\n");
        getchar();
        getchar();
        return;
    } else {
        Lista->vetor[indice_logado]->saldo -= valor;
        printf("Saque realizado com sucesso! Seu novo saldo é: %.2f\n", Lista->vetor[indice_logado]->saldo);
        registra_transacao(Lista, indice_logado, 'S', valor, 0.0, "", 0.0); //adiciona a transação de saque
        salvar_extrato_arquivo(Lista, indice_logado); //salva o extrato em arquivo
    }
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

void registra_transacao(lista *Lista, int indice_logado, 
    char tipo, //tipo da transação, V = venda, C = compra, D = deposito, S = saque
    double valor, //valor da transação em BRL
    double taxa,  //taxa da transação (se houver)
    const char *crypto, //nome da cryptomoeda
    double quantidade) { //quantidade de cryptomoedas compradas

    time_t now = time(NULL);
    struct tm *tm = localtime(&now);
    usuario *u = Lista->vetor[indice_logado];
    if (u->qtdTransacoes < 100) {
        Transacao *t = &u->transacoes[u->qtdTransacoes++];
        t->dh.dia    = tm->tm_mday;
        t->dh.mes    = tm->tm_mon + 1;
        t->dh.ano    = tm->tm_year + 1900;
        t->dh.hora   = tm->tm_hour;
        t->dh.minuto = tm->tm_min;
        t->dh.segundo= tm->tm_sec;
        t->tipo     = tipo;
        t->valor    = valor;
        t->taxa     = taxa;
        strncpy(t->crypto, crypto, 4);
        t->crypto[4] = '\0';
        t->quantidade = quantidade;
    } else {
        printf("Limite de transacoes atingido!\n");
    }
}

void extrato(lista *Lista, int indice_logado) { //função para mostrar o extrato do usuário logado
    if (solicita_senha(*Lista, indice_logado) == 0) {
        return;
    }
    usuario *u = Lista->vetor[indice_logado]; 
    char caminhoArquivo[128]; //declara o caminho do arquivo
    sprintf(caminhoArquivo, "extratos/extrato_%s.txt", u->cpf); //cria o caminho do arquivo de extrato do usuário logado
    FILE *fp = fopen(caminhoArquivo, "r");
    if (!fp) {
        printf("Arquivo de extrato nao encontrado.\n");
        printf("Pressione ENTER para continuar...");
        getchar();
        getchar();
        return;
    }
    printf("\n---------- EXTRATO ----------\n\n");
    char linha[256];
    while (fgets(linha, sizeof(linha), fp)) {
        printf("%s", linha);
    }
    fclose(fp);
    printf("\nPressione ENTER para continuar...");
    getchar();
    getchar();
}

void salvar_extrato_arquivo(lista *Lista, int indice_logado) {
    usuario *u = Lista->vetor[indice_logado];
    char caminhoArquivo[128];
    sprintf(caminhoArquivo, "extratos/extrato_%s.txt", u->cpf);

    FILE *fp = fopen(caminhoArquivo, "w");
    if (!fp) {
        printf("Erro ao abrir arquivo para salvar extrato.\n");
        return;
    }

    fprintf(fp,
        "===== EXTRATO DE %s =====\n"
        "CPF   : %s\n"
        "Saldo : %.2f BRL\n"
        "BTC   : %.8f\n"
        "ETH   : %.8f\n"
        "XRP   : %.8f\n\n"
        "---- TRANSACOES (%d) ----\n",
        u->nome, u->cpf, u->saldo,
        u->btc, u->eth, u->xrp,
        u->qtdTransacoes
    );

    for (int i = 0; i < u->qtdTransacoes; i++) {
        Transacao *t = &u->transacoes[i];
        fprintf(fp,
            "%02d/%02d/%04d %02d:%02d:%02d | %c | valor: %.2f | taxa: %.4f | crypto: %s | qtd: %.8f\n",
            t->dh.dia, t->dh.mes, t->dh.ano,
            t->dh.hora, t->dh.minuto, t->dh.segundo,
            t->tipo, t->valor, t->taxa,
            (t->crypto[0] != '\0') ? t->crypto : "-",
            t->quantidade
        );
    }

    fclose(fp);
}