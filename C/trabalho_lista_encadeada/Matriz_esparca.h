#include <Lista.h>

typedef struct{
    int col;
    int value;
} Entrada_matriz;

typedef struct{
    Lista *multiLista;
    int numColunas;
} Matriz_esparca;

enum{
    false,
    true
};

void inicializa_matriz( Matriz_esparca *m);
int insere_valor(Matriz_esparca *m, int l, int c, int val);
int get_valor_celula(Matriz_esparca m, int l, int c);
Matriz_esparca soma_matrizes(Matriz_esparca m1, Matriz_esparca m2);
void desaloca_matriz(Matriz_esparca *m);
void imprimi_matriz(Matriz_esparca m);
int matriz_vazia(Matriz_esparca m);
