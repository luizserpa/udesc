#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Utilitarios.h"

int valida_coordenada(Coordenada c, MatrizDinamica m){
    int dimencao_x, dimencao_y;
    int pos_x, pos_y;
    dimencoes_matriz(m, &dimencao_x, &dimencao_y);
    informa_posicao_coor(c, &pos_x, &pos_y);
    if (pos_x < 0 || pos_x > dimencao_x || pos_y < 0 || pos_y > dimencao_y)
    {
        return false;
    }
    return true;
}


int valida_entrada_saida(Coordenada e, Coordenada s, MatrizDinamica m){
    int x, y;
    informa_posicao_coor(e, &x, &y);
    if (!valida_coordenada(e, m) || pegar_valor_matriz(m, x, y) == 0)
    {
        return false;
    }
    informa_posicao_coor(s, &x, &y);
    if (!valida_coordenada(s, m) || pegar_valor_matriz(m, x, y) == 0)
    {
        return false;
    }
    return true;
}

void marca_visita(MatrizDinamica *ms, Coordenada c){
    if (valida_coordenada(c, *ms))
    {
        int x, y;
        informa_posicao_coor(c, &x, &y);
        modifica_matriz(ms, y, x, 1);
    }
}

int compara_coordenadas(Coordenada c1, Coordenada c2){
    int c1_x, c1_y, c2_x, c2_y;
    informa_posicao_coor(c1, &c1_x, &c1_y);
    informa_posicao_coor(c2, &c2_x, &c2_y);
    if (c1_x == c2_x && c1_y == c2_y)
    {
        return true;
    }
    return false;
}

int verifica_adjacente(int i, Coordenada c, MatrizDinamica m, MatrizDinamica ms){
    int x, y;
    int dim_x, dim_y;
    dimencoes_matriz(m, &dim_x, &dim_y);
    informa_posicao_coor(c, &x, &y);
    posicao_adjacente(i, &x, &y);
    if (x >= 0 && y>= 0 && x < dim_x && y < dim_y)
    {
        if (pegar_valor_matriz(m, x, y) == 1 && pegar_valor_matriz(ms, x, y) == 0)
        {
            return true;
        }
    }
    
    return false;
}

void posicao_adjacente (int i, int *x, int *y){
    switch (i)
    {
    case 0:
        *y -= 1;
        break;
    case 1:
        *x -= 1;
        break;
    case 2:
        *y += 1;
        break;
    case 3:
        *x += 1;
        break;
    default:
        printf("ERRO -> Func -verifica_adjacente- i > 3\n");
        break;
    }
}

Coordenada celula_adjacente(int i,Coordenada c, MatrizDinamica *ms){
    int x_novo, y_novo, distancia_novo;
    char caminho_novo[SIZE_CAMINHO];
    informa_posicao_coor(c, &x_novo, &y_novo);
    posicao_adjacente(i, &x_novo, &y_novo);
    marca_visita(ms, c);

    passa_distancia_coor(c, &distancia_novo);
    passa_caminho_coor(c, caminho_novo);

    Coordenada nc;
    inicializa_posicao_coor(&nc, x_novo, y_novo);
    atualiza_distancia_coor(&nc, distancia_novo + 1);
    novo_caminho_coor(&nc, caminho_novo);
    return nc;
}

void imprimir_resultado(Coordenada c, MatrizDinamica *m){
    int distancia, dim_x, dim_y;
    char *caminho = calloc(SIZE_STRING_PAD, sizeof(char));
    passa_distancia_coor(c, &distancia);
    int x[distancia], y[distancia];
    passa_caminho_coor(c, caminho);
    dimencoes_matriz(*m, &dim_x, &dim_y);

    char *token = calloc(SIZE_STRING_PAD, sizeof(char));
    token = strtok(caminho, " ");
    for (size_t i = 0; i <= distancia; i++)
    {
        x[i] = atoi(token);
        token = strtok(NULL, " ");
        y[i] = atoi(token);
        token = strtok(NULL, " ");
    }
    
    for (size_t t = 0; t <= distancia; t++)
    {
        modifica_matriz(m, y[t], x[t], 11);
    }
    
    mostra_matriz(*m);
    printf("Menor distancia: %d\n", distancia);
}