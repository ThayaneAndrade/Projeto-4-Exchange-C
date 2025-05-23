#ifndef funcoes_h
#define funcoes_h


typedef struct {
    int dia, mes, ano;
    int hora, minuto, segundo;
}DataHora;

typedef struct {
    DataHora dh;
    char tipo;       //'C' compra, 'V' venda, 'D' deposito e 'S' saque
    double valor;
    double taxa;
    char crypto[5];
    double quantidade;
}Transacao;

typedef struct {
    char cpf[12];
    char nome[50];
    int  senha;
    double saldo;
    double btc, eth, xrp;
    Transacao transacoes[100];
    int qtdTransacoes;
}usuario;

 
typedef struct lista {
    usuario *vetor[100];
    int qtd;
}lista;

typedef struct cryptomoeda {
    char nome[5];
    float valor;
    float taxa_compra;
    float taxa_venda;
}cryptomoeda;
 
void registrar(lista *Lista);
int login(lista *Lista);
void menuprincipal(lista *Lista, int *indice_logado, cryptomoeda *bitcoin, cryptomoeda *ethereum, cryptomoeda *ripple);
int solicita_senha(lista Lista, int indice_logado);
int inserir_usuario(lista *Lista, usuario *user);
void debug_imprimir_lista(lista *l);
void carregar_usuarios(lista *Lista);
void saldo(lista *Lista, int indice_logado);
void deposito(lista *Lista, int indice_logado);
void saque(lista *Lista, int indice_logado);
void arquivar_usuarios(lista *Lista, int indice_logado);
void mostrar_cotacao(cryptomoeda *bitcoin, cryptomoeda *ethereum, cryptomoeda *ripple);
void atualizar_cotacao(cryptomoeda *bitcoin, cryptomoeda *ethereum, cryptomoeda *ripple);
void arquivar_cryptos(cryptomoeda *bitcoin, cryptomoeda *ethereum, cryptomoeda *ripple);
void carregar_cryptos(cryptomoeda *bitcoin, cryptomoeda *ethereum, cryptomoeda *ripple);
void compra_crypto(cryptomoeda *bitcoin, cryptomoeda *ethereum, cryptomoeda *ripple, lista *Lista, int indice_logado);
void vender_crypto(cryptomoeda *bitcoin, cryptomoeda *ethereum, cryptomoeda *ripple, lista *Lista, int indice_logado);
int userinput(int max);
double uservalor();
void registra_transacao(lista *Lista, int indice_logado, char tipo, double valor, double taxa, const char *crypto, double quantidade);
void extrato(lista *Lista, int indice_logado);
void salvar_extrato_arquivo(lista *Lista, int indice_logado);
void verificaadmin(lista *Lista);
int loginadmin(lista *Lista, usuario *adm);
void menuadmin(lista *Lista);

#endif  // Fim do arquivo de cabeçalho