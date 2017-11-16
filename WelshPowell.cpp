// INCLUDES:
#include <stdio.h>
#include <stdlib.h>

// GRAPH DECLARATION:
int vertexNum;
int **graph;

// FUNÇÕES DO PROGRAMA:
int **readGraph(int size){ // Função que lê o grafo do arquivo <graph.in>:
    int **matrix = (int**)malloc((size)*sizeof(int*));
    for(int col = 0; col < size; col++){
        matrix[col] = (int*)malloc((size)*sizeof(int));
        for(int line = 0; line < size; line++){
            scanf("%d", &matrix[col][line]);
        }
    }
    return matrix;
}

void printGraph(int size){ // Função que printa o Grafo:
    printf("\n  Impressão da Matriz de Adjacência do Grafo de Entrada:\n");
    printf("  #|");
    for(int col = 1; col <= vertexNum; col++){
        printf("%3c|", col+64);
    }
    printf("\n");
    for(int line = 0; line < vertexNum; line++){
		printf("%3c|", line+65);
		for(int col = 0; col < vertexNum; col++){
			printf("%3d|", graph[line][col]);
		}
		printf("\n");
	}
	printf("\n");
}

// MAIN FUNCTION:
int main(int argc, char const *argv[]) {
    // Lendo a quantidade de Vértices do Grafo:
    scanf("%d", &vertexNum);
    // Lendo o Grafo:
    graph =  readGraph(vertexNum);
    // Printando o Grafo instanciado:
    printGraph(vertexNum);
    return 0;
}
