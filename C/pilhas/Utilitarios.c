#include <stdio.h>
#include <stdlib.h>
#include "Utilitarios.h"
#include "Pilha.h"
#include <string.h>

void transformaInfPos(PilhaChar *p, char infixa[], char posfixa[]){
    int i = 0;
    int j = 0;
    int isMesmoNumero = 0;
    int deuErro = 0;
    
    while (infixa[i] != '\0' && !deuErro)
    {
        char c = infixa[i];
        int tipoChar = identificarChar(c);
        char x;
        if (c != ' ')
        {
            switch (tipoChar)
            {
            case numero:
                if (j == 0)
                {
                    isMesmoNumero = 1;
                    posfixa[j] = c;
                    j++;
                }else if (isMesmoNumero)
                {
                    isMesmoNumero = 1;
                    posfixa[j] = c;
                    j++;
                }
                else
                {
                    j = adicionaCharComEspaco(posfixa, c, j);
                    isMesmoNumero = 1;
                }
                break;
            case abreParenteses:
                empilha_char(p, c);
                isMesmoNumero = 0;
                break;
            case fechaParenteses:
                isMesmoNumero = 0;
                while (le_topo_char(*p, &x) != -1 && x != '(')
                {
                    desempilha_char(p, &x);
                    j = adicionaCharComEspaco(posfixa, x, j);
                }
                if (pilha_vazia_char(*p))
                {
                    printf("Erro: ')' sem '(' ! \n");
                    deuErro = 1;
                }else
                {
                    desempilha_char(p, &x);
                }
                break;
            case operador:
                isMesmoNumero = 0;
                le_topo_char(*p, &x);
                if (pilha_vazia_char(*p) || x == '(')
                {
                    empilha_char(p, c);
                }else
                {
                    while (le_topo_char(*p, &x) != -1 && precedencia(x) >= precedencia(c))
                    {
                        desempilha_char(p, &x);
                        j = adicionaCharComEspaco(posfixa, x, j);
                    }
                    empilha_char(p, c);
                }
                
                break;
            default:
                printf ("Erro: caractere invalido: %c \n", c);
                deuErro = 1;
                break;
            }
        }
        i++;
    }
    if (!deuErro)
    {
        char x;
        while (le_topo_char(*p, &x) != -1 && x != '(')
        {
            desempilha_char(p, &x);
            j = adicionaCharComEspaco(posfixa, x, j);
        }
        if (pilha_vazia_char(*p))
        {
            posfixa[j] = '\0';
            printf("Expressão posfixa: %s\n", posfixa);
        } else
        {
            printf("Erro: '(' não foi fechado\n");
        } 
    }
}

void somaPosfixa(char posfixa[]){
    int j = 0;
    char c;
    int num1 = 0, num2 = 0, resultado = 0;
    Pilha p;
    inicializa_pilha(&p, 50);
    while (posfixa[j] != '\0')
    {
        c = posfixa[j];
        if (c != ' ')
        {
            if (encontraNumero(posfixa, &j, &num1))
            {
                empilha(&p, num1);
            }else
            {
                desempilha(&p, &num2);
                desempilha(&p, &num1);
                resultado = calcula(c, num1, num2);
                empilha(&p, resultado);
            }
        }else
        {
            j++;
        }
        
    }
    desempilha(&p, &resultado);
    printf("Resultado (%s) = %d\n", posfixa, resultado);
}

int identificarChar(char c){
    if (c >= 48 && c <= 57) return numero;
    if (c == '(') return abreParenteses;
    if (c == ')') return fechaParenteses;
    if (c == '+' || c == '-' || c == '*' || c == '/') return operador;
    return outro;
}

int adicionaCharComEspaco(char *string, char c, int posicao){
    string[posicao] = ' ';
    posicao++;
    string[posicao] = c;
    posicao++;
    return posicao;
}

int precedencia(char x){
    if (x == '(') return 0;
    if (x == '+' || x == '-') return 1;
    if (x == '*' || x == '/') return 2;
    printf("Erro -> func: precedencia - Operador Invalido\n");
    return -1;
}

int encontraNumero(char posfixa[], int *j, int *num){
    int p = 0;
    *num = 0;
    int isNumero = identificarChar(posfixa[(*j)]);
    if (isNumero != numero)
    {
        (*j)++;
        return 0;
    }
    while (posfixa[(*j) + p] != ' ' && posfixa[(*j) + p] != '\0')
    {
        p++;
    }
    for (int x = 0; x < p; x++)
    {
        *num += (posfixa[(*j) + x] - 48)*potenciaBase10(p-x-1);
    }
    *j += p;
    return 1;
}

int potenciaBase10(int p){
    int n = 1;
    for (size_t i = 0; i < p; i++)
    {
        n *= 10;
    }
    return n;
}

int calcula (char c, int aux1, int aux2){
    if (c == '*') return aux1 * aux2;
    if (c == '/') return aux1 / aux2;
    if (c == '+') return aux1 + aux2;
    if (c == '-') return aux1 - aux2;
    printf("Erro -> func: calcula - Operador Invalido\n");
    return -1;
}

int incluirString(char string[], int stringSize){
    printf("Informe a expressão aritimetica infixa (Apenas numeros naturais)\n");
    if (fgets(string, stringSize, stdin))
    {
        string[strcspn(string, "\n")] = 0;
        return 1;
    }
    printf("ERRO - STRING INVALIDA\n");
    return 0;
}