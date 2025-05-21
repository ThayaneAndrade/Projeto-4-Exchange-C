#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "funcoes.h"

void mostrar_cotacao(cryptomoeda *bitcoin, cryptomoeda *ethereum, cryptomoeda *ripple) {
    printf("\n\n----- Cotação Atual -----\n");
    printf("Bitcoin (BTC): %.2f BRL\n", bitcoin->valor);
    printf("Ethereum (ETH): %.2f BRL\n", ethereum->valor);
    printf("Ripple (XRP): %.2f BRL\n", ripple->valor);
    printf("\nPressione ENTER para continuar\n");
    getchar();
    getchar();
}

void atualizar_cotacao(cryptomoeda *bitcoin, cryptomoeda *ethereum, cryptomoeda *ripple) {
    float dado = (rand() % 2);
    if (dado == 0) {
        bitcoin->valor += bitcoin->valor * 0.05;
        ethereum->valor += ethereum->valor * 0.05;
        ripple->valor += ripple->valor * 0.05;
        printf("Cotação atualizada com sucesso!\n");
        mostrar_cotacao(bitcoin, ethereum, ripple);
    } else if (dado == 1) {
        bitcoin->valor -= bitcoin->valor * 0.05;
        ethereum->valor -= ethereum->valor * 0.05;
        ripple->valor -= ripple->valor * 0.05;
        printf("Cotação atualizada com sucesso!\n");
        mostrar_cotacao(bitcoin, ethereum, ripple);
}
}


void arquivar_cryptos(cryptomoeda *bitcoin, cryptomoeda *ethereum, cryptomoeda *ripple) {
    FILE *arquivo = fopen("cryptos.bin", "wb");
    fwrite(bitcoin, sizeof(cryptomoeda), 1, arquivo);
    fwrite(ethereum, sizeof(cryptomoeda), 1, arquivo);
    fwrite(ripple, sizeof(cryptomoeda), 1, arquivo);

    fclose(arquivo);
}

void carregar_cryptos(cryptomoeda *bitcoin, cryptomoeda *ethereum, cryptomoeda *ripple) {
    FILE *arquivo = fopen("cryptos.bin", "rb");
    if(arquivo == NULL) {
        return;
    }
    fread(bitcoin, sizeof(cryptomoeda), 1, arquivo);
    fread(ethereum, sizeof(cryptomoeda), 1, arquivo);
    fread(ripple, sizeof(cryptomoeda), 1, arquivo);
    fclose(arquivo);
}

void compra_crypto(cryptomoeda *bitcoin, cryptomoeda *ethereum, cryptomoeda *ripple, lista *Lista, int indice_logado) {
    if (solicita_senha(*Lista, indice_logado) == 0) {
        return;
    }
    printf("\nTaxas atuais: ");
    mostrar_cotacao(bitcoin, ethereum, ripple);
    printf("\n----- Compra de Criptomoedas -----\n");
    printf("1. Comprar Bitcoin (BTC)\n");
    printf("2. Comprar Ethereum (ETH)\n");
    printf("3. Comprar Ripple (XRP)\n");
    printf("4. Voltar ao menu principal\n");
    int opcao = userinput(4);

    switch (opcao) {
        case 1:
            //Lógica para comprar Bitcoin
            printf("Digite quantos Reais deseja investir em Bitcoin: ");
            float valor = uservalor();
            float valor_com_taxa = valor + (valor * bitcoin->taxa_compra);
            if (valor_com_taxa > Lista->vetor[indice_logado]->saldo) {
                printf("Saldo insuficiente para realizar a compra.\n");
                return;
            }
            double bitcoin_comprada = valor / bitcoin->valor;
            printf("Você está prestes a comprar %.5f BTC por %.2f BRL. Digite '1' para continuar ou '2' para cancelar.\n", bitcoin_comprada, valor_com_taxa);
            int confirmacao = userinput(2);
            if (confirmacao != 1) {
                printf("Compra cancelada.\n");
                return;
            }        
            Lista->vetor[indice_logado]->btc += bitcoin_comprada;
            Lista->vetor[indice_logado]->saldo -= valor_com_taxa;
            printf("Compra realizada com sucesso! Você agora possui %.5f BTC.\n", Lista->vetor[indice_logado]->btc);
            printf("Seu saldo restante é: %.2f BRL\n", Lista->vetor[indice_logado]->saldo);
            registra_transacao(Lista, indice_logado, 'C', valor_com_taxa, bitcoin->taxa_compra, "BTC", bitcoin_comprada); 
            salvar_extrato_arquivo(Lista, indice_logado); //salva o extrato em arquivo
            break;
        case 2:
            // Lógica para comprar Ethereum
            printf("Digite quantos Reais deseja investir em Ethereum: ");
            float valor_eth;
            scanf("%f", &valor_eth);
            if (valor_eth <= 0) {
                printf("Valor inválido.\n");
                return;
            }
            float valor_com_taxa_eth = valor_eth + (valor_eth * ethereum->taxa_compra);
            if (valor_com_taxa_eth > Lista->vetor[indice_logado]->saldo) {
                printf("Saldo insuficiente para realizar a compra.\n");
                return;
            }
            double ethereum_comprada = valor_eth / ethereum->valor;
            printf("Você está prestes a comprar %.3f ETH por %.2f BRL. Digite '1' para continuar ou '2' para cancelar.\n", ethereum_comprada, valor_com_taxa_eth);
            confirmacao = userinput(2);
            if (confirmacao != 1) {
                printf("Compra cancelada.\n");
                return;
            }
            Lista->vetor[indice_logado]->eth += ethereum_comprada;
            Lista->vetor[indice_logado]->saldo -= valor_com_taxa_eth;
            printf("Compra realizada com sucesso! Você agora possui %.3f ETH.\n", Lista->vetor[indice_logado]->eth);
            printf("Seu saldo restante é: %.2f BRL\n", Lista->vetor[indice_logado]->saldo);
            registra_transacao(Lista, indice_logado, 'C', valor_com_taxa_eth, ethereum->taxa_compra, "ETH", ethereum_comprada);
            salvar_extrato_arquivo(Lista, indice_logado); //salva o extrato em arquivo
            break;
        case 3:
            // Lógica para comprar Ripple
            printf("Digite quantos Reais deseja investir em Ripple: ");
            float valor_xrp;
            scanf("%f", &valor_xrp);
            if (valor_xrp <= 0) {
                printf("Valor inválido.\n");
                return;
            }
            float valor_com_taxa_xrp = valor_xrp + (valor_xrp * ripple->taxa_compra);
            if (valor_com_taxa_xrp > Lista->vetor[indice_logado]->saldo) {
                printf("Saldo insuficiente para realizar a compra.\n");
                return;
            }
            double ripple_comprada = valor_xrp / ripple->valor;
            printf("Você está prestes a comprar %.2f XRP por %.2f BRL. Digite '1' para continuar ou '2' para cancelar.\n", ripple_comprada, valor_com_taxa_xrp);
            confirmacao = userinput(2);
            if (confirmacao != 1) {
                printf("Compra cancelada.\n");
                return;
            }
            Lista->vetor[indice_logado]->xrp += ripple_comprada;
            Lista->vetor[indice_logado]->saldo -= valor_com_taxa_xrp;
            printf("Compra realizada com sucesso! Você agora possui %.2f XRP.\n", Lista->vetor[indice_logado]->xrp);
            printf("Seu saldo restante é: %.2f BRL\n", Lista->vetor[indice_logado]->saldo);
            registra_transacao(Lista, indice_logado, 'C', valor_com_taxa_xrp, ripple->taxa_compra, "XRP", ripple_comprada);
            salvar_extrato_arquivo(Lista, indice_logado); //salva o extrato em arquivo
            break;
        case 4:
            return;
        default:
            printf("Opção inválida.\n");
            break;
    }
}

void vender_crypto(cryptomoeda *bitcoin, cryptomoeda *ethereum, cryptomoeda *ripple, lista *Lista, int indice_logado){
    if (solicita_senha(*Lista, indice_logado) == 0) {
        return;
    }
    printf("\nTaxas atuais: ");
    mostrar_cotacao(bitcoin, ethereum, ripple);
    printf("\n----- Venda de Criptomoedas -----\n");
    printf("1. Vender Bitcoin (BTC)\n");
    printf("2. Vender Ethereum (ETH)\n");
    printf("3. Vender Ripple (XRP)\n");
    printf("4. Voltar ao menu principal\n");
    int opcao = userinput(4);
    int confirmacao;
    switch (opcao) {
        case 1:
            // Lógica para vender Bitcoin
            printf("Você possui %.5f BTC.\n", Lista->vetor[indice_logado]->btc); //mostra quantos da crypto o usuário tem
            printf("Digite quantos BTC deseja vender"); 
            double btc_venda = uservalor(); //recebe a quantidade a ser vendida
            if (btc_venda > Lista->vetor[indice_logado]->btc) {
                printf("Saldo insuficiente.\n"); //verifica se o usuário tem saldo suficiente
                return;
            }
            double valor_btc = btc_venda * bitcoin->valor;
            double valor_com_taxa_btc = valor_btc - (valor_btc * bitcoin->taxa_venda);
            printf("Você está prestes a vender %.5f BTC por %.2f BRL. Digite '1' para continuar ou '2' para cancelar.\n", btc_venda, valor_com_taxa_btc);
            confirmacao = userinput(2);
            if (confirmacao != 1) {
                printf("Venda cancelada.\n");
                return;
            }
            Lista->vetor[indice_logado]->btc -= btc_venda;
            Lista->vetor[indice_logado]->saldo += valor_com_taxa_btc;
            printf("Venda realizada com sucesso! Você agora possui %.5f BTC.\n", Lista->vetor[indice_logado]->btc);
            printf("Seu saldo atualizado é: %.2f BRL\n", Lista->vetor[indice_logado]->saldo);
            registra_transacao(Lista, indice_logado, 'V', valor_com_taxa_btc, bitcoin->taxa_venda, "BTC", btc_venda);
            salvar_extrato_arquivo(Lista, indice_logado); //salva o extrato em arquivo
            break;
        case 2:
            //lógica para vender ethereum
            printf("Você possui %.3f ETH.\n", Lista->vetor[indice_logado]->eth);
            printf("Digite quantos ETH deseja vender: ");
            double eth_venda = uservalor();
            if (eth_venda > Lista->vetor[indice_logado]->eth) {
                printf("Saldo insuficiente.\n");
                return;
            }
            double valor_eth = eth_venda * ethereum->valor;
            double valor_com_taxa_eth = valor_eth - (valor_eth * ethereum->taxa_venda);
            printf("Você está prestes a vender %.5f ETH por %.2f BRL. Digite '1' para continuar ou '2' para cancelar.\n", eth_venda, valor_com_taxa_eth);
            confirmacao = userinput(1);
            if (confirmacao != 1) {
                printf("Venda cancelada.\n");
                return;
            }
            Lista->vetor[indice_logado]->eth -= eth_venda;
            Lista->vetor[indice_logado]->saldo += valor_com_taxa_eth;
            printf("Venda realizada com sucesso! Você agora possui %.5f ETH.\n", Lista->vetor[indice_logado]->eth);
            printf("Seu saldo atualizado é: %.2f BRL\n", Lista->vetor[indice_logado]->saldo);
            registra_transacao(Lista, indice_logado, 'V', valor_com_taxa_eth, ethereum->taxa_venda, "ETH", eth_venda);
            break;
        case 3:
            //lógica para vender ripple
            printf("Você possui %.2f XRP.\n", Lista->vetor[indice_logado]->xrp);
            printf("Digite quantos XRP deseja vender: ");
            double xrp_venda = uservalor();
            if (xrp_venda > Lista->vetor[indice_logado]->xrp) {
                printf("Saldo insuficiente.\n");
                return;
            }
            double valor_xrp = xrp_venda * ripple->valor;
            double valor_com_taxa_xrp = valor_xrp - (valor_xrp * ripple->taxa_venda);
            printf("Você está prestes a vender %.5f XRP por %.2f BRL. Digite '1' para continuar ou '2' para cancelar.\n", xrp_venda, valor_com_taxa_xrp);
            confirmacao = userinput(1);
            if (confirmacao != 1) {
                printf("Venda cancelada.\n");
                return;
            }
            Lista->vetor[indice_logado]->xrp -= xrp_venda;
            Lista->vetor[indice_logado]->saldo += valor_com_taxa_xrp;
            printf("Venda realizada com sucesso! Você agora possui %.5f XRP.\n", Lista->vetor[indice_logado]->xrp);
            printf("Seu saldo atualizado é: %.2f BRL\n", Lista->vetor[indice_logado]->saldo);
            registra_transacao(Lista, indice_logado, 'V', valor_com_taxa_xrp, ripple->taxa_venda, "XRP", xrp_venda);
            salvar_extrato_arquivo(Lista, indice_logado); //salva o extrato em arquivo
        case 4:
            return;
        default:
            printf("Opção inválida.\n");
            break;
    }
}
