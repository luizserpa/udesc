#include <stdlib.h>
#include <stdio.h>
#include "FilaInt.h"
#include "Pilha.h"
#include <time.h>

int insereNumeroAleatorio(FilaInt *f, int quantNumeroAdd);

void main(){
    srand(time(NULL)); 
    int n;
    FilaInt f;
    Pilha p;
    inicializaFila(&f, 10);
    inicializa_pilha(&p, 10);
    insereNumeroAleatorio(&f, 5);
    imprimiFila(f);
    while (leInicio(f, &n) != ERRO_FILA_VAZIA)
    {
        removerDado(&f, &n);
        empilha(&p, n);
    }
    while (le_topo(p, &n) != ERRO_PILHA_VAZIA)
    {
        desempilha(&p, &n);
        inserirDado(&f, n);
    }
    imprimiFila(f);
}

int insereNumeroAleatorio(FilaInt *f, int quantNumeroAdd){
    int aleatorio;
    for (size_t i = 0; i < quantNumeroAdd; i++)
    {
        aleatorio = rand() % 99;
        if (aleatorio % 2 == 0)
        {
            inserirDado(f, aleatorio);
        }else
        {
            inserirDado(f, aleatorio);
        }
    }
}



