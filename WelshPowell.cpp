// INCLUDES:
#include <stdio.h>
#include <stdlib.h>

// GRAPH DECLARATION:
int vertexNum; // Número de vértices do Grafo.
int **graph; // Grafo.
int **Table; // Tabela para execução do algoritmo.

// FUNÇÕES DO PROGRAMA:
int **readGraph(int size){ // Função que lê o grafo do arquivo <graph.in>:
    int **matrix = (int**)malloc((size)*sizeof(int*));
    for(int line = 0; line < size; line++){
        matrix[line] = (int*)malloc((size)*sizeof(int));
        for(int col = 0; col < size; col++){
            scanf("%d", &matrix[line][col]);
        }
    }
    return matrix;
}

void printGraph(int size){ // Função que printa o Grafo:
    printf("\n  Impressao da Matriz de Adjacencia do Grafo de Entrada:\n");
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
    return;
}

int **createTable(int lines, int cols){ // Função que cria a tabela de controle do algoritmo:
    int **matrix = (int**)malloc((lines)*sizeof(int*));
    for(int line = 0; line < lines; line++){
        matrix[line] = (int*)malloc((cols)*sizeof(int));
    }
    for(int line = 0; line < lines; line++){
        for(int col = 0; col < cols; col++){
            matrix[line][col] = 0;
        }
    }
    return matrix;
}

void printTable(int **table){ // Função que printa a Tabela:
    printf("\n  Impressao da Tabela de Controle do algoritmo:\n");
    printf("     #|");
    for(int col = 0; col < vertexNum; col++){
        printf("%3c|", col+65);
    }
    printf("\n  Grau|");
    for(int col = 0; col < vertexNum; col++){
        printf("%3d|", Table[0][col]);
    }
    printf("\n   Cor|");
    for(int col = 0; col < vertexNum; col++){
        printf("%3d|", Table[1][col]);
    }
    return;
}

int isNeighbor(int fromVertex, int toVertex){ // Função que verifica se dois vértices são vizinhos:
    return graph[fromVertex][toVertex];
}

void setNeighbors(){ // Função que preenche a tabela com o grau dos vértices:
    int line = 0;
    int col= 0;
    for(line = 0; line < vertexNum; line++){
        int neighbors = 0;
        for(col = 0; col < vertexNum; col++){
            if(isNeighbor(line, col)){
                neighbors++;
            }
        }
        Table[0][line] = neighbors;
    }
}

void setColors(){ // Função que preenche as cores da tabela com -1:
    for(int col = 0; col < vertexNum; col++){
        Table[1][col] = -1;
    }
}

int findBiggerNotColored(){ // Função que retorna o vértice ainda não visitado com o maior grau:
    int value = -1;
    int bigger = -1;
    for(int col = 0; col < vertexNum; col++){
        if((Table[1][col] < 0) && (Table[0][col] > value)){
            value = Table[0][col];
            bigger = col;
        }
    }
    return bigger;
}

int checkNeighborsColor(int vertex, int color){ // Função que verifica se algum vizinho já possui a cor desejada:
    for(int col = 0; col < vertexNum; col++){
        if(graph[vertex][col] > 0 && Table[1][col] == color){
            return 0; // O vértice já possui um vizinho da cor desejada.
        }
    }
    return 1; // O vértice não possui nenhum vizinho da cor desejada.
}

int checkEnd(){ // Função que verifica se todos os vértices já possuem cor:
    for(int col = 0; col < vertexNum; col++){
        if(Table[1][col] < 0){
            return 1;
        }
    }
    return 0;
}

void runWelshPowell(int *vector){ // Função que executa o WelshPowell:
    int actualColor = 0;
    while(checkEnd()){
        for(int i = 0; i < vertexNum; i++){
            int nextVertex = vector[i];
            if(checkNeighborsColor(nextVertex, actualColor) && Table[1][nextVertex] == -1){
                Table[1][nextVertex] = actualColor;
                printf("  Vertice %c pintado com a cor %d;\n", nextVertex+65, actualColor);
            }
        }
        actualColor++;
    }
    return;
}

// MAIN FUNCTION:
int main(int argc, char const *argv[]) {
    // Lendo a quantidade de Vértices do Grafo:
    scanf("%d", &vertexNum);
    // Lendo o Grafo:
    graph =  readGraph(vertexNum);
    // Printando o Grafo instanciado:
    printGraph(vertexNum);
    // Criando a Tabela Original:
    Table = createTable(2, vertexNum);
    // Preenchendo a Tabela com o Grau dos Vértices:
    setNeighbors();
    // Preenchendo as Cores da Tabela com -1 para todos os Vértices:
    setColors();
    // Criando o Vetor de Vértices Ordenados pelo Grau:
    int ordenedVector[11];
    for(int i = 0; i < vertexNum; i++){
        int nextVertex = findBiggerNotColored();
        ordenedVector[i] = nextVertex;
        Table[1][nextVertex] = 1;
    }
    printf("\n  Impressao do Vetor de Vertices Ordenados pelo Grau:\n");
    printf("     #|");
    for(int col = 0; col < vertexNum; col++){
        printf("%3d|", ordenedVector[col]);
    }
    printf("\n\n");
    // Preenchendo as Cores da Tabela com -1 para todos os Vértices:
    setColors();
    // Executnado o WelshPowell:
    runWelshPowell(ordenedVector);
    // Printando a Tabela Original:
    printTable(Table);
    return 0;
}
