#include <stdio.h>
#include <math.h>
#include "../TAD/filaElementos.h"
#include "../TAD/pilhaOperacoes.h"
#include "possibilidades.h"

void criaPossibilidades(char **pr, int count){
    int i, j = -1, aux, contador, changeNum = count;
    while(changeNum > 1){
        contador = 1;
        changeNum /= 2;
        j++;
        aux = 1; //1 = '+'; -1 = '*'
        for(i=0;i<count;i++){
            contador++;
            if(aux == 1){
                pr[i][j] = '+';
            } else {
                pr[i][j] = '*';
            }
            if(contador > changeNum){
                aux *= -1;
                contador = 1;
            }
        }
    }
}

void verificaPossibilidades(filaElementos *fn, char **pr, int count){
    int i, j, aux;
    Value *actual;
    for(i=0;i<count;i++){
        j = 0;
        pilhaOperacoes *pilha = createPV();
        actual = fn->first;
        while(actual != NULL && (pilha->topo == NULL || pilha->topo->val <= fn->resultado)){
            if(actual->iOperador == 1){
                if(pr[i][j] == '+'){
                    fazOperacao(pilha,1);
                } else {
                    fazOperacao(pilha,0);
                }
                j++;
            } else {
                addNumPilha(pilha,actual->val);
            }
            actual = actual->next;
        }
        if(pilha->result == fn->resultado){
            printf("%s\n", pr[i]);
        }
        freePilha(pilha);
    }
}

void exibeResultados(filaElementos *fn){
    int i, j, count_possibilidades = pow(2,fn->count_operadores);
    char **result = (char**)malloc(sizeof(char*)*count_possibilidades);

    for(i=0;i<count_possibilidades;i++){
        result[i] = (char*)malloc(sizeof(char)*fn->count_operadores);
    }
    criaPossibilidades(result, count_possibilidades);
    verificaPossibilidades(fn, result, count_possibilidades);

    for(i=0;i<count_possibilidades;i++){
        free(result[i]);
    }
    free(result);
}
