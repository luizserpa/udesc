#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "FilaIntDeque.h"

int insereNumeroAleatorio(FilaInt *f, int quantNumeroAdd);

void main(){
    srand(time(NULL)); 
    int n;
    FilaInt f;
    inicializaFila(&f, 10);
    insereNumeroAleatorio(&f, 10);
    imprimiFila(f);
    removerInicioFila(&f, &n);
    removerInicioFila(&f, &n);
    imprimiFila(f);
    removerFimFila(&f, &n);
    removerFimFila(&f, &n);
    imprimiFila(f);
    inserirFimFila(&f, 11);
    inserirFimFila(&f, 11);
    inserirFimFila(&f, 11);
    imprimiFila(f);
    removerFimFila(&f, &n);
    removerFimFila(&f, &n);
    removerFimFila(&f, &n);
    inserirInicioFila(&f, 10);
    inserirInicioFila(&f, 10);
    inserirInicioFila(&f, 10);
    imprimiFila(f);
}

int insereNumeroAleatorio(FilaInt *f, int quantNumeroAdd){
    int aleatorio;
    for (size_t i = 0; i < quantNumeroAdd; i++)
    {
        aleatorio = rand() % 99;
        int aleatorio2 = (rand() % 6) + 1;
        if ((aleatorio % aleatorio2) % 2 == 0)
        {
            inserirFimFila(f, aleatorio);
        }else
        {
            inserirFimFila(f, -aleatorio);
        }
    }
}