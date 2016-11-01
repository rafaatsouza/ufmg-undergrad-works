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
  if(a->qtd <= 0){
    return 0;
  }

  Relacao *r_aux = a->primeira;
  while (r_aux != NULL) {
    if((r_aux->id1 == r->id1 || r_aux->id1 == r->id2) && (r_aux->id2 == r->id1 || r_aux->id2 == r->id2)){
      return 1;
    }
    r_aux = r_aux->prox;
  }
  free(r_aux);
  return 0;
}

Relacao* retornaRelacao(Amizade *a, int id1, int id2){
  if(a->qtd > 0){
    Relacao *r_aux = a->primeira;
    Relacao *r_retorno;

    while (r_aux != NULL) {
      if((r_aux->id1 == id1 || r_aux->id1 == id2) && (r_aux->id2 == id1 || r_aux->id2 == id2)){
        r_retorno = r_aux;
      }
      r_aux = r_aux->prox;
    }
    free(r_aux);
    return r_retorno;
  }
}

void iniciarAmizade(Amizade *a, int id1, int id2, int tempo){
  Relacao *r = (Relacao*)malloc(sizeof(Relacao));

  r->id1 = id1;
  r->id2 = id2;
  r->ativa = 1;
  r->t_cadastro = tempo;
  r->prox = NULL;

  if(id1 != id2){
    if(amizadeRepetida(a,r) == 0){
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
            r->t_cadastro = tempo;
            r->ativa = 1;
        }
      }
    }
  }
}

void cancelarAmizade(Amizade *a, int id1, int id2, int tempo){
    if(a->qtd > 0){
      Relacao *r = retornaRelacao(a, id1, id2);

      if(r != NULL){
          if(r->ativa == 1){
              r->ativa = 0;
          }
      }
    }
}

Amizade* verAmigos(Amizade *a, int id_user){
    Amizade *retorno = iniciaListaAmizade();
    Relacao *r_aux = a->primeira;
    while (r_aux != NULL) {
      if(r_aux->ativa == 1){
          if(r_aux->id1 == id_user){
              iniciarAmizade(retorno, id_user, r_aux->id2, r_aux->t_cadastro);
          } else if(r_aux->id2 == id_user) {
              iniciarAmizade(retorno, id_user, r_aux->id1, r_aux->t_cadastro);
          }
      }
      r_aux = r_aux->prox;
    }
    free(r_aux);
    return retorno;
}
