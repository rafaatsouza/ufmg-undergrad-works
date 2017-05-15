#include "grafo.h"

grafo* criaGrafoVazio(int qtdVertices){
    int i, qtdMaxArestas;
    grafo *g = (grafo*)malloc(sizeof(grafo));

    qtdMaxArestas = (qtdVertices * (qtdVertices - 1))/2;

    g->qtdVertices = qtdVertices;
    g->qtdArestas = 0;
    g->v = (vertice*)malloc(sizeof(vertice) * (qtdVertices));
    g->a = (aresta*)malloc(sizeof(aresta) * qtdMaxArestas);

    for(i = 0; i < qtdVertices; i++){
        g->v[i].index = -1;
    }
    return g;
}

int existeVertice(grafo *g, int index){
    int i;
    for (int i = 0; i < g->qtdVertices; i++) {
        if(index >= 0 && g->v[i].index == index){
            return 1;
        }
    }
    return 0;
}

void InsereVertice(grafo *g, int index){
    g->v[index].index = index;
    g->v[index].possuiCliente = 0;
    g->v[index].possuiFranquia = 0;
}

void InsereAresta(grafo *g, int indexOrigem, int indexDestino, int qtdCiclistas){
    g->a[g->qtdArestas].indexOrigem = indexOrigem;
    g->a[g->qtdArestas].indexDestino = indexDestino;
    g->a[g->qtdArestas].qtdMaxCiclistas = qtdCiclistas;
    g->qtdArestas++;
}
void DefineComFranquia(grafo *g, int indexOrigem){
    g->v[indexOrigem].possuiFranquia = 1;
}
void DefineComCliente(grafo *g, int indexOrigem){
    g->v[indexOrigem].possuiCliente = 1;
}
