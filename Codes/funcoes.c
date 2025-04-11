#include <stdio.h>
#include "funcoes.h"
#include <string.h>
#include <stdlib.h>
#include <time.h>

 
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
 
void menuprincipal(lista *Lista, int *indice_logado, cryptomoeda *bitcoin, cryptomoeda *ethereum, cryptomoeda *ripple){
    printf("\n-----Bem vindo(a) à CryptoSpy 2.0------\n");
    int opcao;
    carregar_cryptos(bitcoin, ethereum, ripple);
 
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
                saque(Lista, *indice_logado);
                break;
            case 3:
                saldo(Lista, *indice_logado);
                break;
            case 5:
                compra_crypto(bitcoin, ethereum, ripple, Lista, *indice_logado);
                break;
            case 7:
                mostrar_cotacao(bitcoin, ethereum, ripple);
                break;
            case 8:
                atualizar_cotacao(bitcoin, ethereum, ripple);
                break;
            case 9:
                arquivar_usuarios(Lista, *indice_logado);
                arquivar_cryptos(bitcoin, ethereum, ripple);
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
 
void saque(lista *Lista, int indice_logado) {
    if (solicita_senha(*Lista, indice_logado) == 0) {
        return;
    }
    float valor;
    printf("\nDigite o valor a ser sacado: ");
    scanf("%f", &valor);
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
    }
}

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
    printf("\n----- Compra de Criptomoedas -----\n");
    printf("1. Comprar Bitcoin (BTC)\n");
    printf("2. Comprar Ethereum (ETH)\n");
    printf("3. Comprar Ripple (XRP)\n");
    printf("4. Voltar ao menu principal\n");
    printf("\nEscolha uma opção: ");
    int opcao;
    scanf("%d", &opcao);

    switch (opcao) {
        case 1:
            //Lógica para comprar Bitcoin
            printf("Digite quantos Reais deseja investir em Bitcoin: ");
            float valor;
            scanf("%f", &valor);
            if (valor <= 0) {
                printf("Valor inválido.\n");
                return;
            }
            float valor_com_taxa = valor + (valor * bitcoin->taxa_compra);
            if (valor_com_taxa > Lista->vetor[indice_logado]->saldo) {
                printf("Saldo insuficiente para realizar a compra.\n");
                return;
            }
            float bitcoin_comprada = valor / bitcoin->valor;
            printf("Você está prestes a comprar %.5f BTC por %.2f BRL. Pressione ENTER para continuar\n", bitcoin_comprada, valor);
            getchar();
            getchar();         
            Lista->vetor[indice_logado]->btc += bitcoin_comprada;
            Lista->vetor[indice_logado]->saldo -= valor_com_taxa;
            printf("Compra realizada com sucesso! Você agora possui %.5f BTC.\n", Lista->vetor[indice_logado]->btc);
            printf("Seu saldo restante é: %.2f BRL\n", Lista->vetor[indice_logado]->saldo);
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
            float valor_com_taxa_eth = valor + (valor * ethereum->taxa_compra);
            if (valor_com_taxa_eth > Lista->vetor[indice_logado]->saldo) {
                printf("Saldo insuficiente para realizar a compra.\n");
                return;
            }
            float ethereum_comprada = valor_eth / ethereum->valor;
            printf("Você está prestes a comprar %.3f ETH por %.2f BRL. Pressione ENTER para continuar\n", ethereum_comprada, valor_eth);
            getchar();
            getchar();
            Lista->vetor[indice_logado]->eth += ethereum_comprada;
            Lista->vetor[indice_logado]->saldo -= valor_com_taxa_eth;
            printf("Compra realizada com sucesso! Você agora possui %.3f ETH.\n", Lista->vetor[indice_logado]->eth);
            printf("Seu saldo restante é: %.2f BRL\n", Lista->vetor[indice_logado]->saldo);
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
            float valor_com_taxa_xrp = valor + (valor * ripple->taxa_compra);
            if (valor_com_taxa_xrp > Lista->vetor[indice_logado]->saldo) {
                printf("Saldo insuficiente para realizar a compra.\n");
                return;
            }
            float ripple_comprada = valor_xrp / ripple->valor;
            printf("Você está prestes a comprar %.2f XRP por %.2f BRL. Pressione ENTER para continuar\n", ripple_comprada, valor_xrp);
            getchar();
            getchar();
            Lista->vetor[indice_logado]->xrp += ripple_comprada;
            Lista->vetor[indice_logado]->saldo -= valor_com_taxa_xrp;
            printf("Compra realizada com sucesso! Você agora possui %.2f XRP.\n", Lista->vetor[indice_logado]->xrp);
            printf("Seu saldo restante é: %.2f BRL\n", Lista->vetor[indice_logado]->saldo);
            break;
        case 4:
            return;
        default:
            printf("Opção inválida.\n");
            break;
    }
}