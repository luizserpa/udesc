#include <stdio.h>
#include <stdlib.h>
#include "FilaIntIndex0.h"

void inicializaFila(FilaInt *f, int size){
    f->inicio = 0;
    f->capacidade = size;
    f->fim = -1;
    f->dados = calloc(sizeof(int), size);
}

void desalocarFila(FilaInt *f){
    free(f->dados);
}

int filaVazia(FilaInt f){
    return f.fim == -1;
}

int filaCheia(FilaInt f){
    return f.fim == f.capacidade;
}

int inserirDado (FilaInt *f, int info){
    if (filaCheia (*f))
    {
        return ERRO_FILA_CHEIA;
    }
    f->dados[f->fim + 1] = info;
    f->fim++;
    return 1;
}

int removerDado (FilaInt *f, int *info){
    if (filaVazia(*f))
    {
        return ERRO_FILA_VAZIA;
    }
    *info = f->dados[f->inicio];
    for (size_t i = 0; i < f->fim; i++)
    {
        f->dados[i] = f->dados[i+1];
    }
    f->fim--;
    return 1;
}

void imprimiFila(FilaInt f){
    if (filaVazia(f))
    {
        return;
    }
    printf("Fila:\n");
    for (size_t i = 0; i <= f.fim; i++)
    {
        printf("[%ld]: %d\n",i,  f.dados[f.inicio + i]);
    }
}

