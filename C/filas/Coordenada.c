#include <stdio.h>
#include <stdlib.h>
#include "Coordenada.h"
#include <string.h>


void inicializa_posicao_coor(Coordenada *c, int xInfo, int yInfo){
    c->x = xInfo;
    c->y = yInfo;
    c->distanciaOrigem = 0;
}

void informa_posicao_coor(Coordenada c, int *xInfo, int *yInfo){
    *xInfo = c.x;
    *yInfo = c.y;
}

void atualiza_distancia_coor(Coordenada *c, int dist){
    c->distanciaOrigem = dist;
}

void atualiza_caminho_coor(Coordenada *c){
    char posX[4] = {c->x + 48};
    char posy[4] = {c->y + 48};
    strcat(c->caminho, posX);
    strcat(c->caminho, " ");
    strcat(c->caminho, posy);
    strcat(c->caminho, " ");
}

void passa_distancia_coor(Coordenada c, int *dist){
    *dist = c.distanciaOrigem;
}

void passa_caminho_coor(Coordenada c, char *cam){
    strcpy(cam, c.caminho);
}

void novo_caminho_coor(Coordenada *c, char *novoCam){
    strcpy(c->caminho, novoCam);
    atualiza_caminho_coor(c);
}

void imprimir_pos_coor(Coordenada c){
    int x, y;
    informa_posicao_coor(c, &x, &y);
    printf("Coordenada x: %d, y: %d\n", x, y);
}