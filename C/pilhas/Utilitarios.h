#include "PilhaChar.h"

enum{
    numero,
    abreParenteses,
    fechaParenteses,
    operador,
    outro
} tiposDeChar;

int incluirString(char string[], int stringSize);
void transformaInfPos(PilhaChar *p, char infixa[], char posfixa[]);
int precedencia(char x);
int identificarChar(char c);
int adicionaCharComEspaco(char string[], char c, int posicao);
void somaPosfixa(char posfixa[]);
int encontraNumero(char posfixa[], int *j, int *num);
int potenciaBase10(int p);
int calcula (char c, int aux1, int aux2);