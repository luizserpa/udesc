#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <Matriz_esparca.h>

int insere_linha(Matriz_esparca *m);
Entrada_matriz new_entrada(int c, int val);
int add_linhas(Matriz_esparca *m, int numLinhas);
int get_coluna_EM (Entrada_matriz e);
int get_value_EM (Entrada_matriz e);
void set_value_EM (Entrada_matriz *e, int value);
int comparaNumCol(Entrada_matriz e1, Entrada_matriz e2);

void inicializa_matriz( Matriz_esparca *m){
    inicializa_lista(m->multiLista, sizeof(Lista));
}

int insere_linha(Matriz_esparca *m){
    Lista *linha;
    (inicializa_lista(linha, sizeof(Entrada_matriz)));
    if(!insere_fim(m->multiLista, linha)) return false;
    return true;
}

int add_linhas(Matriz_esparca *m, int numLinhas){
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
int insere_valor(Matriz_esparca *m, int l, int c, int val){
    if(l < 1 || c < 1) return false;
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
        insere_ordem(&linha, &el, comparaNumCol);
        modifica_valor(*m->multiLista, &linha, lI0);
    }
}

int comparaNumCol (Entrada_matriz e1, Entrada_matriz e2){
    return get_coluna_EM(e1) > get_coluna_EM(e2);
}

Entrada_matriz new_entrada(int c, int val){
    Entrada_matriz m;
    m.col = c;
    m.value = val;
    return m;
}

int get_valor_celula(Matriz_esparca m, int l, int c){
    Lista linha;
    Entrada_matriz e;
    le_valor(*m.multiLista, &linha, l-1);
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











Matriz_esparca soma_matrizes(Matriz_esparca m1, Matriz_esparca m2);
void desaloca_matriz(Matriz_esparca *m);
void imprimi_matriz(Matriz_esparca m);
int matriz_vazia(Matriz_esparca m);
int linha_vazia(Matriz_esparca m, int l);


