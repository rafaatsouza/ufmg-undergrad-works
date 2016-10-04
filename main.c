#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Functions/generalFunctions.h"
#include "ADT/Player/player.h"

int main(){
  int mapSize, qtdPlayers = 0, i, **map;
  FILE *arq;
  //abre o arquivo de entrada
	arq = fopen("entrada.txt","r");
	if(arq == NULL) {
		printf("Arquivo não encontrado!");
		exit(-1);
	}
  //cria a matriz e depois lê os valores do arquivo de entrada para modificar a matriz
  fscanf(arq,"%d", &mapSize);
  map = createMap(mapSize);
  for(i=0;i<mapSize;i++){
    for(int j=0;j<mapSize;j++){
      fscanf(arq,"%d", &map[i][j]);
    }
  }

  fscanf(arq,"%d", &qtdPlayers);
  int x, y;
  char *name, *coord, buf[100];
  Player *players = (Player*)malloc(qtdPlayers * sizeof(Player));
  //lê os valores do arquivo de entrada para registrar todos os jogadores
  i = 0;
  while (fgets(buf,100,arq) != NULL) {
    if (buf[0] != '\n' && buf[0] != ' ' && buf[0] != ""){
      name = strtok(buf," ");
      coord = strtok(NULL," ");
      x = atoi(strtok(coord,","));
      y = atoi(strtok(NULL,","));
      createPlayer(&players[i], x, y, name, strlen(name), mapSize);
      i++;
    }
  }

  fclose(arq);
  arq = fopen("saida.txt","w");
  fclose(arq);
  arq = fopen("saida.txt","a");
  //passa por todos os jogadores, para fazer suas jogadas e registrar no arquivo de saída
  for(i=0;i<qtdPlayers;i++){
    andar(&players[i],map,mapSize);
    fprintf(arq, "%s %d ", players[i].name, players[i].score->scoreTotal);
    printHistoric(&players[i],arq);
  }
  //define o vencedor do jogo e registra no arquivo de saida
  DefineWinner(players, qtdPlayers, arq);
  fclose(arq);

  return 0;
}
