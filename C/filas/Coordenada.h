#define SIZE_CAMINHO 1024

typedef struct 
{
    int x;
    int y;
    int distanciaOrigem;
    char caminho[SIZE_CAMINHO];
}Coordenada;

void inicializa_posicao_coor(Coordenada *c, int xInfo, int yInfo);
void informa_posicao_coor(Coordenada c, int *xInfo, int *yInfo);
void atualiza_distancia_coor(Coordenada *c, int dist);
void atualiza_caminho_coor(Coordenada *c);
void passa_distancia_coor(Coordenada c, int *dist);
void passa_caminho_coor(Coordenada c, char *cam);
void novo_caminho_coor(Coordenada *c, char *novoCam);
void imprimir_pos_coor(Coordenada c);

