#include <stdlib.h>
#include <stdio.h>
#include "Utilitarios.h"

Matriz_esparsa new_matriz ();

int main (){
    Lista matrizes;
    Matriz_esparsa m;
    inicializa_lista(&matrizes, sizeof(Matriz_esparsa));
    int escolha = 0, index = 0, index1 = 0, index2 = 0, isLeituraValida = 0, isLeituraUmValida, isLeituraDoisValida;

    do
    {
        menuTexto();
        escolha = escolhaMenu();
        switch (escolha)
        {
        case 1:
            m = new_matriz();
            insere_fim(&matrizes, &m);
            printf("Nova matriz esparsa criada, Index: %d", tamanho_lista(matrizes));
            break;
        case 2:
            
            index = escolhaIndex("\n\n===   Mostrar dados de uma Matriz.   ===\n\nEscolha o index da matriz: ");
            isLeituraValida = le_valor(matrizes, &m, index - 1);
            if(valida_leitura(isLeituraValida))
                imprimi_matriz(m);
                desaloca_matriz(&m);
            break;
        case 3:
            index = escolhaIndex("\n\n===   Modificar dados de uma Matriz.   ===\n\nInsera 0 para excluir valor\nEscolha o index da matriz: ");
            isLeituraValida = le_valor(matrizes, &m, index - 1);
            if (valida_leitura(isLeituraValida)){
                int l = escolhaIndex("Linha: ");
                int c = escolhaIndex("Coluna: ") ;
                int value = setNumero("Valor Inteiro: ");
                insere_valor(&m, l, c, value);
                modifica_valor(matrizes, &m, index);
                desaloca_matriz(&m);
            }
            break;
        case 4:
            printf("\n\n=== Somar duas Matrizes.   ===\n\n");
            index1 = escolhaIndex("Index da primeira matriz: ") - 1;
            index2 = escolhaIndex("Index da segunda matriz: ") - 1;
            Matriz_esparsa m1;
            Matriz_esparsa m2;
            isLeituraUmValida = le_valor(matrizes, &m1, index1);
            isLeituraDoisValida = le_valor(matrizes, &m2, index2);
            if (valida_leitura(isLeituraUmValida) && valida_leitura(isLeituraDoisValida))
            {
                m = soma_matrizes(m1, m2);
                insere_fim(&matrizes, &m);
                desaloca_matriz(&m1);
                desaloca_matriz(&m2);
            }
            break;
        case 5:
            index = escolhaIndex("\n\n===   Remover Matriz   ===\n\nEscolha o index da matriz: ");
            isLeituraValida = le_valor(matrizes, &m, index);
            if (valida_leitura(isLeituraValida)){
                desaloca_matriz(&m);
                modifica_valor(matrizes, &m, index);
                remove_pos(&matrizes, &m, index);
            }
            break;
        default:
            printf("Saindo...\n");
            break;
        }
    } while (escolha != 0);
    return 0;
}

Matriz_esparsa new_matriz (){
    Matriz_esparsa matriz;
    inicializa_matriz(&matriz);
    return matriz;
}

