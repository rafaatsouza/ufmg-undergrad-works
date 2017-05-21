typedef struct gr {
    int **g, **adj, qtdVertices, qtdArestas;
} grafo;

grafo* criaGrafoVazio();
void InsereAresta(grafo *g, int indexOrigem, int indexDestino, int qtdCiclistas);
void liberaGrafo(grafo *g);
