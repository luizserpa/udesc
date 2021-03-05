#include <stdlib.h>
#include <stdio.h>
#include "FilaComPilha.h"

void invertePilha(Pilha p1, Pilha *p2);


void inicializaFila(FilaInt *f, int capacidade){
    inicializa_pilha(&(f->pe), capacidade);
    inicializa_pilha(&(f->ps), capacidade);
}

void desalocarFila(FilaInt *f){
    desaloca_pilha(&(f->pe));
    desaloca_pilha(&(f->ps));
}

int filaCheia(FilaInt f){
    return pilha_cheia(f.pe);
}

int filaVazia(FilaInt f){
    return pilha_vazia(f.pe);
}

int inserirDado (FilaInt *f, int info){
    if (filaCheia(*f) == ERRO_PILHA_CHEIA)
    {
        return ERRO_FILA_CHEIA;
    }
    empilha(&(f->pe), info);
    invertePilha(f->pe, &(f->ps));
    return 1;
}

int removerDado (FilaInt *f, int *info){
    if (filaVazia(*f))
    {
        return ERRO_FILA_VAZIA;
    }
    desempilha(&(f->ps), info);
    invertePilha(f->ps, &(f->pe));
    return 1;
}

int leInicio (FilaInt f, int *info){
    if (filaVazia(f))
    {
        return ERRO_FILA_VAZIA;
    }
    le_topo(f.pe, info);
    return 1;
}

void imprimiFila(FilaInt f){
    if (filaVazia(f))
    {
        return;
    }
    int n;
    printf("Fila: ");
    while (le_topo(f.ps, &n) != ERRO_PILHA_VAZIA)
    {
        desempilha(&f.ps, &n);
        printf("%d\t", n);
    }
    printf("\n");
}

void invertePilha(Pilha p1, Pilha *p2){
    int n;
    while (le_topo(*p2, &n) != ERRO_PILHA_VAZIA)
    {
        desempilha(p2, &n);
    }
    while (le_topo(p1, &n) != ERRO_PILHA_VAZIA)
    {
        desempilha(&p1, &n);
        empilha(p2, n);
    }
}

