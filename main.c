#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Funcoes/Ordena.h"

int main(){
    srand((unsigned)time(NULL));

    printf("Informe a quantidade de elementos no vetor à ser ordenado: ");
    int tamanho;
    scanf("%d",&tamanho);

    if(tamanho <= 0){
        fprintf(stderr, "Tamanho inválido.\n");
        exit(-1);
    }

    vetor *v = criaVetor(1,99,tamanho);
    int fim = 0;

    while(fim == 0){
        system("clear");
        imprimeVetor(v);
        defineOrdenado(v);
        printf("Informe o tipo de ordenacao desejado: \n1 - Bolha\n2 - Seleção\n3 - Inserção\n4 - ShellSort\n5 - QuickSort\n6 - HeapSort\n7 - MergeSort\n8 - RadixSort\n");
        int ordenacao;
        scanf("%d",&ordenacao);
        switch (ordenacao) {
            case 1:
                ordenaBolha(v);
                imprimeVetor(v);
                defineOrdenado(v);
                fim = 1;
            break;
            case 2:
                ordenaSelecao(v);
                imprimeVetor(v);
                defineOrdenado(v);
                fim = 1;
            break;
            case 3:
                ordenaInsercao(v);
                imprimeVetor(v);
                defineOrdenado(v);
                fim = 1;
            break;
            case 4:
                ordenaShellsort(v);
                imprimeVetor(v);
                defineOrdenado(v);
                fim = 1;
            break;
            case 5:
                ordenaQuicksort(v,0,v->tamanho-1);
                imprimeVetor(v);
                defineOrdenado(v);
                fim = 1;
            break;
            case 6:
                system("clear");
                printf("Heapsort ainda nao implementado.\n");
            break;
            case 7:
                ordenaMergesort(v,0,v->tamanho-1);
                imprimeVetor(v);
                defineOrdenado(v);
                fim = 1;
            break;
            case 8:
                ordenaRadixsort(v);
                imprimeVetor(v);
                defineOrdenado(v);
                fim = 1;
            break;
        }
    }

    free(v->v);
    free(v);
    return 0;
}
