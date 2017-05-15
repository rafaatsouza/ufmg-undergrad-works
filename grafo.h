typedef struct v * t_ligacao;

typedef struct a {
    int indexOrigem, indexDestino, qtdMaxCiclistas;
} aresta;

typedef struct v {
    int index, possuiFranquia, possuiCliente;
} vertice;

typedef struct g {
    int qtdVertices, qtdArestas;
    vertice *v;
    aresta *a;
} grafo;


grafo* criaGrafoVazio();
int existeVertice(grafo *g, int index);
void InsereVertice(grafo *g, int index);
void InsereAresta(grafo *g, int indexOrigem, int indexDestino, int qtdCiclistas);
void DefineComFranquia(grafo *g, int indexOrigem);
void DefineComCliente(grafo *g, int indexOrigem);
