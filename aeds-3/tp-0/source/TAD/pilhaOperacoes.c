#include <stdlib.h>
#include "pilhaOperacoes.h"

void freePilha(pilhaOperacoes *po){ //desaloca a memória de todos os itens dentra da pilha, e posteriormente, a memória da própria pilha
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

pilhaOperacoes* createPV(){ //cria uma pilha vazia
    pilhaOperacoes *pv = (pilhaOperacoes*)malloc(sizeof(pilhaOperacoes));

    pv->result = 0;
    pv->count_numeros = 0;
    pv->topo = NULL;
}

void addNumPilha(pilhaOperacoes *po, int num){ //adiciona um número ao topo da pilha
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

void fazOperacao(pilhaOperacoes *po, int iSoma){ //executa uma soma/multiplicação com dois itens do topo da pilha, transformado-os em um item com o resultado da operação
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
