#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include "Functions/functions.h"
#include <pthread.h>
#include <allegro5/threads.h>

//------------CONSTANTES-----------
const float FPS = 60;
const int SCREEN_W = 640;
const int SCREEN_H = 480;
const int BOMBER_SIZE = 32;
const int ENEMY_SIZE = 32;
const int BOMB_SIZE = 22;
const int BOMB_RANGE = 64;
const int BOMB_TIMER = 60;
const int QTD_ENEMIES = 3;
const int QTD_BOMBS = 3;
const float VEL_ENEMY = 1.0;

int main(int argc, char **argv){
	//------------VARIÁVEIS-----------
    ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_SAMPLE *sample = NULL;
    ALLEGRO_EVENT_QUEUE *event_queue = NULL;
    ALLEGRO_TIMER *timer = NULL;
    ALLEGRO_BITMAP *bomber = NULL;
	ALLEGRO_BITMAP *enemies[QTD_ENEMIES];
	ALLEGRO_BITMAP *bombs[QTD_BOMBS];
	location enemies_l[QTD_ENEMIES];
    location bomber_l;
	bomb bombs_b[QTD_BOMBS];
	int count, fase = 1, tempo = 0, live_enemies = QTD_ENEMIES;
	float pontos_kill = 10.0, pontos_tempo = 1.0, pontuacao = 0;
	bool redraw = true, jogando = true;

	srand((unsigned)time(NULL));
	createLocationBomber(&bomber_l,(SCREEN_W - BOMBER_SIZE),(SCREEN_H - BOMBER_SIZE),BOMBER_SIZE);
	createLocationEnemies(enemies_l,QTD_ENEMIES,&bomber_l,(SCREEN_W - ENEMY_SIZE),(SCREEN_H - ENEMY_SIZE),ENEMY_SIZE);
	defineDelta(enemies_l, QTD_ENEMIES, VEL_ENEMY, fase);
	for(count = 0;count < QTD_BOMBS;count++){
		bombs_b[count].active = false;
	}

	if(!al_init()) {
        fprintf(stderr, "failed to initialize allegro!\n");
        return -1;
    }
    timer = al_create_timer(1.0 / FPS);
    if(!timer) {
       fprintf(stderr, "failed to create timer!\n");
       return -1;
    }

    display = al_create_display(SCREEN_W, SCREEN_H);
    if(!display) {
       fprintf(stderr, "failed to create display!\n");
       al_destroy_timer(timer);
       return -1;
    }

	if(!al_install_audio()){
 	   fprintf(stderr, "failed to initialize audio!\n");
	   return -1;
    }

    if(!al_init_acodec_addon()){
	   fprintf(stderr, "failed to initialize audio codecs!\n");
	   return -1;
    }

    if (!al_reserve_samples(1)){
 	   fprintf(stderr, "failed to reserve samples!\n");
	   return -1;
    }

    bomber = al_create_bitmap(BOMBER_SIZE, BOMBER_SIZE);
    if(!bomber) {
       fprintf(stderr, "failed to create bouncer bitmap!\n");
       al_destroy_display(display);
       al_destroy_timer(timer);
       return -1;
    }

	for(count = 0;count<QTD_BOMBS;count++){
		bombs[count] = al_create_bitmap(BOMB_SIZE, BOMB_SIZE);
		if(!bombs[count]) {
		   fprintf(stderr, "failed to create bomb bitmap!\n");
		   al_destroy_display(display);
		   al_destroy_timer(timer);
		   return -1;
		}
	}
	for(count = 0;count<QTD_ENEMIES;count++){
		enemies[count] = al_create_bitmap(ENEMY_SIZE, ENEMY_SIZE);
		if(!enemies[count]) {
		   fprintf(stderr, "failed to create enemy bitmap!\n");
		   al_destroy_display(display);
		   al_destroy_timer(timer);
		   return -1;
		}
	}

	sample = al_load_sample("biu.ogg");
    if (!sample){
       fprintf(stderr, "Audio clip sample not loaded!\n" );
       return -1;
    }

	al_install_keyboard();
	al_set_target_bitmap(bomber);
    al_clear_to_color(al_map_rgb(0, 0, 176));
	for(count = 0;count<QTD_BOMBS;count++){
		al_set_target_bitmap(bombs[count]);
    	al_clear_to_color(al_map_rgb(255, 0, 0));
	}
	for(count = 0;count<QTD_ENEMIES;count++){
		al_set_target_bitmap(enemies[count]);
    	al_clear_to_color(al_map_rgb(255, 0, 0));
	}
    al_set_target_bitmap(al_get_backbuffer(display));
    al_clear_to_color(al_map_rgb(0,0,0));

    event_queue = al_create_event_queue();
    if(!event_queue) {
        fprintf(stderr, "failed to create event_queue!\n");
        goto fim;
    }

    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_flip_display();
    al_start_timer(timer);

    while(jogando){
		tempo++;
        ALLEGRO_EVENT ev;
      	al_wait_for_event(event_queue, &ev);
      	if(ev.type == ALLEGRO_EVENT_TIMER) {
			for(count = 0;count < QTD_BOMBS; count++){
				if (bombs_b[count].active == true){
					int count_e;
					if (bombs_b[count].seconds == 0){
						for(count_e = 0;count_e < QTD_ENEMIES; count_e++){
							if(checkKill(&bombs_b[count],&enemies_l[count_e]) == true){
								pontuacao += pontos_kill * (pow(fase,2)/fase);
								live_enemies--;
							}
						}
						if(checkKill(&bombs_b[count],&bomber_l) == true){
							bomber_l.active = false;
							pontuacao -= pontos_kill * (pow(fase,2)/fase);
						}
						bombs_b[count].active = false;
					}
					else{
					  bombs_b[count].seconds--;
					}
			  	}
			}
			PersegueLocation(enemies_l,QTD_ENEMIES,&bomber_l);
		    MoveEnemies(enemies_l,QTD_ENEMIES,ENEMY_SIZE,(SCREEN_W - ENEMY_SIZE),(SCREEN_H - ENEMY_SIZE));
			checkDeath(&bomber_l,enemies_l,QTD_ENEMIES,BOMBER_SIZE);
            redraw = true;
        }
		else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			jogando = false;
			break;
		}
		else if(ev.type == ALLEGRO_EVENT_KEY_DOWN) {
			redraw = true;
			switch(ev.keyboard.keycode) {
				case ALLEGRO_KEY_W:
					bomber_l.y -= bomber_l.dy;
					if(bomber_l.y < 0){
						bomber_l.y = 0;
					}
				break;
				case ALLEGRO_KEY_S:
					bomber_l.y += bomber_l.dy;
					if(bomber_l.y > SCREEN_H - BOMBER_SIZE){
						bomber_l.y = SCREEN_H - BOMBER_SIZE;
					}
				break;
				case ALLEGRO_KEY_A:
					bomber_l.x -= bomber_l.dx;
					if(bomber_l.x < 0){
						bomber_l.x = 0;
					}
				break;
				case ALLEGRO_KEY_D:
					bomber_l.x += bomber_l.dx;
					if(bomber_l.x > SCREEN_W - BOMBER_SIZE){
						bomber_l.x = SCREEN_W - BOMBER_SIZE;
					}
				break;
					case ALLEGRO_KEY_SPACE:
					createBomb(bombs_b, QTD_BOMBS, &bomber_l,BOMB_TIMER,BOMB_RANGE);
					al_play_sample(sample, 0.8, 0, 1.0,ALLEGRO_PLAYMODE_ONCE, NULL);
				break;
			}
		}
		if(redraw && al_is_event_queue_empty(event_queue)) {
			draw:
			redraw = false;
			al_set_target_bitmap(al_get_backbuffer(display));
			al_clear_to_color(al_map_rgb(0,0,0));
			al_draw_bitmap(bomber, bomber_l.x, bomber_l.y, 0);
			for(count = 0;count < QTD_ENEMIES; count++){
				if(enemies_l[count].active == true){
					al_draw_bitmap(enemies[count], enemies_l[count].x, enemies_l[count].y, 0);
				}
			}
			if(bomber_l.active == true){
				for(count = 0;count < QTD_BOMBS; count++){
					if(bombs_b[count].active == true){
						al_draw_bitmap(bombs[count], bombs_b[count].x, bombs_b[count].y, 0);
					}
				}
			}
			al_flip_display();
		}
		if(live_enemies == 0 && bomber_l.active == true){
			if(fase > 1){
				pontuacao += (tempo/FPS) * pontos_tempo * sqrt(fase);
			}
			fase++;
			tempo = 0;
			//char text[20];
			//al_init_font_addon();
			//al_init_ttf_addon();
			//ALLEGRO_FONT *defaultf = al_load_font("arial.ttf", 32, 1);
			//sprintf(text, "Próxima Fase!");
			//al_draw_text(defaultf, al_map_rgb(15, 200, 30), SCREEN_W/3, SCREEN_H/2, 0,text);
			al_flip_display();
			createLocationBomber(&bomber_l,(SCREEN_W - BOMBER_SIZE),(SCREEN_H - BOMBER_SIZE),BOMBER_SIZE);
			createLocationEnemies(enemies_l,QTD_ENEMIES,&bomber_l,(SCREEN_W - ENEMY_SIZE),(SCREEN_H - ENEMY_SIZE),ENEMY_SIZE);
			defineDelta(enemies_l, QTD_ENEMIES, VEL_ENEMY, fase);
			live_enemies = QTD_ENEMIES;
			//sleep(3);
    		goto draw;
		}
		else{
			if(bomber_l.active == false && (tempo/FPS) > 2.5){
				jogando = false;
				char text[20];
				al_init_font_addon();
				al_init_ttf_addon();
				ALLEGRO_FONT *defaultf = al_load_font("arial.ttf", 32, 1);
				al_clear_to_color(al_map_rgb(0,0,0));
				sprintf(text, "Derrota!");
				al_draw_text(defaultf, al_map_rgb(15, 200, 30), SCREEN_W/3, SCREEN_H/2, 0,text);
				sprintf(text,"Pontuacao:%f",pontuacao);
				al_draw_text(defaultf, al_map_rgb(15, 200, 30), SCREEN_W/3, SCREEN_H/2 + 32, 0,text);
				sprintf(text,"Recorde:%f",returnRecorde(pontuacao));
				al_draw_text(defaultf, al_map_rgb(15, 200, 30), SCREEN_W/3, SCREEN_H/2 + 64, 0,text);
				al_flip_display();
				al_rest(5);
				goto fim;
			}
		}
	}

	fim:
	al_destroy_bitmap(bomber);
	for(count = 0;count<QTD_BOMBS;count++){
		al_destroy_bitmap(bombs[count]);
	}
	for(count = 0;count<QTD_ENEMIES;count++){
		al_destroy_bitmap(enemies[count]);
	}
	al_destroy_timer(timer);
	al_destroy_display(display);
	al_destroy_sample(sample);
	al_destroy_event_queue(event_queue);
	return 0;
}
