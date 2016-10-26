#include <stdio.h>
#include <stdlib.h>
#include <time.h>
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

void insereAmizade(Amizade *a, int id1, int id2){
  Relacao *r = (Relacao*)malloc(sizeof(Relacao));

  r->id1 = id1;
  r->id2 = id2;
  r->t_cadastro = time(0);
  r->prox = NULL;

  if(amizadeRepetida(a,r) == 0 && id1 != id2){
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
  }
}
