#include <stdio.h>
#include <time.h>
#include <stdlib.h>

typedef struct r {
    int bar, casa;
} relacao;

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

void dinamica(int qtdBar, relacao *BarCasa, int *bares, int *casas){
    printf("%d bares - tipo dinamica\n", qtdBar);
}

void guloso(int qtdBar, relacao *BarCasa, int *bares, int *casas){
    printf("%d bares - tipo guloso\n", qtdBar);
}

void bruta(int qtdBar, relacao *BarCasa, int *bares, int *casas){
    printf("%d bares - tipo bruta\n", qtdBar);
}

int main(int argc, char *argv[]){
    char tipoAlgoritmo;
    int qtdBar, *bares, *casas, bar, casa, i;
    relacao *BarCasa;

    tipoAlgoritmo = getchar();

    if(tipoAlgoritmo != 'd' && tipoAlgoritmo != 'g' && tipoAlgoritmo != 'b'){
        fprintf(stderr, "Error - Tipo de algoritmo nao foi encontrado\n");
        exit(-1);
    }

    scanf("%d", &qtdBar);
    getchar();

    BarCasa = (relacao*)malloc(sizeof(relacao) * qtdBar);
    bares = (int*)malloc(sizeof(int) * qtdBar);
    casas = (int*)malloc(sizeof(int) * qtdBar);

    for(i=0;i<qtdBar;i++){
        scanf("%d %d", &bar, &casa);
        BarCasa[i].bar = bar;
        BarCasa[i].casa = casa;
        bares[i] = bar;
        casas[i] = casa;
    }

    ordenaRadixsort(bares, qtdBar);
    ordenaRadixsort(casas, qtdBar);

    clock_t tempo_exec;
    tempo_exec = clock();
    if(tipoAlgoritmo == 'd'){
        dinamica(qtdBar, BarCasa, bares, casas);
    } else if(tipoAlgoritmo == 'g'){
        guloso(qtdBar, BarCasa, bares, casas);
    } else if(tipoAlgoritmo == 'b'){
        bruta(qtdBar, BarCasa, bares, casas);
    }
    if(argc >= 2){
        if(strcmp(argv[1],"-t") == 0){
            tempo_exec = clock() - tempo_exec;
            printf("Tempo gasto: %f segundos\n", ((double)tempo_exec)/CLOCKS_PER_SEC);
        }
    }
    return 0;
}
