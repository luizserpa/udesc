#include <stdlib.h>
#include <stdio.h>
#include "Utilitarios.h"

int setNumero(char []);

void menuTexto () {
    printf("\n\n\n--- MENU ---\n");
    printf("\n");
    printf("1. Criar Nova Matriz. \n");
    printf("2. Mostrar Dados de Uma Matriz. \n");
    printf("3. Modificar Dados. \n");
    printf("4. Somar Duas Matrizes. \n");
    printf("5. Remover uma matriz. \n");
    printf("0. Sair. \n");
    printf("Obs.: Todos os valores com index inicial 1. \n");
    printf("\n");
}

int escolhaMenu(int matrizesDisponiveis){
    int numero = 0;
    do
    {
        printf("Existem %d matrizes disponiveis.\n", matrizesDisponiveis);
        numero = setNumero("Favor escolha a opção desejada: ");
        printf("\n");
        if (numero >= 0 && numero <= 5){
            return numero;
        }
        printf("Entrada Invalida. \n");
    } while (true);
}

int setNumero(char informacaoNumero[]){
    int numero;
    char limpa_buffer[255];
    while(true){
        printf("%s", informacaoNumero);
        if (scanf("%d", &numero)){
            fgets(limpa_buffer, 255, stdin);
            return numero;
        }else{
            printf("Entrada Invalida.\n");
            fgets(limpa_buffer, 255, stdin);
        }
    }
}

int escolhaIndex(char info[]) {
    int index = 0;
    do
    {
        index = setNumero(info);
        if (index > 0){
            return index;
        }
        printf("Entrada Invalida. \n");
    } while (true);
}

int valida_leitura(int leituraValida){
    if(leituraValida == -1){
        printf("ERRO LISTA VAZIA!\n");
        return 0;
    }else if (leituraValida == - 2){
        printf("ERRO POSIÇÃO INVALIDA!\n");
        return 0;
    }
    return 1;
}

