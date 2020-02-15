#include <stdio.h>
#include <time.h>
#include "Funcoes/Ordena.h"

int main(int argc, char *argv[]){
    if(argc < 4){
        fprintf(stderr, "Parametros invalidos.\n");
        exit(-1);
    }

    if(strlen(argv[1]) < 3){
        fprintf(stderr, "Tipo de ordenacao invalida.\n");
        exit(-1);
    }

    if(strlen(argv[3]) < 3){
        fprintf(stderr, "Ordenacao inicial invalida.\n");
        exit(-1);
    }

    if(atoi(argv[2]) <= 0){
        fprintf(stderr, "Tamanho invalido.\n");
        exit(-1);
    }

    vetor *v;
    if(strcmp(argv[3],"asc") == 0){
        v = criaVetorOrdenado(atoi(argv[2]),0);
    } else if(strcmp(argv[3],"desc") == 0){
        v = criaVetorOrdenado(atoi(argv[2]),1);
    } else if(strcmp(argv[3],"ale") == 0){
        v = criaVetorAleatorio(1, 99, atoi(argv[2]));
    } else if(strcmp(argv[3],"qasc") == 0){
        v = criaVetorQuaseAleatorio(1, 99, atoi(argv[2]));
    } else {
        fprintf(stderr, "Ordenacao inicial invalida.\n");
        exit(-1);
    }

    clock_t tempo_exec;

    if(argc >= 5){
        if(strcmp(argv[4],"-P") == 0){
            defineOrdenado(v);
            imprimeVetor(v);
        }
    }

    int movimentacoes = 0, comparacoes = 0;

    if(strcmp(argv[1],"bol") == 0){
        printf("Ordenacao escolhida: BubbleSort.\n");
        tempo_exec = clock();
        movimentacoes = ordenaBolha(v, &comparacoes);
        tempo_exec = clock() - tempo_exec;
    } else if(strcmp(argv[1],"sel") == 0){
        printf("Ordenacao escolhida: Selecao.\n");
        tempo_exec = clock();
        movimentacoes = ordenaSelecao(v, &comparacoes);
        tempo_exec = clock() - tempo_exec;
    } else if(strcmp(argv[1],"ins") == 0){
        printf("Ordenacao escolhida: Insercao.\n");
        tempo_exec = clock();
        movimentacoes = ordenaInsercao(v, &comparacoes);
        tempo_exec = clock() - tempo_exec;
    } else if(strcmp(argv[1],"she") == 0){
        printf("Ordenacao escolhida: ShellSort.\n");
        tempo_exec = clock();
        movimentacoes = ordenaShellsort(v, &comparacoes);
        tempo_exec = clock() - tempo_exec;
    } else if(strcmp(argv[1],"qui") == 0){
        printf("Ordenacao escolhida: QuickSort.\n");
        tempo_exec = clock();
        ordenaQuicksort(v,0,v->tamanho-1, &movimentacoes, &comparacoes);
        tempo_exec = clock() - tempo_exec;
    } else if(strcmp(argv[1],"hea") == 0){
        printf("Ordenacao escolhida: HeapSort.\n");
        tempo_exec = clock();
        movimentacoes = ordenaHeapSort(v, &comparacoes);
        tempo_exec = clock() - tempo_exec;
    } else if(strcmp(argv[1],"mer") == 0){
        printf("Ordenacao escolhida: MergeSort.\n");
        tempo_exec = clock();
        ordenaMergesort(v->v,v->tamanho, &movimentacoes, &comparacoes);
        tempo_exec = clock() - tempo_exec;
    } else if(strcmp(argv[1],"rad") == 0){
        printf("Ordenacao escolhida: RadixSort.\n");
        tempo_exec = clock();
        movimentacoes = ordenaRadixsort(v);
        tempo_exec = clock() - tempo_exec;
    } else {
        fprintf(stderr, "Ordenacao invalida.\n");
        free(v->v);
        free(v);
        exit(-1);
    }

    if(argc >= 5){
        if(strcmp(argv[4],"-P") == 0){
            defineOrdenado(v);
            imprimeVetor(v);
        }
    }
    printf("Movimentacoes: %d\n", movimentacoes);
    printf("Comparacoes: %d\n", comparacoes);
    printf("Tempo gasto: %f segundos\n", ((double)tempo_exec)/CLOCKS_PER_SEC);

    free(v->v);
    free(v);
    return 0;
}
