#include "grafo.h"
#include "fila.h"

grafo* criaGrafoVazio(int qtdVertices){
    int i, j;
    grafo *g;

    g = (grafo*)malloc(sizeof(grafo));

    g->qtdVertices = qtdVertices;
    g->qtdArestas = 0;

    g->g = (int**)malloc(sizeof(int*) * qtdVertices);
    for(i=0;i<g->qtdVertices;i++){
        g->g[i] = (int*)malloc(sizeof(int) * qtdVertices);
        for(j=0;j<g->qtdVertices;j++){
            g->g[i][j] = 0;
        }
    }
    return g;
}

void InsereAresta(grafo *g, int indexOrigem, int indexDestino, int qtdCiclistas){
    g->g[indexOrigem][indexDestino] = qtdCiclistas;
    g->qtdArestas++;
}

int* retornaAdj(grafo *g, int vertice, int *qtdAdj){ //retorna quantidade de vertices adjacentes um vertice informado possui
    int i, *retorno;
    *qtdAdj = 0;

    for(i=0;i<g->qtdVertices;i++){
        if(g->g[vertice][i] != -1){
            *qtdAdj = *qtdAdj + 1;
        }
    }

    retorno = (int*)malloc(sizeof(int) * (*qtdAdj));
    *qtdAdj = 0;

    for(i=0;i<g->qtdVertices;i++){
        if(g->g[vertice][i] != -1){
            retorno[*qtdAdj] = i;
            *qtdAdj = *qtdAdj + 1;
        }
    }

    return retorno;
}

int existeCaminho(grafo *g, int origem, int destino, int *arrayCaminho){ //retorna 1 caso exista caminho entre dois vertices informados, e 0 caso não exista.
    int i, j, aux, *cor, *distancia_bfs, qtd_adj, *adj;

    cor = (int*)malloc(sizeof(int) * g->qtdVertices);
    distancia_bfs = (int*)malloc(sizeof(int) * g->qtdVertices);

    for(i=0;i<g->qtdVertices;i++){
        cor[i] = 0;
        distancia_bfs[i] = -1;
    }
    distancia_bfs[origem] = 0;
    arrayCaminho[origem] = -1;

    filaNumeros *fv = criaFilaVazia(g->qtdVertices);
    enfileira(fv, origem);

    while(filaVazia(fv) == 0){
        aux = desenfileira(fv);
        adj = retornaAdj(g, aux, &(qtd_adj));

        for(i=0;i<qtd_adj;i++){
            if(cor[adj[i]] == 0 && g->g[aux][adj[i]] > 0){
                cor[adj[i]] = 1;
                distancia_bfs[adj[i]] = distancia_bfs[aux] + 1;
                arrayCaminho[adj[i]] = aux;
                enfileira(fv, adj[i]);
            }
            cor[aux] = 2;
        }
        free(adj);
    }

    liberaFila(fv);
    free(cor);

    if(distancia_bfs[destino] > 0){
        free(distancia_bfs);
        return 1;
    } else {
        free(distancia_bfs);
        return 0;
    }
}

int retornaFluxoMax(grafo *g){
    int i, j, aux, fluxo, fluxo_max = 0, origem = 0, destino = g->qtdVertices - 1, *arrayCaminho, **grafo_fluxo;

    arrayCaminho = (int*)malloc(sizeof(int) * (g->qtdVertices));

    while(existeCaminho(g, origem, destino, arrayCaminho) == 1){
        fluxo = 9999999;

        aux = destino;
        while(aux != origem){
            if(fluxo > g->g[arrayCaminho[aux]][aux]){
                fluxo = g->g[arrayCaminho[aux]][aux];
            }
            aux = arrayCaminho[aux];
        }

        aux = destino;
        while(aux != origem){
            g->g[arrayCaminho[aux]][aux] -= fluxo;
            g->g[aux][arrayCaminho[aux]] += fluxo;
            aux = arrayCaminho[aux];
        }
        fluxo_max += fluxo;
    }
    return fluxo_max;
}

void liberaGrafo(grafo *g){
    free(g->g);
    free(g);
}
