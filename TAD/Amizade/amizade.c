#include <stdio.h>
#include <stdlib.h>
#include "amizade.h"

//inicia uma nova lista de amizades
Amizade* iniciaListaAmizade(){
  Amizade *a = (Amizade*)malloc(sizeof(Amizade));
  a->qtd = 0;
  a->primeira = NULL;
  a->ultima = NULL;

  return a;
}

//verifica se uma amizade entre dois usuarios ja existe
int amizadeRepetida(Amizade *a, int id1, int id2){
  if(a->qtd <= 0){
    return 0;
  }

  Relacao *r_aux = a->primeira;
  while (r_aux != NULL) {
    if((r_aux->id1 == id1 || r_aux->id1 == id2) && (r_aux->id2 == id1 || r_aux->id2 == id2)){
      return 1;
    }
    r_aux = r_aux->prox;
  }
  free(r_aux);
  return 0;
}

//retorna o end. de memória para a relação entre dois usuarios
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

//inicia a amizade entre dois usuarios
void iniciarAmizade(Amizade *a, int id1, int id2, int tempo){
  if(id1 != id2){
    if(amizadeRepetida(a,id1,id2) == 0){
      Relacao *r = (Relacao*)malloc(sizeof(Relacao));

      r->id1 = id1;
      r->id2 = id2;
      r->ativa = 1;
      r->t_cadastro = tempo;
      r->prox = NULL;
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
      Relacao *r = retornaRelacao(a, id1, id2);
      if(r != NULL){
        if(r->ativa == 0){
            r->t_cadastro = tempo;
            r->ativa = 1;
        }
      }
    }
  }
}

//cancela a amizade entre dois usuarios
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

//retorna uma nova lista de amizades contendo só as amizades de um determinado usuario
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
