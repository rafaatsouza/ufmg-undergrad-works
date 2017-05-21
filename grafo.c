#include "grafo.h"
#include "fila.h"

grafo* criaGrafoVazio(int qtdVertices){
    int i, j;
    grafo *g;

    g = (grafo*)malloc(sizeof(grafo));

    g->qtdVertices = qtdVertices;
    g->qtdArestas = 0;

    g->g = (int**)malloc(sizeof(int*) * qtdVertices);
    g->adj = (int**)malloc(sizeof(int*) * qtdVertices);
    for(i=0;i<g->qtdVertices;i++){
        g->g[i] = (int*)malloc(sizeof(int) * qtdVertices);
        g->adj[i] = (int*)malloc(sizeof(int) * qtdVertices);
        for(j=0;j<g->qtdVertices;j++){
            g->g[i][j] = 0;
            g->adj[i][j] = 0;
        }
    }
    return g;
}

void removeAresta(grafo *g, int index, int destino){
    int i, parada;
    for (i = 0; i < g->qtdVertices; i++) {
        if(g->adj[index][i] == destino){
            g->adj[index][i] = 0;
            parada = i;
        }
    }
    for(i = parada; i < g->qtdVertices - 1; i++){
        if(g->adj[index][i+1] != 0){
            g->adj[index][i] = g->adj[index][i+1];
        } else { break; }
    }
    g->qtdArestas = g->qtdArestas - 1;
}

void InsereAresta(grafo *g, int indexOrigem, int indexDestino, int qtdCiclistas){
    int i;
    g->g[indexOrigem][indexDestino] = qtdCiclistas;
    g->qtdArestas = g->qtdArestas + 1;

    for (i = 0; i < g->qtdVertices; i++) {
        if(g->adj[indexOrigem][i] == 0){
            g->adj[indexOrigem][i] = indexDestino;
            break;
        }
    }
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
    int i, j, aux, *cor, *distancia_bfs, qtd_adj;

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

        i = 0;
        while(g->adj[aux][i] != 0){
            if(cor[g->adj[aux][i]] == 0 && g->g[aux][g->adj[aux][i]] > 0){
                cor[g->adj[aux][i]] = 1;
                distancia_bfs[g->adj[aux][i]] = distancia_bfs[aux] + 1;
                arrayCaminho[g->adj[aux][i]] = aux;
                enfileira(fv, g->adj[aux][i]);
            }
            i++;
        }
        cor[aux] = 2;
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
    int aux, fluxo, fluxo_max = 0, origem = 0, destino = g->qtdVertices - 1, *arrayCaminho;

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
            if(g->g[arrayCaminho[aux]][aux] + fluxo > 0 && g->g[arrayCaminho[aux]][aux] <= 0){
                removeAresta(g, arrayCaminho[aux], aux);
            }
            g->g[aux][arrayCaminho[aux]] += fluxo;
            if(g->g[aux][arrayCaminho[aux]] - fluxo <= 0 && g->g[aux][arrayCaminho[aux]] > 0){
                InsereAresta(g, aux, arrayCaminho[aux], g->g[aux][arrayCaminho[aux]]);
            }
            aux = arrayCaminho[aux];
        }
        fluxo_max += fluxo;
    }

    free(arrayCaminho);
    return fluxo_max;
}

void liberaGrafo(grafo *g){
    int i;
    for(i=0;i<g->qtdVertices;i++){
        free(g->g[i]);
        free(g->adj[i]);
    }
    free(g->g);
    free(g->adj);
    free(g);
}
