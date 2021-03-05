#include <stdio.h>
#include <stdlib.h>
#include "FilaGenerica.h"
#include "Utilitarios.h"

#define NOME_ARQUIVO "info_lab.txt"

/*
Arquivo Organizado da sequinte forma:

n_linhas n_colunas (Dimenções)
numeros matriz organizados
n_linha n_coluna (Posição Inicial)
n_linha n_coluna (posilça final)

Todos os numeros devem ser separados por espaço simples
*/

int main(){
    FILE *arquivo = abre_arquivo_leitura(NOME_ARQUIVO);
    MatrizDinamica m;
    MatrizDinamica ms;
    Coordenada e;
    Coordenada s;
    FilaGenerica f;
    int x, y;
    int achou = false;

    if (!tamanho_necessario(&x, &y, arquivo))
    {
        printf("ERRO -> Arquivo não existe\n");
        return 0;
    }
    inicializa_matriz(&m, y, x);
    inicializa_matriz(&ms, y, x);
    if (!popula_matriz(&m, arquivo))
    {
        printf("ERRO -> Numeros Invalidos presentes na matriz\n");
        return 0;
    }
    inicializa_fila(&f, x*y, sizeof(Coordenada));

    coordenada_entrada(&x, &y, arquivo);
    inicializa_posicao_coor(&e, (x-1), (y-1));
    atualiza_caminho_coor(&e);
    coordenada_saida(&x, &y, arquivo);
    inicializa_posicao_coor(&s, (x-1), (y-1));
    fecha_arquivo(arquivo);

    if (!valida_entrada_saida(e, s, m))
    {
        printf("ERRO -> Entrada Ou Saida Invalida\n");
        return 0;
    }
    
    marca_visita(&ms, e);
    inserir(&f, &e);
    Coordenada c;
    while (!fila_vazia(f) && !achou)
    {
        remover(&f, &c);
        if (compara_coordenadas(c, s))
        {
            achou = true;
        }else
        {
            for (size_t i = 0; i < 4; i++)
            {
                if (verifica_adjacente(i, c, m, ms))
                {
                    Coordenada nc = celula_adjacente(i, c, &ms);
                    inserir(&f, &nc);
                }
            }
        }
    }
    if (achou)
    {
        imprimir_resultado(c, &m);
    }else
    {
        printf("Não existe caminho possível entre a Entrada e Saida\n");
    }

    desaloca_fila(&f);
    desaloca_matriz(&m);
    desaloca_matriz(&ms);
    return 0;
}