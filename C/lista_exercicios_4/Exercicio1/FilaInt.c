#include <stdio.h>
#include <stdlib.h>
#include "FilaInt.h"

void inicializaFila(FilaInt *f, int size){
    f->inicio = 0;
    f->capacidade = size;
    f->qntOcupada = 0;
    f->dados = calloc(sizeof(int), size);
}

void desalocarFila(FilaInt *f){
    free(f->dados);
}

int filaVazia(FilaInt f){
    return f.qntOcupada == 0;
}

int filaCheia(FilaInt f){
    return f.qntOcupada == f.capacidade;
}

int inserirDado (FilaInt *f, int info){
    if (filaCheia (*f))
    {
        return ERRO_FILA_CHEIA;
    }
    int posicaoFim = (f->inicio + f->qntOcupada) % f->capacidade;
    f->dados[posicaoFim] = info;
    f->qntOcupada++;
    return 1;
}

int removerDado (FilaInt *f, int *info){
    if (filaVazia(*f))
    {
        return ERRO_FILA_VAZIA;
    }
    *info = f->dados[f->inicio];
    f->inicio = (f->inicio + 1) % f->capacidade;
    f->qntOcupada--;
    return 1;
}

int leInicio(FilaInt f, int *info){
    if (filaVazia (f))
    {
        return ERRO_FILA_VAZIA;
    }
    *info = f.dados[f.inicio];
    return 1;
}

void imprimiFila(FilaInt f){
    if (filaVazia (f))
    {
        return;
    }
    printf("Fila: ");
    for (size_t i = 0; i < f.qntOcupada; i++)
    {
        printf("%d", f.dados[(f.inicio + i) % f.capacidade]);
        if (i != f.qntOcupada -1)
        {
            printf(", ");
        }
    }
    printf(".\n");
}
