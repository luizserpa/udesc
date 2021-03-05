#include "Coordenada.h"
#include "ManipulaArquivo.h"

enum{
    false,
    true
} bool;

int valida_entrada_saida(Coordenada e, Coordenada s, MatrizDinamica m);
void marca_visita(MatrizDinamica *ms, Coordenada c);
int valida_coordenada(Coordenada c, MatrizDinamica m);
int compara_coordenadas(Coordenada c1, Coordenada c2);
void posicao_adjacente (int i, int *x, int *y);
int verifica_adjacente(int i, Coordenada c, MatrizDinamica m, MatrizDinamica ms);
Coordenada celula_adjacente(int i,Coordenada c,MatrizDinamica *ms);
void imprimir_resultado(Coordenada c, MatrizDinamica *m);