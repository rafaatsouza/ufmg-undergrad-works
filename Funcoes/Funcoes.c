#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Funcoes.h"

//retorna um numero aleatorio nos intervalos definidos
int retornaAleatorio(int min, int max){
    return min + (rand()%max);
}

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
