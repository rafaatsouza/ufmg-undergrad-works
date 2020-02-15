#include <stdio.h>
#include "fila.h"

filaNumeros* criaFilaVazia(int maxTam){
    filaNumeros *fv = (filaNumeros*)malloc(sizeof(filaNumeros));
    fv->v = (int*)malloc(sizeof(int) * (maxTam));
    fv->qtdNumeros = 0;
}

int filaVazia(filaNumeros *fv){
    if(fv->qtdNumeros > 0){
        return 0;
    } else {
        return 1;
    }
}

void enfileira(filaNumeros *fv, int v){
    fv->v[fv->qtdNumeros] = v;
    fv->qtdNumeros = fv->qtdNumeros + 1;
}

int desenfileira(filaNumeros *fv){
    int i;
    if(filaVazia(fv) != 1){
        int primeiro = fv->v[0];
        for(i=0;i<(fv->qtdNumeros)-1;i++){
            fv->v[i] = fv->v[i+1];
        }
        fv->qtdNumeros = fv->qtdNumeros - 1;
        return primeiro;
    } else {
        fprintf(stderr, "Erro - nao eh possivel desenfileirar de uma fila vazia.\n");
        exit(-1);
    }
}

void liberaFila(filaNumeros *fv){
    free(fv->v);
    free(fv);
}
