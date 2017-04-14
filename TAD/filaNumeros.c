#include <stdlib.h>
#include <stdio.h>
#include "filaNumeros.h"

filaNumeros* createFV(){
    filaNumeros *fv = (filaNumeros*)malloc(sizeof(filaNumeros));

    fv->count_numeros = 0;
    fv->resultado = -1;
    return fv;
}

void addElement(filaNumeros *fv, int num, int iOperador){
    Value *val = (Value*)malloc(sizeof(Value));

    val->val = num;
    val->iOperador = iOperador;
    val->next = NULL;

    if(fv->count_numeros == 0){
        fv->first = val;
        fv->last = val;
    } else {
        val->ant = fv->last;
        fv->last->next = val;
        fv->last = val;

    }
    fv->count_numeros++;
}

void imprimeFila(filaNumeros* fv){
    if(fv->count_numeros > 0){
        Value *val = fv->first;

        while(val != NULL){
            if(val->iOperador == 1){
                printf("? ");
            } else {
                printf("%d ", val->val);
            }
            val = val->next;
        }
        printf("\n");
    }
}

void printResults(filaNumeros *fv){
    printf("To do\n");
}
