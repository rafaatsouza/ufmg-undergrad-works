#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Funcoes.h"

int retornaAleatorio(int min, int max){
    return min + (rand()%max);
}

vetor* retornaVetor(int min, int max, int tamanho){
    int i;
    vetor *v = (vetor*)malloc(sizeof(vetor));

    v->tamanho = tamanho;
    v->v = (int*)malloc(sizeof(int) * tamanho);

    for(i=0;i<tamanho;i++){
        v->v[i] = retornaAleatorio(min,max);
    }
    return v;
}
