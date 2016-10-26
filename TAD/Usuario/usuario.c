#include <stdio.h>
#include <stdlib.h>
#include "usuario.h"

void registraUsuario(Usuario *u, int id, char *n, int nome_qtd){
  int i;
  u->id = id;
  u->nome_qtd = nome_qtd;
  u->nome = (char*)malloc(nome_qtd * sizeof(char));
  for(i = 0;i < nome_qtd; i++){
      if(n[i] != ':') {
        u->nome[i] = n[i];
      }
  }
}

void listaInfoUsuario(Usuario *u){
  printf("Usuario %s, de id %d\n", u->nome, u->id);
}
