#include <stdio.h>
#include <math.h>
#include "filaNumeros.h"
#include "pilhaOperacoes.h"
#include "possibilidades.h"

void criaPossibilidades(possibilidadeResult *pr, int count){
    int i, j = -1, aux, contador, changeNum = count;
    while(changeNum > 1){
        contador = 1;
        changeNum /= 2;
        j++;
        aux = 1; //1 = '+'; -1 = '*'
        for(i=0;i<count;i++){
            contador++;
            if(aux == 1){
                pr[i].result[j] = '+';
            } else {
                pr[i].result[j] = '*';
            }
            if(contador > changeNum){
                aux *= -1;
                contador = 1;
            }
        }
    }
}

void retornaPossibilidades(possibilidadeResult *pr, int count){
    int i, j, aux;
    Value *actual;
    for(i=0;i<count;i++){
        j = 0;
        pilhaOperacoes *pilha = createPV();
        actual = pr[i].fn->first;
        while(actual != NULL && pr[i].valid == 1){
            if(actual->iOperador == 1){
                if(pr[i].result[j] == '+'){
                    fazOperacao(pilha,1);
                } else {
                    fazOperacao(pilha,0);
                }
                j++;
            } else {
                addNumPilha(pilha,actual->val);
            }
            actual = actual->next;
            if(pilha->topo->val > pr[i].fn->resultado){
                pr[i].valid = 0;
            }
        }
        if(pilha->result != pr[i].fn->resultado){
            pr[i].valid = 0;
        } else {
            printf("%s\n", pr[i].result);
        }
        freePilha(pilha);
    }
}

void printResults(filaNumeros *fn){
    int i, j, count_possibilidades = pow(2,fn->count_operadores);
    possibilidadeResult *result = (possibilidadeResult*)malloc(sizeof(possibilidadeResult)*count_possibilidades);

    for(i=0;i<count_possibilidades;i++){
        result[i].result = (char*)malloc(sizeof(char)*count_possibilidades);
        result[i].valid = 1;
        result[i].fn = fn;
    }
    criaPossibilidades(result, count_possibilidades);
    retornaPossibilidades(result, count_possibilidades);

    for(i=0;i<count_possibilidades;i++){
        free(result[i].result);
    }
    free(result);
}