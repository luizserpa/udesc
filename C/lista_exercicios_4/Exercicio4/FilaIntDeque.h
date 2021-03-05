#define ERRO_FILA_CHEIA -1
#define ERRO_FILA_VAZIA -2

typedef struct
{
    int *dados;
    int inicio;
    int capacidade;
    int qntOcupada;
}FilaInt;

void inicializaFila(FilaInt *f, int capacidade);
void desalocarPilha(FilaInt *f);
int filaCheia(FilaInt f);
int filaVazia(FilaInt f);
int inserirInicioFila (FilaInt *f, int info);
int removerInicioFila (FilaInt *f, int *info);
int inserirFimFila (FilaInt *f, int info);
int removerFimFila (FilaInt *f, int *info);
int leInicio (FilaInt f, int *info);
void imprimiFila(FilaInt f);