#include <stdio.h>
#include <stdlib.h>
#include "Funcoes.h"
#include "Ordena.h"

#define less(A, B) (A < B)

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
        printf("%d ", v->v[i]);
    }
    printf("\n");
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

//ordena vetor por método shellsort
void ordenaShellsort(vetor *v){
    int i, j, x, h = 1;
    do h = h * 3 + 1; while (h < v->tamanho);
    do{
        h /= 3;
        for (i = 0; i <= v->tamanho; i=i+h){
            x = v->v[i];
            j = i;
            while (v->v[j - h] >= x){
                v->v[j] = v->v[j - h];
                j -= h;
                if (j < h) break;
            }
            v->v[j] = x;
        }
    } while (h != 1);
}

void merge(vetor *v, int p, int q, int r){
    int i, j, k, *aux = (int*)malloc(sizeof(int) * (p+q));
    for (i = q+1; i > p; i--)
       aux[i-1] = v->v[i-1];
    for (j = q; j < r; j++)
       aux[r+q-j] = v->v[j+1];
    for (k = p; k <= r; k++)
       if (less(aux[j], aux[i])) v->v[k] = aux[j--];
       else v->v[k] = aux[i++];
}

//ordena vetor por método mergesort
void ordenaMergesort(vetor *v, int inicio, int final){
    if (inicio < final) {
       int q = (inicio + final) / 2;
       ordenaMergesort(v, inicio, q);
       ordenaMergesort(v, q+1, final);
       merge(v, inicio, q, final);
    }
}

//ordena vetor por método inserção
void ordenaInsercao(vetor *v){
    int j, i, x;
    for(j=1;j<v->tamanho;j++){
        x = v->v[j];
        i = j-1;
        while(i>=0 && v->v[i] > x){
            v->v[i+1] = v->v[i];
            i--;
        }
        v->v[i+1] = x;
    }
}

// void Radixsort(vetor *v, int n, int base, int num_digitos) {
//     int i, j, digito, max = retornaMax(v->v, v->tamanho), **tabela = (int**)malloc(sizeof(int*)), aux = (int*)malloc(sizeof(int)* v->tamanho);
//     int numDigitos = retornaNumDigitos(max);
//
//     for(i=0;i<10;i++){
//         tabela[i] = (int*)malloc(sizeof(int) * v->tamanho);
//     }
//
//     for(i=0;i<10;i++){
//         for(j=0;j<v->tamanho;j++){
//             tabela[i][j] = 0;
//         }
//     }
//
//     for(i=0;i<numDigitos;i++){
//         for(j=0;j<v->tamanho;j++){
//             digito = retornaDigito(v->v[j],i);
//         }
//     }
// }
