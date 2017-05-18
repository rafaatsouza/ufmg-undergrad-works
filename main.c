#include <stdio.h>
#include "grafo.h"

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

    printaTudo(grafoMapa);
}
