#include <stdlib.h>
#include <stdio.h>
#include "Functions/generalFunctions.h"
#include "ADT/Player/player.h"

void teste(int **map, int size){
  printf("tamanho: %d\n", size);
}

int main(){
  int mapSize, **map;
  FILE *arq;
	arq = fopen("entrada.txt","r");
	if(arq == NULL) {
		printf("Arquivo não encontrado!");
		exit(-1);
	}

  fscanf(arq,"%d", &mapSize);
  createMap(map, mapSize);

  for(int i=0;i<mapSize;i++){
    for(int j=0;j<mapSize;j++){
      fscanf(arq,"%d", &map[i][j]);
    }
  }
  imprimeMatriz(map,mapSize);

  return 0;
}
