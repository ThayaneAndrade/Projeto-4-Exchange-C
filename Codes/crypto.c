#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "funcoes.h"

void mostrar_cotacao(Coins *cc) {
    printf("\n\n----- Cotação Atual -----\n");
    for (int i = 0; i < cc->qtd; i++) {
        cryptomoeda *c = cc->vetor[i];                                         //pega ponteiro da crypto
        printf("Nome: %s\n",   c->nome);                                       //imprime nome
        printf("Valor: %.2f BRL\n", c->valor);                                 //imprime valor
        printf("Taxa de Compra: %.2f%%\n", c->taxa_compra * 100);              //imprime taxa compra
        printf("Taxa de Venda:  %.2f%%\n", c->taxa_venda  * 100);              //imprime taxa venda
        printf("-------------------------\n");
    }
    getchar(); getchar();                                                     //espera ENTER
}

void atualizar_cotacao(Coins *cc) {
    int direcao = rand() % 2;                                                 //0=alta,1=baixa
    for (int i = 0; i < cc->qtd; i++) {
        cryptomoeda *c = cc->vetor[i];                                        //ponteiro para cada crypto
        if (direcao == 0) c->valor *= 1.05f;                                  //aumenta 5%
        else             c->valor *= 0.95f;                                  //reduz 5%
    }
    printf("Cotação atualizada com sucesso!\n");
    mostrar_cotacao(cc);                                                      // mostra nova cotação
}

void arquivar_cryptos(Coins *cc) {
    FILE *f = fopen("cryptos.bin", "wb");                                     //abre para escrita binária
    if (!f) return;                                                           //falha ao abrir?
    fwrite(&cc->qtd, sizeof(int), 1, f);                                      //grava quantidade
    for (int i = 0; i < cc->qtd; i++) {
        fwrite(cc->vetor[i], sizeof(cryptomoeda), 1, f);                      //grava cada struct
    }
    fclose(f);                                                                //fecha arquivo
}

void carregar_cryptos(Coins *cc) {
    FILE *f = fopen("cryptos.bin", "rb");                                     //abre para leitura binária
    if (!f) { cc->qtd = 0; return;}                                           //se nao existe, sem cryptos
    fread(&cc->qtd, sizeof(int), 1, f);                                       //lê quantidade
    for (int i = 0; i < cc->qtd; i++) {
        cc->vetor[i] = malloc(sizeof(cryptomoeda));                           //aloca nova struct
        fread(cc->vetor[i], sizeof(cryptomoeda), 1, f);                       //lê dados no ponteiro
    }
    fclose(f);                                                                //fecha arquivo
}

void compra_crypto(lista *Lista, int indice_logado, Coins *cc) {
    if (solicita_senha(*Lista, indice_logado) == 0) {
        return;
    }
    printf("\nTaxas atuais: ");
    mostrar_cotacao(cc);
    printf("\n----- Compra de Criptomoedas -----\n");
    for (int i = 0; i < cc->qtd; i++) {
        printf("%d. Comprar %s\n", i + 1, cc->vetor[i]->nome);
    }
    int opcao = userinput(cc->qtd);
    double valor_compra;
    double valor_com_taxa;
    double quantidade;
    printf("Digite a quantidade de %s que deseja comprar: ", cc->vetor[opcao - 1]->nome);
    quantidade = uservalor();
    valor_compra = quantidade * cc->vetor[opcao - 1]->valor;
    valor_com_taxa = valor_compra + (valor_compra * cc->vetor[opcao - 1]->taxa_compra);
    if (valor_com_taxa > Lista->vetor[indice_logado]->saldo) {
        printf("Saldo insuficiente para realizar a compra.\n");
        return;
    }
    printf("Você está prestes a comprar %.5f %s por %.2f BRL. Digite '1' para continuar ou '2' para cancelar.\n", quantidade, cc->vetor[opcao - 1]->nome, valor_com_taxa);
    int confirmacao = userinput(2);
    if (confirmacao != 1) {
        printf("Compra cancelada.\n");
        return;
    }else{
        Lista->vetor[indice_logado]->saldo -= valor_com_taxa;
        Lista->vetor[indice_logado]->btc += quantidade;
        Lista->vetor[indice_logado]->transacoes[Lista->vetor[indice_logado]->qtdTransacoes].valor = valor_compra;
        Lista->vetor[indice_logado]->transacoes[Lista->vetor[indice_logado]->qtdTransacoes].taxa = cc->vetor[opcao - 1]->taxa_compra;
        strcpy(Lista->vetor[indice_logado]->transacoes[Lista->vetor[indice_logado]->qtdTransacoes].crypto, cc->vetor[opcao - 1]->nome);
        Lista->vetor[indice_logado]->transacoes[Lista->vetor[indice_logado]->qtdTransacoes].quantidade = quantidade;
        Lista->vetor[indice_logado]->qtdTransacoes++;
        printf("Compra confirmada.\n");
        printf("Você comprou %.5f %s por %.2f BRL.\n", quantidade, cc->vetor[opcao - 1]->nome, valor_com_taxa);
        printf("Taxa de compra: %.2f%%\n", cc->vetor[opcao - 1]->taxa_compra * 100);
        printf("Pressione ENTER para continuar\n");
        getchar();
        getchar();
        return;
    }
}

void vender_crypto(lista *Lista, int indice_logado, Coins *cc) {
    if (cc->qtd == 0) {
        printf("Nenhuma criptomoeda disponível para venda.\n");
        return;
    }
    if (solicita_senha(*Lista, indice_logado) == 0) {
        return;
    }
    printf("\nTaxas atuais: ");
    mostrar_cotacao(cc);
    printf("\n----- Venda de Criptomoedas -----\n");
    for (int i = 0; i < cc->qtd; i++) {
        printf("%d. Vender %s\n", i + 1, cc->vetor[i]->nome);
    }
    int opcao = userinput(cc->qtd);
    int confirmacao;
    double valor_venda;
    double valor_venda_com_taxa;
    double quantidade;
    printf("Digite a quantidade de %s que deseja vender: ", cc->vetor[opcao - 1]->nome);
    quantidade = uservalor();
    valor_venda = quantidade * cc->vetor[opcao - 1]->valor;
    valor_venda_com_taxa = valor_venda - (valor_venda * cc->vetor[opcao - 1]->taxa_venda);
    printf("Você está prestes a vender %.5f %s por %.2f BRL. Digite '1' para continuar ou '2' para cancelar.\n", quantidade, cc->vetor[opcao - 1]->nome, valor_venda_com_taxa);
    confirmacao = userinput(2);
    if (confirmacao != 1) {
        printf("Venda cancelada.\n");
        return;
    }else{
        Lista->vetor[indice_logado]->saldo += valor_venda_com_taxa;
        Lista->vetor[indice_logado]->btc -= quantidade;
        Lista->vetor[indice_logado]->transacoes[Lista->vetor[indice_logado]->qtdTransacoes].valor = valor_venda;
        Lista->vetor[indice_logado]->transacoes[Lista->vetor[indice_logado]->qtdTransacoes].taxa = cc->vetor[opcao - 1]->taxa_venda;
        strcpy(Lista->vetor[indice_logado]->transacoes[Lista->vetor[indice_logado]->qtdTransacoes].crypto, cc->vetor[opcao - 1]->nome);
        Lista->vetor[indice_logado]->transacoes[Lista->vetor[indice_logado]->qtdTransacoes].quantidade = quantidade;
        Lista->vetor[indice_logado]->qtdTransacoes++;
        printf("\nVenda confirmada.\n");
        printf("Você vendeu %.5f %s por %.2f BRL.\n", quantidade, cc->vetor[opcao - 1]->nome, valor_venda_com_taxa);
        printf("Taxa de venda: %.2f%%\n", cc->vetor[opcao - 1]->taxa_venda * 100);
        printf("Pressione ENTER para continuar\n");
        getchar();
        getchar();
    }
}
