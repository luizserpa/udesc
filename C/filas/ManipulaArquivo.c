#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ManipulaArquivo.h"

FILE *abre_arquivo_leitura(char *indereco){
    FILE *arquivo = fopen(indereco, "r");
    return arquivo;
}

int fecha_arquivo(FILE *arquivo){
    if (arquivo != NULL)
    {
        fclose(arquivo);
        return 1;
    }
    return ERRO_ARQUIVO_INEXISTENTE;
}

int tamanho_necessario(int *x, int *y, FILE *arquivo){
    if (arquivo != NULL)
    {
        char *tamanhos = calloc(SIZE_STRING_PAD, sizeof(char));
        char *token = calloc(SIZE_STRING_PAD, sizeof(char));
        int i = 0;
        fgets(tamanhos, SIZE_STRING_PAD, arquivo);
        token = strtok(tamanhos, " ");
        *y = atoi(token);
        token = strtok(NULL, " ");
        *x = atoi(token);
        free(tamanhos);
        return 1;
    }
    if (arquivo == NULL)
    {
        return ERRO_ARQUIVO_INEXISTENTE;
    }
}

int popula_matriz(MatrizDinamica *m, FILE *arquivo){
    int numerosEsperados = 1;
    if (arquivo != NULL)
    {
        int x, y, num;
        char *linha = calloc(SIZE_STRING_PAD, sizeof(char));
        char *token = calloc(SIZE_STRING_PAD, sizeof(char));
        dimencoes_matriz(*m, &x, &y);
        for (size_t i = 0; i < y; i++)
        {
            fgets(linha, SIZE_STRING_PAD, arquivo);
            token = strtok(linha, " ");
            for (size_t j = 0; j < x; j++)
            {
                num = atoi(token);
                modifica_matriz(m, i, j, num);
                token = strtok(NULL, " ");
                if (num < 0 || num > 1)
                {
                    numerosEsperados = 0;
                }
                
            }
        } 
        free(linha);
    }
    return numerosEsperados;
}

int coordenada_entrada(int *x, int *y, FILE *arquivo){
    return tamanho_necessario(x, y, arquivo);
}

int coordenada_saida(int *x, int *y, FILE *arquivo){
    return tamanho_necessario(x, y, arquivo);
}

