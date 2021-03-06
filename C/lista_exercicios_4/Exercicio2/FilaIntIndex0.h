#define ERRO_FILA_CHEIA -1
#define ERRO_FILA_VAZIA -2

typedef struct
{
    int *dados;
    int inicio;
    int capacidade;
    int fim;
}FilaInt;

void inicializaFila(FilaInt *f, int capacidade);
void desalocarPilha(FilaInt *f);
int filaCheia(FilaInt f);
int filaVazia(FilaInt f);
int inserirDado (FilaInt *f, int info);
int removerDado (FilaInt *f, int *info);
int leInicio (FilaInt f, int *info);
void imprimiFila(FilaInt f);