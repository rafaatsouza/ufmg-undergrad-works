#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Functions/generalFunctions.h"
#include "ADT/Player/player.h"

int main(){
  int mapSize, qtdPlayers, i, **map;
  FILE *arq;
	arq = fopen("entrada.txt","r");
	if(arq == NULL) {
		printf("Arquivo não encontrado!");
		exit(-1);
	}

  fscanf(arq,"%d", &mapSize);
  map = createMap(mapSize);
  for(i=0;i<mapSize;i++){
    for(int j=0;j<mapSize;j++){
      fscanf(arq,"%d", &map[i][j]);
    }
  }
  //imprimeMatriz(map,mapSize); //imprimir matriz para testar

  fscanf(arq,"%d", &qtdPlayers);
  int x, y;
  char *name, *coord, buf[100];
  Player *players = (Player*)malloc(qtdPlayers * sizeof(Player));

  i = 0;
  while (fgets(buf,100,arq) != NULL) {
    if (buf[0] != '\n'){
      name = strtok(buf," ");
      coord = strtok(NULL," ");
      x = atoi(strtok(coord,","));
      y = atoi(strtok(NULL,","));
      createPlayer(&players[i], x, y, name, strlen(name), mapSize);
      i++;
    }
  }

  fclose(arq);

  for(i=0;i<qtdPlayers;i++){
    MovePlayer(&players[i],map,mapSize);
  }

  for(i=0;i<qtdPlayers;i++){
    printf("player %s: %dpts\n", players[i].name, players[i].score->scoreTotal);
  }
  //DefineWinner(players);

  return 0;
}
