#define funcoes_h


typedef struct usuario {
    char nome[50];
    int senha;

}usuario;

typedef struct lista{
    usuario *lista[100];
    int qtd;
}lista;

void registrar();

int login(char *usuariologado, int *senhalogada);

void menuprincipal(char *usuariologado, int *senhalogada, int *logado);
