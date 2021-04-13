#include "Lista.h"

#define ERRO_MATRIZ_VAZIA -2

typedef struct{
    int col;
    int value;
} Entrada_matriz;

typedef struct{
    Lista multiLista;
    int numColunas;
} Matriz_esparsa;

enum boolean{
    false,
    true
};

void inicializa_matriz( Matriz_esparsa *m);
int insere_valor(Matriz_esparsa *m, int l, int c, int val);
int get_valor_celula(Matriz_esparsa *m, int l, int c);
Matriz_esparsa soma_matrizes(Matriz_esparsa m1, Matriz_esparsa m2);
void desaloca_matriz(Matriz_esparsa *m);
void imprimi_matriz(Matriz_esparsa m);
int matriz_vazia(Matriz_esparsa m);
