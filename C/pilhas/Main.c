#include <stdlib.h>
#include <stdio.h>
#include "Utilitarios.h"


#define STRING_SIZE 255

void main(){
    char stringInfixa[STRING_SIZE];
    char stringPosfixa[STRING_SIZE];
    PilhaChar p;

    while (!incluirString(stringInfixa, STRING_SIZE));
    inicializa_pilha_char(&p, STRING_SIZE);
    transformaInfPos(&p, stringInfixa, stringPosfixa);
    desaloca_pilha_char(&p);
    somaPosfixa(stringPosfixa);
}