#include <stdio.h>
#include <stdlib.h>
#include "amizade.h"

Amizade* iniciaListaAmizade(){
  Amizade *a = (Amizade*)malloc(sizeof(Amizade));
  a->qtd = 0;
  a->primeira = NULL;
  a->ultima = NULL;

  return a;
}

int amizadeRepetida(Amizade *a, Relacao *r){
  Relacao *r_aux = (Relacao*)malloc(sizeof(Relacao));

  if(a->qtd <= 0){
    return 0;
  }

  r_aux = a->primeira;
  while (r_aux != NULL) {
    if((r_aux->id1 == r->id1 || r_aux->id1 == r->id2) && (r_aux->id2 == r->id1 || r_aux->id2 == r->id2)){
      return 1;
    }
    r_aux = r_aux->prox;
  }
  return 0;
}

Relacao* retornaRelacao(Amizade *a, int id1, int id2){
  if(a->qtd > 0){
    Relacao *r_aux = (Relacao*)malloc(sizeof(Relacao));
    Relacao *r_retorno = (Relacao*)malloc(sizeof(Relacao));

    r_aux = a->primeira;
    while (r_aux != NULL) {
      if((r_aux->id1 == id1 || r_aux->id1 == id2) && (r_aux->id2 == id1 || r_aux->id2 == id2)){
        r_retorno = r_aux;
      }
      r_aux = r_aux->prox;
    }
    return r_retorno;
  }
}

void ativaAmizade(Relacao *r, int tempo){
  Momento *m_ultimo = (Momento*)malloc(sizeof(Momento));
  Momento *m_novo = (Momento*)malloc(sizeof(Momento));

  m_ultimo = r->momento;

  while(m_ultimo->prox != NULL){
    m_ultimo = m_ultimo->prox;
  }

  m_ultimo->prox = m_novo;

  m_novo->t_cadastro = tempo;
  r->ativa = 1;
}

void insereAmizade(Amizade *a, int id1, int id2, int tempo){
  Relacao *r = (Relacao*)malloc(sizeof(Relacao));

  r->id1 = id1;
  r->id2 = id2;
  r->ativa = 1;
  r->prox = NULL;

  if(id1 != id2){
    if(amizadeRepetida(a,r) == 0){
      Momento *m = (Momento*)malloc(sizeof(Momento));

      m->prox = NULL;
      m->t_cadastro = tempo;
      m->t_cancelamento = -1;

      r->momento = m;

      if(a->qtd <= 0){
        a->primeira = r;
        a->ultima = r;
        a->qtd = 1;

        r->ant = NULL;
      } else {
        a->ultima->prox = r;

        r->ant = a->ultima;

        a->ultima = r;
        a->qtd++;
      }
    } else {
      r = retornaRelacao(a, id1, id2);
      if(r != NULL){
        if(r->ativa == 0){
          ativaAmizade(r, tempo);
        }
      }
    }
  }
}
