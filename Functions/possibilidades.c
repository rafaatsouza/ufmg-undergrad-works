#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "../TAD/filaElementos.h"
#include "../TAD/pilhaOperacoes.h"
#include "possibilidades.h"

void printaPossibilidade(char *possibilidade, int operadores){
    int i;
    for(i=0;i<operadores;i++){
        if(possibilidade[i] == '0'){
            printf("+");
        } else{
            printf("*");
        }
    }
    printf("\n");
}

void converteParaBinario(long long int num, char *possibilidade, int operadores){
    long long int j, i = operadores-1, resto;
    while(num >= 1){
        resto = num % 2;
        num = (num-resto)/2;
        if(resto == 0){
            possibilidade[i] = '0';
        } else {
            possibilidade[i] = '1';
        }
        i--;
        if(num == 1){
            possibilidade[i] = '1';
            i--;
            break;
        }
    }
    for(j=i;j>=0;j--){
        possibilidade[j] = '0';
    }
}

void exibeResultados(filaElementos *fn){
    unsigned long long int i, count = pow(2,fn->count_operadores);
    int j;

    char *possibilidadeAtual = (char*)malloc(sizeof(char)*fn->count_operadores);

    for(i=0;i<count;i++){
        converteParaBinario(i,possibilidadeAtual, fn->count_operadores);
        pilhaOperacoes *pilha = createPV();
        j = 0;
        Value *actual = fn->first;
        while(actual != NULL && (pilha->topo == NULL || pilha->topo->val <= fn->resultado)){
            if(actual->iOperador == 1){
                if(possibilidadeAtual[j] == '0'){
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
            printaPossibilidade(possibilidadeAtual, fn->count_operadores);
        }
        freePilha(pilha);
    }
    free(possibilidadeAtual);
}
