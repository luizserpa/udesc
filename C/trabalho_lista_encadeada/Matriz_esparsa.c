#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Matriz_esparsa.h"

int insere_linha(Matriz_esparsa *m);
Entrada_matriz new_entrada(int c, int val);
int add_linhas(Matriz_esparsa *m, int numLinhas);
int get_coluna_EM (Entrada_matriz e);
int get_value_EM (Entrada_matriz e);
void set_value_EM (Entrada_matriz *e, int value);
int comparaNumCol(void *e1, void *e2);
void imprimi_linha(Lista linha, int qntColunas);
void atualiza_tam_col(Matriz_esparsa *m, int c);
void imprimi_linha_vazia(int qntColunas);
Entrada_matriz soma_elementos(Matriz_esparsa m1, Matriz_esparsa m2, int l, int c);

void inicializa_matriz( Matriz_esparsa *m){
    inicializa_lista(m->multiLista, sizeof(Lista));
}

int insere_linha(Matriz_esparsa *m){
    Lista *linha;
    inicializa_lista(linha, sizeof(Entrada_matriz));
    if(!insere_fim(m->multiLista, linha)) return false;
    return true;
}

int add_linhas(Matriz_esparsa *m, int numLinhas){
    if (numLinhas > 0){
        int i = 0;
        for(i = 0; i < numLinhas; i++){
            insere_linha(m);
        }
        return true;
    }
    return false;
}

// Recebe numero de linha e coluna com index inicial 1
int insere_valor(Matriz_esparsa *m, int l, int c, int val){
    if(l < 1 || c < 1) return ERRO_POS_INVALIDA;
    if (matriz_vazia(*m)) return ERRO_MATRIZ_VAZIA;
    Lista linha;
    Entrada_matriz el;
    int lI0 = l - 1, i = 0;
    int cI0 = c - 1;
    int numLinhaAdicionar = lI0 - tamanho_lista(*m->multiLista);
    add_linhas(m, numLinhaAdicionar);

    if (get_valor_celula(*m, l, c)){
        le_valor(*m->multiLista, &linha, lI0);
        for (i = 0; i < tamanho_lista(linha); i++){
            le_valor(linha, &el, i);
            if (cI0 == get_coluna_EM(el)){
                if(val == 0){
                    remove_pos(&linha, &el, i);
                }else {
                    set_value_EM(&el, val);
                    modifica_valor(linha, &el, i);
                }
                modifica_valor(*m->multiLista, &linha, lI0);
                atualiza_tam_col(m, c);
                return true;
            }
        }
        return false;
    } else {
        if (val == 0) {
            return true;
        }
        le_valor(*m->multiLista, &linha, lI0);
        el = new_entrada(cI0, val);
        insere_ordem(&linha, &el, *comparaNumCol);
        modifica_valor(*m->multiLista, &linha, lI0);
        atualiza_tam_col(m, c);
        return true;
    }
}

int comparaNumCol (void *e1, void *e2){
    Entrada_matriz el1;
    Entrada_matriz el2;
    memcpy(&el1, e1, sizeof(Entrada_matriz));
    memcpy(&el2, e2, sizeof(Entrada_matriz));
    return get_coluna_EM(el1) > get_coluna_EM(el2);
}

Entrada_matriz new_entrada(int c, int val){
    Entrada_matriz m;
    m.col = c;
    m.value = val;
    return m;
}

// Linha e coluna com index inicial 1
int get_valor_celula(Matriz_esparsa m, int l, int c){
    Lista linha;
    Entrada_matriz e;
    if (le_valor(*m.multiLista, &linha, l-1) <= 0) return 0;
    if (!lista_vazia(linha)){
        int i = 0;
        for (i = 0; i < tamanho_lista(linha); i++){
            le_valor(linha, &e, i);
            if ((c-1) == get_coluna_EM(e)) return get_value_EM(e);
        }
        return 0;
    }else {
        return 0;
    }
}

int get_coluna_EM (Entrada_matriz e){
    return e.col;
}

int get_value_EM (Entrada_matriz e){
    return e.value;
}

void set_value_EM (Entrada_matriz *e, int value){
    e->value = value;
}

void desaloca_matriz(Matriz_esparsa *m){
    desaloca_sub_lista(m->multiLista);
    desaloca_lista(m->multiLista);
}

void imprimi_linha(Lista linha, int qntColunas){
    size_t i = 0, j = 0;
    Entrada_matriz em;
    if (le_valor(linha, &em, i) > 0){
        for ( i = 0; i < tamanho_lista(linha); i++)
        {
            while (j < qntColunas)
            {
                if (j == get_coluna_EM(em))
                {
                    printf(" %d", get_value_EM(em));
                    j++;
                    break;
                }
                printf(" 0");
                j++;
            }
        }
        printf("\n");
    } else {
        imprimi_linha_vazia(qntColunas);
    }

}

void imprimi_linha_vazia(int qntColunas){
    size_t i = 0;
    for (i = 0; i < qntColunas; i++)
    {
        printf(" 0");
    }
    printf("\n");
}

void atualiza_tam_col(Matriz_esparsa *m, int c){
    m->numColunas = m->numColunas < (c - 1) ? c : m->numColunas;
}

void imprimi_matriz(Matriz_esparsa m){
    int numLinhas = tamanho_lista(*m.multiLista);
    int numColunas = m.numColunas;
    Lista linha;
    size_t i = 0;
    printf("Matriz [ %d, %d]\n", numLinhas, m.numColunas);
    for ( i = 0; i < numLinhas; i++)
    {
        if(le_valor(*m.multiLista, &linha, i) > 0){
            imprimi_linha(linha, numColunas);
        }else {
            printf("Matriz Vazia");
        }
    }
    printf("\n");
}

int matriz_vazia(Matriz_esparsa m){
    return lista_vazia(*m.multiLista);
}

int linha_vazia(Matriz_esparsa m, int l){
    int lI0 = l - 1;
    Lista linha;
    le_valor (*m.multiLista, &linha, lI0);
    return lista_vazia(linha);
}


Matriz_esparsa soma_matrizes(Matriz_esparsa m1, Matriz_esparsa m2){
    Matriz_esparsa matriz_soma;
    inicializa_matriz(&matriz_soma);
    if (matriz_vazia(m1) && matriz_vazia(m2)) return matriz_soma;
    if (matriz_vazia(m1)) return m2;
    if (matriz_vazia(m2)) return m1;

    int numLinhas = tamanho_lista(*m1.multiLista) > tamanho_lista(*m2.multiLista) ? tamanho_lista(*m1.multiLista) : tamanho_lista(*m2.multiLista);
    int numColunas = m1.numColunas > m2.numColunas ? m1.numColunas : m2.numColunas;

    size_t i = 0, j = 0;
    for (i = 0; i < numLinhas; i++)
    {
        for (j = 0; j < numColunas; j++)
        {
            Entrada_matriz el = soma_elementos(m1, m2, i + 1, j + 1);
            insere_valor(&matriz_soma, i+1, j+1, get_value_EM(el));
        }
    }
    return matriz_soma;
}

// Linha e coluna com index inicial 1
Entrada_matriz soma_elementos(Matriz_esparsa m1, Matriz_esparsa m2, int l, int c){
    int val1 = get_valor_celula(m1, l, c);
    int val2 = get_valor_celula(m2, l, c);
    Entrada_matriz el = new_entrada(c-1, val1 + val2);
    return el;
}






