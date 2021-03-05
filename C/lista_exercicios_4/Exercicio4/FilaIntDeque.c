#include <stdio.h>
#include <stdlib.h>
#include "FilaIntDeque.h"


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

int inserirFimFila(FilaInt *f, int info){
    if (filaCheia (*f))
    {
        return ERRO_FILA_CHEIA;
    }
    int posicaoFim = (f->inicio + f->qntOcupada) % f->capacidade;
    f->dados[posicaoFim] = info;
    f->qntOcupada++;
    return 1;
}

int removerFimFila(FilaInt *f, int *info){
    if (filaVazia(*f))
    {
        return ERRO_FILA_VAZIA;
    }
    int posicaoFim = (f->inicio + f->qntOcupada - 1) % f->capacidade;
    *info = f->dados[posicaoFim];
    f->qntOcupada--;
    f->dados[posicaoFim] = 150;
    return 1;
}

int removerInicioFila (FilaInt *f, int *info){
    if (filaVazia(*f))
    {
        return ERRO_FILA_VAZIA;
    }
    *info = f->dados[f->inicio];
    f->dados[f->inicio] = 150;
    f->inicio = (f->inicio + 1) % f->capacidade;
    f->qntOcupada--;
    return 1;
}

int inserirInicioFila (FilaInt *f, int info){
    if (filaCheia(*f))
    {
        return ERRO_FILA_CHEIA;
    }
    int posicaoInicio;
    if ((f->inicio) == 0)
    {
        posicaoInicio = f->capacidade - 1;
    }else {
        posicaoInicio = f->inicio - 1;
    }
    f->inicio = posicaoInicio;
    f->dados[posicaoInicio] = info;
    f->qntOcupada++;
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
        printf("%d",  f.dados[(f.inicio + i) % f.capacidade]);
        if (i != f.qntOcupada -1)
        {
            printf(", ");
        }
    }
    printf(".\n");
}