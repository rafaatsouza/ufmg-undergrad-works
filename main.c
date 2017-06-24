#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "vizinhanca.h"

int main(int argc, char *argv[]){
    char tipoAlgoritmo;
    vizinhanca *v;
    int qtdBar, mostraTempo = 0;

    if(argc >= 2){
        if(strcmp(argv[1],"-t") == 0){
            mostraTempo = 1;
        }
    }

    tipoAlgoritmo = getchar();

    if(tipoAlgoritmo != 'd' && tipoAlgoritmo != 'g' && tipoAlgoritmo != 'b'){
        fprintf(stderr, "Error - Tipo de algoritmo nao foi encontrado\n");
        exit(-1);
    }

    scanf("%d", &qtdBar);
    getchar();

    v = instanciaVizinhanca(qtdBar);
    preencheVizinhanca(v);

    clock_t tempo_exec;
    if(mostraTempo == 1){ tempo_exec = clock(); }

    if(tipoAlgoritmo == 'd'){
        dinamica(v);
    } else if(tipoAlgoritmo == 'g'){
        guloso(v);
    } else if(tipoAlgoritmo == 'b'){
        bruta(v);
    }

    if(mostraTempo == 1){
        tempo_exec = clock() - tempo_exec;
        printf("Tempo gasto: %f segundos\n", ((double)tempo_exec)/CLOCKS_PER_SEC);
    }
    
    return 0;
}
