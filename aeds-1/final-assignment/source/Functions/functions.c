#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include "functions.h"

int returnRandom(int min, int max){
	return (rand()%max) + min;
}
bool checkEqualLocation(int x1, int y1, int x2, int y2, double max_dif){
	if(x1 == x2 && y1 == y2){
		return true;
	}
	else {
		double dif = sqrt(pow(x1 - x2,2) + pow(y1 - y2,2));
		if(dif > max_dif){
			return false;
		}
		else{
			return true;
		}
	}
}
void PersegueLocation(location enemy_l[], int qtd_enemies, location *target){
	int count;
	for(count = 0;count< qtd_enemies;count++){
		if(enemy_l[count].active == true){
			if(enemy_l[count].x >= target->x){
				if(enemy_l[count].dx > 0){
					enemy_l[count].dx = (-1.0)*(enemy_l[count].dx);
				}
			}
			else{
				if(enemy_l[count].dx < 0){
					enemy_l[count].dx = (-1.0)*(enemy_l[count].dx);
				}
			}
			if(enemy_l[count].y >= target->y){
				if(enemy_l[count].dy > 0){
					enemy_l[count].dy = (-1.0)*(enemy_l[count].dy);
				}
			}
			else{
				if(enemy_l[count].dy < 0){
					enemy_l[count].dy = (-1.0)*(enemy_l[count].dy);
				}
			}
		}	
	}
}
void createBomb(bomb b[], int qtd_bombs, location *bomber_l, int time, double range){
	if(bomber_l->active == true){
		int count;
		for(count = 0;count < qtd_bombs;count++){
			if(b[count].active == false){
				b[count].x = bomber_l->x;
				b[count].y = bomber_l->y;
				b[count].seconds = time;
				b[count].raio = range;
				b[count].active = true;
				break;
			}
		}
	}
}
bool checkKill(bomb *b, location *enemy){
	double d;
	d = sqrt(pow(b->x - enemy->x,2) + pow(b->y - enemy->y,2));
	if(d <= b->raio){
		enemy->active = false;
		return true;
	}
	else{
		return false;
	}
}
void createLocationBomber(location *bomber_l, int max_x, int max_y, int size){
	bomber_l->active = true;
	bomber_l->x = returnRandom(0,max_x);
	bomber_l->y = returnRandom(0,max_y);		
	bomber_l->dx = size;
	bomber_l->dy = size;
}
void createLocationEnemies(location enemy[], int qtd_enemies, location *bomber_l, int max_x, int max_y, int size){
	int x;
	bool validlocation = false;
	while (validlocation == false){
		validlocation = true;
		for(x=0;x<qtd_enemies;x++){
			enemy[x].active = true;
			enemy[x].x = returnRandom(0,max_x);
			enemy[x].y = returnRandom(0,max_y);		
			if (checkEqualLocation(enemy[x].x,enemy[x].y,bomber_l->x,bomber_l->y,size*2) == true){
				validlocation = false;
			}
		}
		if (validlocation == true){
			for(x=0;x<qtd_enemies;x++){
				int y;
				for(y=0;y<qtd_enemies;y++){
					if(x != y){
						if(checkEqualLocation(enemy[x].x,enemy[x].y,enemy[y].x,enemy[y].y,size*2) == true){
							validlocation = false;
						}
					}
				}
			}	
		}
	}
}
void checkDeath(location *bomber, location e[], int qtd_enemies, int size){
	int x;
	double distancia;
	for(x = 0; x < qtd_enemies; x++){
		if(e[x].active == true){
			distancia = sqrt(pow(bomber->x - e[x].x,2) + pow(bomber->y - e[x].y,2));
			if(distancia < (size-1)){
				bomber->active = false;
			}
		}	
	}
}
void MoveEnemies(location e[], int qtd_enemies, int size, int max_x, int max_y){
	int count, count_o;
	for(count=0;count<qtd_enemies;count++){
		if (e[count].active == true){
			e[count].x += e[count].dx;
			e[count].y += e[count].dy;
			
			if(e[count].y < 0){
				e[count].y = 0;
			}
			if(e[count].x < 0){
				e[count].x = 0;
			}
			if(e[count].x > max_x){
				e[count].x = max_x;
			}
			if(e[count].y > max_y){
				e[count].y = max_y;
			}
		}	
	}
}
void defineDelta(location enemies[], int qtd_enemies, float x, int fase){
	int count;
	for(count=0;count<qtd_enemies;count++){
		enemies[count].dx = x*(pow(fase,2)/fase);
		enemies[count].dy = x*(pow(fase,2)/fase);	
	}
}
float returnRecorde(float pontuacao){
	FILE *recorde;
	char recorde_FileName[20] = "recorde.dat";
	recorde = fopen(recorde_FileName,"r");
	if(recorde == NULL){
		recorde = fopen(recorde_FileName,"w");
		fprintf(recorde,"%f",pontuacao);
		fclose(recorde);
		return pontuacao;
	}
	else{
		float vlr_recorde;
		fscanf(recorde,"%f",&vlr_recorde);
		fclose(recorde);
		if(pontuacao > vlr_recorde){
			remove(recorde_FileName);
			recorde = fopen(recorde_FileName,"w");
			fprintf(recorde,"%f",pontuacao);
			fclose(recorde);
			return pontuacao;
		}
		else{
			return vlr_recorde;	
		}
	}
}
