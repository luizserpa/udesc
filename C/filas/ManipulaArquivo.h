#include "MatrizDinamica.h"

#define SIZE_STRING_PAD 255
#define ERRO_ARQUIVO_INEXISTENTE 0

FILE *abre_arquivo_leitura(char *indereco);
int fecha_arquivo(FILE *arquivo);
int tamanho_necessario(int *x, int *y, FILE *arquivo);
int popula_matriz(MatrizDinamica *m, FILE *arquivo);
int coordenada_entrada(int *x, int *y, FILE *arquivo);
int coordenada_saida(int *x, int *y, FILE *arquivo);