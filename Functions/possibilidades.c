#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "../TAD/filaElementos.h"
#include "../TAD/pilhaOperacoes.h"
#include "possibilidades.h"

//recebe o vetor de char's referente à sequência de 0's e 1's e printa na tela a sequência de operadores equivalente
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

//recebe um numero e converte de decimal para binario, alocando o resultado num vetor de char's que tem tamanho = int operadores
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
    //completa o resto do vetor com 0's. Ex: conv 3 para binario = 11. Caso a máscara seja de 6 operadores, o vetor fica "000011"
    for(j=i;j>=0;j--){
        possibilidade[j] = '0';
    }
}

//recebe a fila de elementos informada, seu resultado, e printa todas as possbilidades de operadores possíveis
void exibeResultados(filaElementos *fn){
    unsigned long long int i, count = pow(2,fn->count_operadores); //count é a quantidade de possibilidades, definida por 2^(quantidade de "?")
    int j;

    char *possibilidadeAtual = (char*)malloc(sizeof(char)*fn->count_operadores); //cria vetor de char's para máscara de operadores

    for(i=0;i<count;i++){
        converteParaBinario(i,possibilidadeAtual, fn->count_operadores); //converte o contador do for para binário, para ser usado como máscara de operadores
        pilhaOperacoes *pilha = createPV(); //cria uma pilha vazia
        j = 0;
        Value *actual = fn->first;
        while(actual != NULL && (pilha->topo == NULL || pilha->topo->val <= fn->resultado)){ //passa por todos os elementos da fila, usando a pilha para aplicar os operadores da tentativa atual à sequência de númros
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
            printaPossibilidade(possibilidadeAtual, fn->count_operadores); //caso o resultado final da pilha seja = informado na entrada, printa a sequência de operadores testada
        }
        freePilha(pilha); //desaloca a memória referente à pilha
    }
    free(possibilidadeAtual); //desaloca memória do vetor de char's usado para máscara de operadores
}
