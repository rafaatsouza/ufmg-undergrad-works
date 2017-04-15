#include <stdlib.h>
#include "pilhaOperacoes.h"

void freePilha(pilhaOperacoes *po){
    Num *n = po->topo;
    Num *aux;
    while(n != NULL){
        aux = n;
        n = n->abaixo;
        free(aux);
    }
    free(n);
    free(po);
}

pilhaOperacoes* createPV(){
    pilhaOperacoes *pv = (pilhaOperacoes*)malloc(sizeof(pilhaOperacoes));

    pv->result = 0;
    pv->count_numeros = 0;
    pv->topo = NULL;
}

void addNumPilha(pilhaOperacoes *po, int num){
    Num *n = (Num*)malloc(sizeof(Num));

    n->val = num;

    if(po->count_numeros > 0){
        n->abaixo = po->topo;
    } else {
        n->abaixo = NULL;
    }

    po->topo = n;
    po->count_numeros++;
}

void fazOperacao(pilhaOperacoes *po, int iSoma){
    if(po->count_numeros >= 2){
        int ResultadoOperacao;

        if(iSoma == 1){
            ResultadoOperacao = po->topo->val + po->topo->abaixo->val;
        } else {
            ResultadoOperacao = po->topo->val * po->topo->abaixo->val;
        }

        Num *oldTopo = po->topo;
        po->topo->abaixo->val = ResultadoOperacao;
        po->topo = oldTopo->abaixo;
        free(oldTopo);

        if(po->count_numeros == 2){
            po->result = ResultadoOperacao;
        }
        po->count_numeros--;
    }
}
