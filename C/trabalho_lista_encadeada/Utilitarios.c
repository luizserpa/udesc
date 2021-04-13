#include <stdlib.h>
#include <stdio.h>
#include "Utilitarios.h"

int setNumero(char []);

void menuTexto () {
    printf("--- MENU ---\n");
    printf("\n");
    printf("1. Criar Nova Matriz. \n");
    printf("2. Mostrar Dados de Uma Matriz. \n");
    printf("3. Modificar Dados. \n");
    printf("4. Somar Duas Matrizes. \n");
    printf("5. Remover uma matriz. \n");
    printf("Obs.: Todos os valores com index inicial 1. \n");
    printf("\n")
}

int escolhaMenu(){
    return setNumero("Favor escolha a opção desejada: \n");
}

int setNumero(char informacaoNumero[]){
    int numero;
    char limpa_buffer[255];
    while(true){
        printf("%s", informacaoNumero);
        if (scanf("%d", &numero)){
            fgets(limpa_buffer, 255, stdin);
            if(numero >= 0 && numero <= 5){
                return numero;
            }
            printf("Entrada Invalida\n");
            fgets(limpa_buffer, 255, stdin);
        }else{
            printf("Entrada Invalida\n");
            fgets(limpa_buffer, 255, stdin);
        }
    }
}
