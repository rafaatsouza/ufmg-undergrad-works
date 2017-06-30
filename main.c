#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "vizinhanca.h"

int main(int argc, char *argv[]){
    clock_t tempo_exec;
    char tipoAlgoritmo;
    vizinhanca *v;
    int qtdBar, mostraTempo = 0, forcaTipoAlgoritmo = 0;

    if(argc >= 2){
        if(strcmp(argv[1],"-t") == 0){
            mostraTempo = 1;
        } else if(strcmp(argv[1],"-d") == 0){
            forcaTipoAlgoritmo = 1;
        } else if(strcmp(argv[1],"-g") == 0){
            forcaTipoAlgoritmo = 2;
        } else if(strcmp(argv[1],"-b") == 0){
            forcaTipoAlgoritmo = 3;
        }
        if(argc >= 3){
            if(strcmp(argv[2],"-d") == 0){
                forcaTipoAlgoritmo = 1;
            } else if(strcmp(argv[2],"-g") == 0){
                forcaTipoAlgoritmo = 2;
            } else if(strcmp(argv[2],"-b") == 0){
                forcaTipoAlgoritmo = 3;
            }
        }
    }

    tipoAlgoritmo = getchar();

    if(tipoAlgoritmo != 'd' && tipoAlgoritmo != 'g' && tipoAlgoritmo != 'b' && forcaTipoAlgoritmo == 0){
        fprintf(stderr, "Error - Tipo de algoritmo nao foi encontrado\n");
        exit(-1);
    }

    scanf("%d", &qtdBar);
    getchar();

    v = instanciaVizinhanca(qtdBar);
    preencheVizinhanca(v);

    if(mostraTempo == 1){ tempo_exec = clock(); }

    if(forcaTipoAlgoritmo == 0){
        if(tipoAlgoritmo == 'd'){
            dinamica(v);
        } else if(tipoAlgoritmo == 'g'){
            guloso(v);
        } else if(tipoAlgoritmo == 'b'){
            bruta(v);
        }
    } else {
        if(forcaTipoAlgoritmo == 1){
            dinamica(v);
        } else if(forcaTipoAlgoritmo == 2){
            guloso(v);
        } else if(forcaTipoAlgoritmo == 3){
            bruta(v);
        }
    }

    if(mostraTempo == 1){
        tempo_exec = clock() - tempo_exec;
        printf("Tempo gasto: %f segundos\n", ((double)tempo_exec)/CLOCKS_PER_SEC);
    }

    liberaVizinhanca(v);

    return 0;
}
