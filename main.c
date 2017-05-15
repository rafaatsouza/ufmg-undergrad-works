#include <stdio.h>
#include "grafo.h"

// void printaTudo(grafo *g){
//     int i;
//     printf("----DADOS:\n");
//     printf("Qtd Vertices: %d Qtd Arestas: %d\n", g->qtdVertices, g->qtdArestas);
//
//     for(i = 0; i < g->qtdArestas; i++){
//         printf("Index %d vai do vertice %d ao vertice %d, comporta no max %d ciclistas.\n", i, g->a[i].indexOrigem, g->a[i].indexDestino, g->a[i].qtdMaxCiclistas);
//     }
// }

int main(){
    int QtdIntersecoes, QtdCiclofaixas, QtdIntersecoesComFranquias, QtdIntersecoesComClientes;

    scanf("%d %d %d %d", &QtdIntersecoes, &QtdCiclofaixas, &QtdIntersecoesComFranquias, &QtdIntersecoesComClientes);
    getchar();

    if(QtdIntersecoes < 2 || QtdCiclofaixas < 1 || QtdIntersecoesComFranquias < 1 || QtdIntersecoesComClientes < 1){
        fprintf(stderr, "Entrada invalida\n");
        exit(-1);
    }

    grafo *grafoMapa = criaGrafoVazio(QtdIntersecoes);
    int indexOrigem, indexDestino, qtdCiclistas, i;
    for(i = 0; i < QtdCiclofaixas; i++){
        scanf("%d %d %d", &indexOrigem, &indexDestino, &qtdCiclistas);
        getchar();
        if(existeVertice(grafoMapa, indexOrigem) == 0){
            InsereVertice(grafoMapa, indexOrigem);
        }
        if(existeVertice(grafoMapa, indexDestino) == 0){
            InsereVertice(grafoMapa, indexDestino);
        }
        InsereAresta(grafoMapa, indexOrigem, indexDestino, qtdCiclistas);
    }
    for(i = 0; i < QtdIntersecoesComFranquias; i++){
        scanf("%d", &indexOrigem);
        getchar();
        DefineComFranquia(grafoMapa, indexOrigem);
    }
    for(i = 0; i < QtdIntersecoesComClientes; i++){
        scanf("%d", &indexOrigem);
        getchar();
        DefineComCliente(grafoMapa, indexOrigem);
    }
}
