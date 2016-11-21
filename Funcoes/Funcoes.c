#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Funcoes.h"

//informa se o vetor está ordenado ou não
void defineOrdenado(vetor *v){
    int i;
    for(i=0;i<v->tamanho;i++){
        if(i != 0){
            if(v->v[i] < v->v[i-1]){
                printf("Vetor nao esta ordenado.\n");
                return;
            }
        }
    }
    printf("Vetor esta ordenado.\n");
}

//retorna um numero aleatorio nos intervalos definidos
int retornaAleatorio(int min, int max){
    return min + (rand()%max);
}

//cria uma nova variável do tipo vetor
vetor* criaVetor(int min, int max, int tamanho){
    int i;
    vetor *v = (vetor*)malloc(sizeof(vetor));

    v->tamanho = tamanho;
    v->v = (int*)malloc(sizeof(int) * tamanho);

    for(i=0;i<tamanho;i++){
        v->v[i] = retornaAleatorio(min,max);
    }
    return v;
}

//imprime todos os elementos de um vetor
void imprimeVetor(vetor *v){
    int i;
    for(i=0;i<v->tamanho;i++){
        printf("%d\n", v->v[i]);
    }
}

//ordena vetor por método seleção
void ordenaSelecao(vetor *v){
    int i, j, Min, x;
    for (i=0;i<v->tamanho;i++){
        Min = i;
        for (j=i+1;j<v->tamanho;j++)
            if (v->v[j] < v->v[Min])
                Min = j;
        x = v->v[Min];
        v->v[Min] = v->v[i];
        v->v[i] = x;
    }
}

//ordena vetor por método bolha
void ordenaBolha(vetor *v){
    int i, j, x;
    for (i=0;i<= v->tamanho;i++){
        for (j=0;j<=(v->tamanho-i);j++){
            if (v->v[j] > v->v[j+1]){
                x = v->v[j];
                v->v[j] = v->v[j+1];
                v->v[j+1] = x;
            }
        }
    }
}
