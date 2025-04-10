#define funcoes_h
 
typedef struct usuario {
    char cpf[12];
    char nome[50];
    int senha;
    float saldo;
    float btc;
    float eth;
    float xrp;
} usuario;
 
typedef struct lista {
    usuario *vetor[100];
    int qtd;
} lista;
 
void registrar(lista *Lista);
int login(lista *Lista);
void menuprincipal(lista *Lista, int *indice_logado);
int solicita_senha(lista Lista, int indice_logado);
int inserir_usuario(lista *Lista, usuario *user);
void debug_imprimir_lista(lista *l);
void carregar_usuarios(lista *Lista);
void saldo(lista *Lista, int indice_logado);
void deposito(lista *Lista, int indice_logado);
void saque(lista *Lista, int indice_logado);
void arquivar_usuarios(lista *Lista, int indice_logado);