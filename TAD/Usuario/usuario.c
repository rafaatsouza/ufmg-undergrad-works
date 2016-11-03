#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "usuario.h"

void registraUsuario(Usuario *u, int id, char *n){
  int i;

  u->id = id;
  u->nome = (char*)malloc(strlen(n) * sizeof(char));
  strcpy(u->nome, n);
}

Usuario* retornaUsuario(Usuario *u, int qtdUsuarios, int id_user){
    int i;
    for(i=0;i<qtdUsuarios;i++){
        if(u[i].id == id_user){
            return &u[i];
        }
    }
}
