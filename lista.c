#include <stdio.h>
#include "lista.h"

lista* criaListaVazia(){
    lista* l = (lista*)malloc(sizeof(lista));
    l->qtd = 0;
    l->primeiro = NULL;
    l->ultimo = NULL;
    return l;
}

int listaVazia(lista *l){
    if(l->qtd > 0){
        return 0;
    } else {
        return 1;
    }
}

void adicionaItemLista(lista *l, int v){
    item *i = (item*)malloc(sizeof(item));

    i->index = v;
    i->prox = NULL;

    if(listaVazia(l) == 1){
        l->primeiro = i;
        l->ultimo = i;
    } else {
        l->ultimo->prox = i;
        l->ultimo = i;
    }

    l->qtd = l->qtd + 1;
}

void liberaLista(lista *l){
    if(l->qtd > 0){
        item *i = l->primeiro, *aux;
        while(i != NULL){
            aux = i;
            i = i->prox;
            free(aux);
        }
    }
    free(l);
}

void printaSequencia(lista *l){
    if(l->qtd > 0){
        item *i = l->primeiro;
        while(i != NULL){
            printf("%d ", i->index);
            i = i->prox;
        }
        printf("\n");
    } else {
        printf("sem adjacentes \n");
    }
}

// int existeItem(lista *l, int val){
//     int retorno = 0, i;
//     if(l->qtd > 0){
//         item *i = l->primeiro;
//         while(i != NULL && retorno == 0){
//             if(i->index == val){
//                 retorno = 1;
//             }
//             i = i->prox;
//         }
//         return retorno;
//     }
//}