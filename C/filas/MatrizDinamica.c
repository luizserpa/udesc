#include "MatrizDinamica.h"
#include <stdlib.h>
#include <stdio.h>

void inicializa_matriz( MatrizDinamica *p, int l, int c ){
	p->linhas = l;
	p->colunas = c;
	
	p->dados = malloc( sizeof(int*) * l );
	int i, j;
	for( i = 0 ; i < l ; i++ ){
		p->dados[i] = calloc( c, sizeof(int) );
	}
}

void mostra_matriz( MatrizDinamica m ){
	int i, j;
	
	printf("Menor caminho(11) da matriz (%dx%d):\n", m.linhas, m.colunas);
	for( i = 0 ; i < m.linhas; i++ ){
		for( j = 0; j < m.colunas ; j++ )
			printf("%4d", m.dados[i][j]);
		printf("\n");
	}
	printf("\n");
}

void desaloca_matriz( MatrizDinamica *p ){
	int i;
	for( i = 0 ; i < p->linhas ; i++ )
		free( p->dados[i] );
		
	free( p->dados );
}

int modifica_matriz( MatrizDinamica *p, int lin, int col, int valor){
	if( lin >= p->linhas || col > p->colunas || lin < 0 || col < 0 )
		return ERRO_COORDENADA_INVALIDA;
		
	p->dados[lin][col] = valor;
	return 1;
}

int compara_matrizes( MatrizDinamica a, MatrizDinamica b ){
	if( a.linhas != b.linhas || a.colunas != b.colunas )
		return 0; 
	
	int i, j;
	for( i = 0 ; i < a.linhas; i++ )
		for( j = 0; j < a.colunas ; j++ )
			if( a.dados[i][j] != b.dados[i][j] )
				return 0; 
	
	return 1;
}


void dimencoes_matriz(MatrizDinamica m, int *c, int *l){
	*c = m.colunas;
	*l = m.linhas;
}

int pegar_valor_matriz(MatrizDinamica m, int x, int y){
	return m.dados[y][x];
}

