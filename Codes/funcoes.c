#include <stdio.h>
#include "funcoes.h"
#include <string.h>
#include <stdlib.h>
#include <time.h>

 
void registrar(lista *Lista) { //função para registrar usuários, pede somente nome cpf e senha, os valores iniciais de moedas são 0.
    FILE *arquivo = fopen("usuarios.bin", "wb");
    printf("----- Cadastro -----\n");
    usuario *user = malloc(sizeof(usuario));
    user->qtdTransacoes = 0;
    printf("Digite seu nome: ");
    scanf("%s", user->nome);
    printf("Digite seu CPF (somente números): ");
    scanf("%s", user->cpf);
    //verifica se o CPF já existe
    for (int i = 0; i < Lista->qtd; i++) {
        if (strcmp(Lista->vetor[i]->cpf, user->cpf) == 0) {
            printf("CPF já cadastrado. Tente novamente.\n");
            free(user);
            fclose(arquivo);
            return;
        }
    }
    printf("Digite sua senha (somente números): ");
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
        int opcao = userinput(9);
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
            case 6:
                vender_crypto(bitcoin, ethereum, ripple, Lista, *indice_logado);
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
        printf("  BTC:   %.5f\n", l->vetor[i]->btc);
        printf("  ETH:   %.3f\n", l->vetor[i]->eth);
        printf("  XRP:   %.2f\n", l->vetor[i]->xrp);
        printf("\n");
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
            float bitcoin_comprada = valor / bitcoin->valor;
            printf("Você está prestes a comprar %.5f BTC por %.2f BRL. Pressione ENTER para continuar\n", bitcoin_comprada, valor_com_taxa);
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

void vender_crypto(cryptomoeda *bitcoin, cryptomoeda *ethereum, cryptomoeda *ripple, lista *Lista, int indice_logado){
    if (solicita_senha(*Lista, indice_logado) == 0) {
        return;
    }
    printf("\n----- Venda de Criptomoedas -----\n");
    printf("1. Vender Bitcoin (BTC)\n");
    printf("2. Vender Ethereum (ETH)\n");
    printf("3. Vender Ripple (XRP)\n");
    printf("4. Voltar ao menu principal\n");
    int opcao = userinput(4);
    switch (opcao) {
        case 1:
            // Lógica para vender Bitcoin
            printf("Digite quantos BTC deseja vender");
            float btc_venda = uservalor();
            if (btc_venda > Lista->vetor[indice_logado]->btc) {
                printf("Quantidade inválida.\n");
                return;
            }
            float valor_btc = btc_venda * bitcoin->valor;
            float valor_com_taxa_btc = valor_btc - (valor_btc * bitcoin->taxa_venda);
            Lista->vetor[indice_logado]->btc -= btc_venda;
            Lista->vetor[indice_logado]->saldo += valor_com_taxa_btc;
            printf("Venda realizada com sucesso! Você agora possui %.5f BTC.\n", Lista->vetor[indice_logado]->btc);
            printf("Seu saldo atualizado é: %.2f BRL\n", Lista->vetor[indice_logado]->saldo);
            break;
        case 2:
            // Lógica para vender Ethereum
            printf("Digite quantos ETH deseja vender: ");
            float eth_venda = uservalor();
            if (eth_venda > Lista->vetor[indice_logado]->eth) {
                printf("Quantidade inválida.\n");
                return;
            }
            float valor_eth = eth_venda * ethereum->valor;
            float valor_com_taxa_eth = valor_eth - (valor_eth * ethereum->taxa_venda);
            Lista->vetor[indice_logado]->eth -= eth_venda;
            Lista->vetor[indice_logado]->saldo += valor_com_taxa_eth;
            printf("Venda realizada com sucesso! Você agora possui %.3f ETH.\n", Lista->vetor[indice_logado]->eth);
            printf("Seu saldo atualizado é: %.2f BRL\n", Lista->vetor[indice_logado]->saldo);
            break;
        case 3:
            //lógica para vender ripple
            printf("Digite quantos XRP deseja vender: ");
            float xrp_venda = uservalor();
            if (xrp_venda > Lista->vetor[indice_logado]->xrp) {
                printf("Quantidade inválida.\n");
                return;
            }
            float valor_xrp = xrp_venda * ripple->valor;
            float valor_com_taxa_xrp = valor_xrp - (valor_xrp * ripple->taxa_venda);
            Lista->vetor[indice_logado]->xrp -= xrp_venda;
            Lista->vetor[indice_logado]->saldo += valor_com_taxa_xrp;
            printf("Venda realizada com sucesso! Você agora possui %.2f XRP.\n", Lista->vetor[indice_logado]->xrp);
            printf("Seu saldo atualizado é: %.2f BRL\n", Lista->vetor[indice_logado]->saldo);
            break;
        case 4:
            return;
        default:
            printf("Opção inválida.\n");
            break;
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

int uservalor(){
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