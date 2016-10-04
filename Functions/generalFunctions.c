#include <stdio.h>
#include <stdlib.h>
#include "generalFunctions.h"

//cria uma matriz bidimensional com a dimensão informada em size
int** createMap(int size){
  int i,x,**map;
  map = (int**)malloc(sizeof(int*)*size);
  for (i = 0; i < size; i++){
    map[i] = (int*)malloc(sizeof(int)*size);
    for (x=0;x < size; x++){
      map[i][x] = 0;
    }
  }
  return map;
}
