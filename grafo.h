typedef struct gr {
    int **g, qtdVertices, qtdArestas;
} grafo;

grafo* criaGrafoVazio();
void printaTudo(grafo *g);
void InsereAresta(grafo *g, int indexOrigem, int indexDestino, int qtdCiclistas);
void liberaGrafo(grafo *g);
