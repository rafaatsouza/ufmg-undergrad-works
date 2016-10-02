#include <stdio.h>
#include <stdlib.h>
#include "player.h"

void createPlayer(Player *p, int x, int y, char *n, int name_count, int mapSize){
  int i;
  p->name_count = name_count;
  p->count_pokebolas = 3;
  p->name = (char*)malloc(name_count * sizeof(char));
  for(i = 0;i < name_count; i++){
      if(n[i] != ':') {
        p->name[i] = n[i];
      }
  }
  p->x = x;
  p->y = y;

  Historic *player_historic;
  Score *player_score;

  player_historic = (Historic*)malloc(sizeof(Historic));
  player_score = (Score*)malloc(sizeof(Score));

  player_score->scoreTotal = 0;
  player_score->moveTotal = 0;
  player_score->historic = player_historic;
  p->score = player_score;
  p->score->historic->first = NULL;
  p->score->historic->last = NULL;
}

int checkCel(Player *p, int x, int y){
  Move *m = (Move*)malloc(sizeof(Move));

  m = p->score->historic->first;
  while (m != NULL) {
    if(m->x == x && m->y == y){
      return 1;
    }
    m = m->next;
  }
  return 0;
}

int defineNextMove(Player *p, int **map, int mapsize){
  Move *best_move = (Move*)malloc(sizeof(Move));
  int x,y, best_filled = 0;
  for(x =(p->x)-1;x<=(p->x)+1;x++){
    for(y =(p->y)-1;y<=(p->y)+1;y++){
      if(x >= 0 && y >= 0 && x <= (mapsize-1) && y <= (mapsize-1)){
        if(checkCel(p,x,y) == 0){
          if(best_filled == 0){
            best_move->x = x;
            best_move->y = y;
            best_move->val = map[x][y];
            best_filled = 1;
          } else {
            if((map[x][y] > best_move->val) || (best_move->val == 6 && p->count_pokebolas > 0 && map[x][y] > 0 && map[x][y] < 6)){
              if(map[x][y] != 6){
                best_move->x = x;
                best_move->y = y;
                best_move->val = map[x][y];
              } else if(p->count_pokebolas == 0 || best_move->val < 0){
                best_move->x = x;
                best_move->y = y;
                best_move->val = map[x][y];
              }
            }
          }
        }
      }
    }
  }
  if(best_filled == 0){
    return 0;
  } else {
    p->x = best_move->x;
    p->y = best_move->y;
    return 1;
  }
}

void registerPlay(Player *p, int **map){
  Move *actual_move = (Move*)malloc(sizeof(Move));

  actual_move->val = map[p->x][p->y];
  actual_move->x = p->x;
  actual_move->y = p->y;
  actual_move->next = NULL;

  if(p->score->historic->first == NULL && p->score->historic->last == NULL){
    p->score->historic->first = actual_move;
    p->score->historic->last = actual_move;
  } else {
    p->score->historic->last->next = actual_move;
    p->score->historic->last = actual_move;
  }

  p->score->moveTotal++;
  if(map[p->x][p->y] != 6){
    if(map[p->x][p->y] > 0){
      if(p->count_pokebolas > 0){
        p->score->scoreTotal += map[p->x][p->y];
        p->count_pokebolas--;
      }
    } else {
      p->score->scoreTotal += map[p->x][p->y];
    }
  } else {
    if(p->count_pokebolas == 0){
      p->count_pokebolas++;
    }
  }
  //printf("[JOGADA]Player %s foi na posicao %d,%d e ganhou %d pontos. Total:%d\n", p->name, p->x, p->y, map[p->x][p->y], p->score->scoreTotal);
}

void andar(Player *p, int **map, int mapsize){
  if(p->score->moveTotal <= (3*mapsize)){
    registerPlay(p, map);
    if(defineNextMove(p,map,mapsize) == 1){
      andar(p,map,mapsize);
    }
  }
}

int* explorar(Player *p, int mapsize, int **map){
  int x,y, count = 0;
  for(x =(p->x)-1;x<=(p->x)+1;x++){
    for(y =(p->y)-1;y<=(p->y)+1;y++){
      if(x >= 0 && y >= 0 && x <= (mapsize-1) && y <= (mapsize-1)){
        if(checkCel(p,x,y) == 0){
          count++;
        }
      }
    }
  }
  Move *possiveis = (Move*)malloc(sizeof(Move)*count);
  count = 0;
  for(x =(p->x)-1;x<=(p->x)+1;x++){
    for(y =(p->y)-1;y<=(p->y)+1;y++){
      if(x >= 0 && y >= 0 && x <= (mapsize-1) && y <= (mapsize-1)){
        if(checkCel(p,x,y) == 0){
          possiveis[count].x = x;
          possiveis[count].y = y;
          possiveis[count].val = map[x][y];
        }
      }
    }
  }
}

Move* caminho_percorrido(Player *p){
  return p->score->historic->first;
}

void printHistoric(Player *p, FILE *arq){
  Move *m = (Move*)malloc(sizeof(Move));
  m = caminho_percorrido(p);

  while (m != NULL) {
    fprintf(arq, " %d,%d", m->x, m->y);
    m = m->next;
  }
  fprintf(arq, "\n");
}

void ResolveTie(Player *p, int qtdPlayers, FILE *arq){
  int i, cp = 5, vencedor = -1, *qtd_pokemon = (int*)malloc(sizeof(int)*qtdPlayers);
  Move *m = (Move*)malloc(sizeof(Move));
  Player *winner = (Player*)malloc(sizeof(Player));
  while (cp > 0) {
    for(i = 0;i<qtdPlayers;i++){
      qtd_pokemon[i] = 0;
    }
    for (i = 0; i < qtdPlayers; i++) {
        m = p[i].score->historic->first;
        while (m != NULL) {
          if(m->val == cp){
            qtd_pokemon[i]++;
          }
          m = m->next;
        }
    }
    for(i=0;i<qtdPlayers;i++){
      if(i==0){
        vencedor = i;
      } else {
        if(qtd_pokemon[i] > qtd_pokemon[vencedor]){
          vencedor = i;
        } else if(qtd_pokemon[i] == qtd_pokemon[vencedor]){
          vencedor = -1;
          break;
        }
      }
    }
    cp--;
  }
  if(vencedor >= 0){
    fprintf(arq, "VENCEDOR %s", p[vencedor].name);
  } else {
    vencedor = -1;
    for(i=0;i<qtdPlayers;i++){
      if(i==0){
        vencedor = i;
      } else {
        if(p[i].score->moveTotal < p[vencedor].score->moveTotal){
          vencedor = i;
        } else if(p[i].score->moveTotal == p[vencedor].score->moveTotal){
          vencedor = -1;
          break;
        }
      }
    }
    if(vencedor >= 0){
      fprintf(arq, "VENCEDOR %s", p[vencedor].name);
    } else {
      fprintf(arq, "VENCEDORES ");
      for(i=0;i<qtdPlayers;i++){
        if(i>0){
          fprintf(arq, ",");
        }
        fprintf(arq, "%s", p[i].name);
      }
    }
  }
}

void DefineWinner(Player *p, int qtdPlayers, FILE *arq){
  int i, maxScore = 0, tie = 0;

  for (i = 0; i < qtdPlayers; i++) {
    if (maxScore < p[i].score->scoreTotal) {
      maxScore = p[i].score->scoreTotal;
    }
  }

  for (i = 0; i < qtdPlayers; i++) {
    if (maxScore == p[i].score->scoreTotal) {
      tie++;
    }
  }

  Player *winners = (Player*)malloc(tie*sizeof(Player));
  if(tie == 1){
    for(i=0;i<qtdPlayers;i++){
      if(p[i].score->scoreTotal == maxScore){
        winners = &p[i];
        break;
      }
    }
    fprintf(arq, "VENCEDOR %s", winners->name);
  } else {
    int c = 0;
    for (i = 0; i < qtdPlayers; i++) {
      if(p[i].score->scoreTotal == maxScore){
        winners[c] = p[i];
        c++;
      }
    }
    ResolveTie(winners,tie,arq);
  }
}
