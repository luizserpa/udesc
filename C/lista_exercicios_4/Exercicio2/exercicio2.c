#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "FilaIntIndex0.h"

int insereNumeroAleatorio(FilaInt *f, int quantNumeroAdd);

void main(){
    srand(time(NULL)); 
    int n;
    FilaInt f;
    inicializaFila(&f, 10);
    insereNumeroAleatorio(&f, 10);
    imprimiFila(f);
    removerDado(&f, &n);
    imprimiFila(f);
    removerDado(&f, &n);
    removerDado(&f, &n);
    removerDado(&f, &n);
    insereNumeroAleatorio(&f, 1);
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
            inserirDado(f, aleatorio);
        }else
        {
            inserirDado(f, -aleatorio);
        }
    }
}