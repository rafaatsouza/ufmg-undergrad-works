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

int retornaNumDigitos(int n){
    int digitos = 0;
    while(n != 0){
        n /= 10;
        digitos++;
    }
    return digitos;
}

int retornaDigito(int n, int i){
    int digito;
    while(i > 0){
        digito = n % 10;
        n /= 10;
        i--;
    }
    return digito;
}
