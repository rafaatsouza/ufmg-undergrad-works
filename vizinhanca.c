#include <stdio.h>
#include <stdlib.h>
#include "vizinhanca.h"

int retornaMax(int *v, int tamanho){
    int i, max;
    for(i=0;i<tamanho;i++){
        if(i==0){
            max = v[i];
        } else if(v[i] > max) {
            max = v[i];
        }
    }
    return max;
}

void ordenaRadixsort(int *v, int tamanho) {
    int i, digito = 1, aux[tamanho], maior = retornaMax(v, tamanho);

    while (maior / digito > 0){
        int bucket[10] = { 0 };
        for (i = 0; i < tamanho; i++) { bucket[(v[i] / digito) % 10]++; }
        for (i = 1; i < 10; i++) { bucket[i] += bucket[i - 1]; }
        for (i = tamanho - 1; i >= 0; i--){ aux[--bucket[(v[i] / digito) % 10]] = v[i]; }
        for (i = 0; i < tamanho; i++){ v[i] = aux[i]; }
        digito *= 10;
    }
}

vizinhanca* instanciaVizinhanca(int qtdBar){
    vizinhanca *v = (vizinhanca*)malloc(sizeof(vizinhanca));

    v->qtdBar = qtdBar;
    v->r = (relacao*)malloc(sizeof(relacao) * qtdBar);
    v->bares = (int*)malloc(sizeof(int) * qtdBar);
    v->casas = (int*)malloc(sizeof(int) * qtdBar);

    return v;
}

void preencheVizinhanca(vizinhanca *v){
    int i, bar, casa;

    for(i=0;i<v->qtdBar;i++){
        scanf("%d %d", &bar, &casa);
        v->r[i].bar = bar;
        v->r[i].casa = casa;
        v->bares[i] = bar;
        v->casas[i] = casa;
    }

    ordenaRadixsort(v->bares, v->qtdBar);
    ordenaRadixsort(v->casas, v->qtdBar);
}

void dinamica(vizinhanca *v){
    printf("%d bares - tipo dinamica\n", v->qtdBar);
}

void guloso(vizinhanca *v){
    printf("%d bares - tipo guloso\n", v->qtdBar);
}

void bruta(vizinhanca *v){
    printf("%d bares - tipo bruta\n", v->qtdBar);
}
