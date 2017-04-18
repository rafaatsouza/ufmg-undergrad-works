#include <stdlib.h>
#include "filaElementos.h"

void freeFila(filaElementos *fn){
    Value *val = fn->first;
    Value *aux;
    while(val != NULL){
        aux = val;
        val = val->next;
        free(aux);
    }
    free(val);
    free(fn);
}

filaElementos* createFV(){
    filaElementos *fv = (filaElementos*)malloc(sizeof(filaElementos));

    fv->count_numeros = 0;
    fv->count_operadores = 0;
    fv->resultado = -1;
    return fv;
}

void addElement(filaElementos *fn, int num, int iOperador){
    Value *val = (Value*)malloc(sizeof(Value));

    val->val = num;
    val->iOperador = iOperador;
    val->next = NULL;

    if((fn->count_numeros + fn->count_operadores) == 0){
        fn->first = val;
        fn->last = val;
    } else {
        fn->last->next = val;
        fn->last = val;
    }

    if(iOperador == 1){
        fn->count_operadores++;
    } else {
        fn->count_numeros++;
    }
}
