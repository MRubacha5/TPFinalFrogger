/*******************************************************************************
 * HEADERS
 ******************************************************************************/

#include <stdlib.h>
#include <stdio.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_image.h>

#include "worldData.h"
#include "score.h"
#include "rana.h"
#include "movement.h"

/*******************************************************************************
 * CONSTANTES CON DEFINE
 ******************************************************************************/

#define GSIZE 50
#define FPS 60

#define DISPLAY_X (GSIZE*WIDTH)
#define DISPLAY_Y (GSIZE*HEIGHT)

#define MENU 0
#define GAME 1
#define PAUSE 2

#define TIME 45 //cantidad de tiempo en segundos para pasar el nivel

void * line();

int do_exit = 0;
int keyPressed = 0;
int keyPressedValue = 0;

int flag = 0;
int contadores[HEIGHT];
uint16_t inscreenscore;

linea_t map[HEIGHT];
rana_t rana;
rana_t * pRana = &rana;

int main (void) {

		ALLEGRO_DISPLAY * display = NULL;
		ALLEGRO_FONT * font;
		ALLEGRO_EVENT_QUEUE * event_queue;
		ALLEGRO_TIMER * timer;
		ALLEGRO_BITMAP * background;

		uint8_t time_left = 20; //hardcodeado solo para probar funcion  

		if(!al_init()){
		    	fprintf(stderr, "failed to initialize allegro!\n");
		    	return -1;
		}

	    display = al_create_display(DISPLAY_X, DISPLAY_Y);

	    if(!display){
	        	fprintf(stderr, "failed to create\n");
	        	return -1;
	    }

		if (!al_install_keyboard()) {
		    fprintf(stderr, "failed to initialize the keyboard!\n");
		    return -1;
		}

	    event_queue = al_create_event_queue();
	    if (!event_queue) {
	        printf("failed to create event_queue!\n");
	        al_destroy_display(display);
	        return -1;
	    }

	    timer = al_create_timer(1.0/FPS);
	    al_init_font_addon();
	    if(!timer){
	    	printf("failed to create timer!\n");
	    	al_destroy_display(display);
	    	return -1;
	    }

	    font = al_create_builtin_font();
	    if (!font) {
	    	printf("failed to create event_queue!\n");
	    	al_destroy_display(display);
	    	return -1;
	    }

	    if (!al_install_mouse()) {
	        printf("failed to initialize the mouse!\n");
	        return -1;
        }

	    if (!al_init_primitives_addon()) {
	    	printf("failed to initialize primitives!\n");
	        return -1;
        }

		if(!al_init_image_addon()){
			printf("failed to inicialize image\n");
			return -1;
		}

		background = al_load_bitmap("background.jpg");

		al_register_event_source(event_queue, al_get_display_event_source(display));
		al_register_event_source(event_queue, al_get_timer_event_source(timer));
		al_register_event_source(event_queue, al_get_keyboard_event_source());
		al_register_event_source(event_queue, al_get_mouse_event_source());

		al_start_timer(timer);

		al_clear_to_color(al_color_name("black"));

        al_flip_display();

		int mouse_x=0;
		int mouse_y=0;
		int leftClick = 0;
		int fpsCounter = 0;
		int screen = MENU;
		int optionSelected = 0;
		int i, c;


		while(!do_exit){

			ALLEGRO_EVENT ev;
			

			if(al_get_next_event(event_queue, &ev)){

				if(ev.type == ALLEGRO_EVENT_TIMER){

					switch (screen)
					{
					case MENU:
						al_clear_to_color(al_color_name("black"));
						al_draw_filled_rectangle(DISPLAY_X/8, DISPLAY_Y/8, DISPLAY_X*7/8, DISPLAY_Y*3/8, al_color_name("white"));
						al_draw_filled_rectangle(DISPLAY_X/8, DISPLAY_Y*5/8, DISPLAY_X*7/8, DISPLAY_Y*7/8, al_color_name("white"));
						if(mouse_x > DISPLAY_X/8 && mouse_x < DISPLAY_X*7/8){
							if(mouse_y > DISPLAY_Y/8 && mouse_y < DISPLAY_Y*3/8){
								al_draw_filled_rectangle(DISPLAY_X/8, DISPLAY_Y/8, DISPLAY_X*7/8, DISPLAY_Y*3/8, al_color_name("grey"));
								if(leftClick){
									leftClick = 0;
									screen = GAME;
									createMap(map,0);
									spawnRana(map, pRana);
								}
							}
							else if(mouse_y > DISPLAY_Y*5/8 && mouse_y < DISPLAY_Y*7/8){
								al_draw_filled_rectangle(DISPLAY_X/8, DISPLAY_Y*5/8, DISPLAY_X*7/8, DISPLAY_Y*7/8, al_color_name("grey"));
								if(leftClick){
									leftClick = 0;
									do_exit = 1;
								}
							}
						}
						al_draw_text(font, al_color_name("black"), DISPLAY_X/2, DISPLAY_Y/4, ALLEGRO_ALIGN_CENTER, "START");
						al_draw_text(font, al_color_name("black"), DISPLAY_X/2, DISPLAY_Y*3/4, ALLEGRO_ALIGN_CENTER, "QUIT");
						al_flip_display();
						break;
					case PAUSE:
						al_clear_to_color(al_color_name("black"));
						al_draw_filled_rectangle(DISPLAY_X/8, DISPLAY_Y/8, DISPLAY_X*7/8, DISPLAY_Y*3/8, al_color_name("white"));
						al_draw_filled_rectangle(DISPLAY_X/8, DISPLAY_Y*5/8, DISPLAY_X*7/8, DISPLAY_Y*7/8, al_color_name("white"));
						if(mouse_x > DISPLAY_X/8 && mouse_x < DISPLAY_X*7/8){
							if(mouse_y > DISPLAY_Y/8 && mouse_y < DISPLAY_Y*3/8){
								al_draw_filled_rectangle(DISPLAY_X/8, DISPLAY_Y/8, DISPLAY_X*7/8, DISPLAY_Y*3/8, al_color_name("grey"));
								if(leftClick){
									leftClick = 0;
									screen = GAME;
								}
							}
							else if(mouse_y > DISPLAY_Y*5/8 && mouse_y < DISPLAY_Y*7/8){
								al_draw_filled_rectangle(DISPLAY_X/8, DISPLAY_Y*5/8, DISPLAY_X*7/8, DISPLAY_Y*7/8, al_color_name("grey"));
								if(leftClick){
									leftClick = 0;
									screen = MENU;
								}
							}
						}
						al_draw_text(font, al_color_name("black"), DISPLAY_X/2, DISPLAY_Y/4, ALLEGRO_ALIGN_CENTER, "CONTINUE");
						al_draw_text(font, al_color_name("black"), DISPLAY_X/2, DISPLAY_Y*3/4, ALLEGRO_ALIGN_CENTER, "MENU");
						al_flip_display();
						break;
					case GAME:
						if(fpsCounter >= FPS){
							fpsCounter = 0;
						}
						for (i = 0; i < HEIGHT ; i++){

							linea_t * linea = map+i;
							
							for(c = 0 ; c < WIDTH ; c++){
								for(c = 0 ; c < WIDTH ; c++){
								
								if (i == 0) //posicion inicial
								{
									//imprimo piso
								}
								else if(i > 0 && i < HEIGHT / 2){ //Calle
									//imprimo calle si es 1
									//imprimo auto si es 0
								}
								else if(i == HEIGHT/2){ //Pasto
									//imprimo pasto
								}					
								else if(i > HEIGHT/2 && i < HEIGHT-1){ //Agua
									//imprimo agua si es 0
									//imprimo tronco si es 1
								}
								else if(i == HEIGHT - 1){
									//imprimo lilypad si es 1;
									//imprimo pasto si es 0
								}		

							}

							/* esto es para modificar el movimient segun la velocidad */
							if(linea->cant_obj > 0){
								switch (linea->v)
								{
								case 1:
									if(fpsCounter == 0){
										moveLine(linea, i, pRana);
									}
									break;
								case 2:
									if(fpsCounter == FPS/2 || fpsCounter == 0){
										moveLine(linea, i, pRana);
									}
									break;
								case 3:
									if(fpsCounter == FPS/3 || fpsCounter == FPS*2/3 || fpsCounter == 0){
										moveLine(linea, i, pRana);
									}
								}
							}
							RanaCollisions(pRana, &map[pRana->posy]);
						}
						
						fpsCounter++;
						break;
					}
					
					al_flip_display();
					
										
                    
		    	}
				else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
					do_exit = true;
		    	}
				else if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
					leftClick = 1;
				}
				else if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP){
					leftClick = 0;
				}
				else if(ev.type == ALLEGRO_EVENT_MOUSE_AXES){
					mouse_x = ev.mouse.x;
					mouse_y = ev.mouse.y;
		    	}
                else if(ev.type == ALLEGRO_EVENT_KEY_DOWN){
					
					if(screen == GAME){
						switch(ev.keyboard.keycode){
							case ALLEGRO_KEY_ESCAPE:
								screen = PAUSE;
								break;
							case ALLEGRO_KEY_DOWN:
								MoveRana(pRana, DOWN, map+rana.posy);
								
								break;
							case ALLEGRO_KEY_UP:
								MoveRana(pRana, UP, map+rana.posy);
								
								//Cada vez que va para arriba se fija si se debe inc score
								//inscreenscore = ct_score(rana.posy,TIME,time_left,0,rana.vidas,0);
								//printf ("%u\n",inscreenscore);

								break;
							case ALLEGRO_KEY_LEFT:
								MoveRana(pRana, LEFT, map+rana.posy);
								
								break;
							case ALLEGRO_KEY_RIGHT:
								MoveRana(pRana, RIGHT, map+rana.posy);
								
								break;

						}
					
					}
					else if(screen == PAUSE && ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE){
							screen = GAME;
					}
			    }
		    }
		}
		al_destroy_display(display);
		al_destroy_bitmap(background);
		al_destroy_event_queue(event_queue);
		al_destroy_font(font);
		al_destroy_timer(timer);

	return 0;
}
