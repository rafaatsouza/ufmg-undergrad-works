#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Funcoes/Ordena.h"

int main(){
    srand((unsigned)time(NULL));
    vetor *v = criaVetor(1,10,10);
    int fim = 0;

    while(fim == 0){
        imprimeVetor(v);
        defineOrdenado(v);
        printf("Informe o tipo de ordenacao desejado: \n1 - Bolha\n2 -Seleção\n3 -Inserção\n4 -ShellSort\n5 -QuickSort\n6 -HeapSort\n7 -MergeSort\n8 -RadixSort\n");
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
                system("clear");
                printf("Ainda nao implementado.\n");
            break;
            case 6:
                system("clear");
                printf("Ainda nao implementado.\n");
            break;
            case 7:
                ordenaMergesort(v,0,v->tamanho-1);
                imprimeVetor(v);
                defineOrdenado(v);
                fim = 1;
            break;
            case 8:
                system("clear");
                printf("Ainda nao implementado.\n");
            break;
            default:
            system("clear");
            printf("Informe o tipo de ordenacao desejado: \n1 - Bolha\n2 -Seleção\n3 -Inserção\n4 -ShellSort\n4 -QuickSort\n5 -HeapSort\n6 -MergeSort\n7 -RadixSort\n");
            break;
        }
    }
    return 0;
}
