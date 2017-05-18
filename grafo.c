#include "grafo.h"
#include "fila.h"

grafo* criaGrafoVazio(int qtdVertices){
    int i, qtdMaxArestas;
    grafo *g = (grafo*)malloc(sizeof(grafo));

    qtdMaxArestas = (qtdVertices * (qtdVertices - 1))/2;

    g->qtdVertices = qtdVertices;
    g->qtdArestas = 0;
    g->v = (vertice*)malloc(sizeof(vertice) * (qtdVertices));
    g->a = (aresta*)malloc(sizeof(aresta) * qtdMaxArestas);

    for(i=0;i<g->qtdVertices;i++){
        g->v[i].possuiCliente = 0;
        g->v[i].possuiFranquia = 0;
    }

    return g;
}

void printaTudo(grafo *g){
    int i;
    printf("----DADOS:\n");
    printf("Qtd Vertices: %d Qtd Arestas: %d\n", g->qtdVertices, g->qtdArestas);

    for(i = 0; i < g->qtdArestas; i++){
        printf("Index %d vai do vertice %d ao vertice %d, comporta no max %d ciclistas.\n", i, g->a[i].indexOrigem, g->a[i].indexDestino, g->a[i].qtdMaxCiclistas);
    }
    printf("-----------------\n");
}

void InsereAresta(grafo *g, int indexOrigem, int indexDestino, int qtdCiclistas){
    g->a[g->qtdArestas].indexOrigem = indexOrigem;
    g->a[g->qtdArestas].indexDestino = indexDestino;
    g->a[g->qtdArestas].qtdMaxCiclistas = qtdCiclistas;
    g->qtdArestas++;
}

void DefineComFranquia(grafo *g, int index){
    g->v[index].possuiFranquia = 1;
}

void DefineComCliente(grafo *g, int index){
    g->v[index].possuiCliente = 1;
}

int* retornaVerticesQueVao(grafo *g, int index, int *qtdVerticesDest){ //retorna um vetor com index de todos os vertices que tem uma aresta indo ao vertice de index informado
    int i, *retorno;
    *qtdVerticesDest = 0;
    for(i=0;i<g->qtdArestas;i++){
        if(g->a[i].indexDestino == index) {
            *qtdVerticesDest = *qtdVerticesDest + 1;
        }
    }

    retorno = (int*)malloc(sizeof(int) * (*qtdVerticesDest));
    *qtdVerticesDest = 0;

    for(i=0;i<g->qtdArestas;i++){
        if(g->a[i].indexDestino == index) {
            retorno[*qtdVerticesDest] = g->a[i].indexOrigem;
            *qtdVerticesDest = *qtdVerticesDest + 1;
        }
    }
    return retorno;
}

int retornaIndexFranquiaMaisProx(grafo *g, int indexVertice){
    int i, aux, qtdVerticesDest, *VerticesDest, indexFranquia = -1;

    for(i=0;i<g->qtdVertices;i++){
        g->v[i].cor = 0;
        g->v[i].distancia_bfs = 0;
    }
    g->v[indexVertice].distancia_bfs = 1;

    filaNumeros *fv = criaFilaVazia(g->qtdVertices);
    enfileira(fv, indexVertice);

    while(filaVazia(fv) == 0 && indexFranquia == -1){
        aux = desenfileira(fv);
        VerticesDest = retornaVerticesQueVao(g, aux, &qtdVerticesDest);
        for(i=0;i<qtdVerticesDest;i++){
            if(g->v[VerticesDest[i]].cor == 0){
                g->v[VerticesDest[i]].cor = 1;
                g->v[VerticesDest[i]].distancia_bfs = g->v[aux].distancia_bfs + 1;
                enfileira(fv, VerticesDest[i]);
                if(g->v[VerticesDest[i]].possuiFranquia == 1 && indexFranquia == -1){ //eh a franquia mais prox
                    indexFranquia = VerticesDest[i];
                }
            }
            g->v[aux].cor = 2;
        }
        free(VerticesDest);
    }

    liberaFila(fv);
    return indexFranquia;
}

void liberaGrafo(grafo *g){
    free(g->a);
    free(g->v);
    free(g);
}
