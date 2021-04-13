#include <stdlib.h>
#include <stdio.h>
#include "Utilitarios.h"

Matriz_esparsa new_matriz ();

int main (){
    Lista matrizes;
    inicializa_lista(&matrizes, sizeof(Matriz_esparsa));
    int escolha = 0, index = 0, index1 = 0, index2 = 0, isLeituraValida = 0, isLeituraUmValida, isLeituraDoisValida;

    do
    {
        menuTexto();
        escolha = escolhaMenu();
        switch (escolha)
        {
        case 1: ;
            Matriz_esparsa m;
            m = new_matriz();
            insere_fim(&matrizes, &m);
            printf("Nova matriz esparsa criada, Index: %d", tamanho_lista(matrizes));
            break;
        case 2: ;
            Matriz_esparsa matriz_imprimir;
            matriz_imprimir = new_matriz();
            index = escolhaIndex("\n\n===   Mostrar dados de uma Matriz.   ===\n\nEscolha o index da matriz: ");
            isLeituraValida = le_valor(matrizes, &matriz_imprimir, index - 1);
            if(valida_leitura(isLeituraValida))
                imprimi_matriz(matriz_imprimir);
                // desaloca_matriz(&m);
            break;
        case 3: ;
            Matriz_esparsa matriz_adcionar;
            matriz_adcionar = new_matriz();
            index = escolhaIndex("\n\n===   Modificar dados de uma Matriz.   ===\n\nInsera 0 para excluir valor\nEscolha o index da matriz: ") - 1;
            isLeituraValida = le_valor(matrizes, &matriz_adcionar, index);
            if (valida_leitura(isLeituraValida)){
                int l = escolhaIndex("Linha: ");
                int c = escolhaIndex("Coluna: ") ;
                int value = setNumero("Valor Inteiro: ");
                insere_valor(&matriz_adcionar, l, c, value);
                modifica_valor(matrizes, &matriz_adcionar, index);
                //desaloca_matriz(&matriz_adcionar);
            }
            break;
        case 4: ;
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
        case 5: ;
            Matriz_esparsa matriz_desaloca;
            matriz_desaloca = new_matriz();
            index = escolhaIndex("\n\n===   Remover Matriz   ===\n\nEscolha o index da matriz: ") - 1;
            isLeituraValida = le_valor(matrizes, &matriz_desaloca, index);
            if (valida_leitura(isLeituraValida)){
                desaloca_matriz(&matriz_desaloca);
                modifica_valor(matrizes, &matriz_desaloca, index);
                remove_pos(&matrizes, &matriz_desaloca, index);
            }
            break;
        default: ;
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

