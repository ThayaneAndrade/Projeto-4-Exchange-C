#define funcoes_h
 
typedef struct usuario { //struct que define as características de cada usuário.
    char cpf[12];
    char nome[50];
    int senha;
    float saldo;
    float btc;
    float eth;
    float xrp;
 
}usuario;
 
typedef struct lista { //struct que será usada para organizar os usuários por "índices" através do qtd, além de armazenar os usuarios definidos em ponteiros.
    usuario *vetor[100];
    int qtd;
}lista;
 
void registrar(lista *Lista);

int login(lista *Lista);

void menuprincipal(lista *Lista, int *indice_logado);

int solicita_senha(lista Lista, int indice_logado);

int inserir_usuario(lista *Lista, usuario *user);

void debug_imprimir_lista(lista *l);

void carregar_usuarios(lista *Lista);

void saldo(lista *Lista, int indice_logado);

void deposito(lista *Lista, int indice_logado);

void arquivar_usuarios(lista *Lista, int indice_logado);
