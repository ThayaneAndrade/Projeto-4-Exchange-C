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
    float saldo;
    double crypto[10];
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

typedef struct {
    cryptomoeda *vetor[10];  //ponteiro para array de cryptomoedas
    int qtd;             //quantas cryptos estao ativas
} Coins;
 
void registrar(lista *Lista);
int login(lista *Lista);
void menuprincipal(lista *Lista, int *indice_logado, Coins *cc);
int solicita_senha(lista Lista, int indice_logado);
int inserir_usuario(lista *Lista, usuario *user);
void debug_imprimir_lista(lista *Lista);
void carregar_usuarios(lista *Lista);
void saldo(lista *Lista, int indice_logado, Coins *cc);
void deposito(lista *Lista, int indice_logado);
void saque(lista *Lista, int indice_logado);
void arquivar_usuarios(lista *Lista);
void mostrar_cotacao(Coins *cc);
void atualizar_cotacao(Coins *cc);
void arquivar_cryptos(Coins *cc);
void carregar_cryptos(Coins *cc);
void compra_crypto(lista *Lista, int indice_logado, Coins *cc);
void vender_crypto(lista *Lista, int indice_logado, Coins *cc);
void mostrar_cotacao(Coins *cc);
int userinput(int max);
double uservalor();
void registra_transacao(lista *Lista, int indice_logado, char tipo, double valor, double taxa, const char *crypto, double quantidade);
void extrato(lista *Lista, int indice_logado);
void salvar_extrato_arquivo(lista *Lista, int indice_logado);
void verificaadmin(lista *Lista);
int loginadmin(lista *Lista, usuario *adm);
void menuadmin(lista *Lista, Coins *cc);
void excluiruser(lista *Lista);
void criarcrypto(Coins *cc);
void mostrar_cryptos(Coins *cc);
void excluircrypto(Coins *cc);
void consultarusuario(lista *Lista);
void consultarextrato(lista *Lista, int indice_logado);

#endif  // Fim do arquivo de cabeçalho