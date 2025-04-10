#define funcoes_h


typedef struct usuario { //struct que define as características de cada usuário.
    char nome[50];
    int senha;
    float saldo;

}usuario;

typedef struct lista{ //struct que será usada para organizar os usuários por "índices" através do qtd, além de armazenar os usuarios definidos em ponteiros.
    usuario *vetor[100];
    int qtd;
}lista;

void registrar(lista *Lista);

int login(char *usuariologado, int *senhalogada);

void menuprincipal(char *usuariologado, int *senhalogada, int *logado);

int inserir_usuario(lista *Lista, usuario *user);

void debug_imprimir_lista(lista *l);

void carregar_usuarios(lista *Lista);