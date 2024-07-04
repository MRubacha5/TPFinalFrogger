/*codigo para allegro*/
#include "Objetos.h"
#include "Rana.h"
#include "score.h"
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_image.h>
#include <stdio.h>
#include <pthread.h>

#define GSIZE 50
#define FPS 60

#define DISPLAY_X (GSIZE*WIDTH)
#define DISPLAY_Y (GSIZE*HEIGHT)

#define MENU 0
#define GAME 1
#define PAUSE 2

#define TIME 45 //cant de tiempo en segundos para pasar el nivel

void * line();

int do_exit = 0;
int keyPressed = 0;

linea_t * pl;
rana_t rana = {.posx=WIDTH/2, .posy=0, .vidas=3};

int tnum[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22};

int flag = 0;
int contadores[HEIGHT];
uint16_t inscreenscore;


int main (void) {

		ALLEGRO_DISPLAY * display = NULL;
		ALLEGRO_FONT * font;
		ALLEGRO_EVENT_QUEUE * event_queue;
		ALLEGRO_TIMER * timer;
		ALLEGRO_BITMAP * background;

		pthread_t tid[HEIGHT];
		
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
			printf("falied to inicialize image\n");
			return -1;
		}

		background = al_load_bitmap("background.jpg");

		al_register_event_source(event_queue, al_get_display_event_source(display));
		al_register_event_source(event_queue, al_get_timer_event_source(timer));
		al_register_event_source(event_queue, al_get_keyboard_event_source());
		al_register_event_source(event_queue, al_get_mouse_event_source());

		al_start_timer(timer);

		al_clear_to_color(al_color_name("black"));

		pl = CreateWorld(HEIGHT, WIDTH);
		CreateObject(pl+3);
		CreateObject(pl+4);
		CreateObject(pl+5);

        al_flip_display();

		int fpsCounter = 0;
		int screen = GAME;
		int optionSelected = 0;
		int i, c;

		while(!do_exit){

			ALLEGRO_EVENT ev;

			if(al_get_next_event(event_queue, &ev)){

				if(ev.type == ALLEGRO_EVENT_TIMER){
					
					//al_draw_bitmap(background, 0, 0, 0);
					//al_fwrite16le(background, inscreenscore);

					

					switch (screen)
					{
					case MENU:
						/* code */
						break;
					case GAME:
						if(fpsCounter >= FPS){
							fpsCounter = 0;
						}
						for (i = 0; i < HEIGHT; i++){
							linea_t * linea = pl+i;

							if(linea->cant_obj > 0){
								switch (linea->v)
								{
								case 1:
									if(fpsCounter == 0){
										MoveObject(linea);
									}
									break;
								case 2:
									if(fpsCounter == FPS/2 || fpsCounter == 0){
										MoveObject(linea);
									}
									break;
								case 3:
									if(fpsCounter == FPS/3 || fpsCounter == FPS*2/3 || fpsCounter == 0){
										MoveObject(linea);
									}
								}
							}

							for(c = 0 ; c < WIDTH ; c++){
								if(i <= HEIGHT/2){
									al_draw_filled_rectangle(c * GSIZE, i*GSIZE, (c+1) * GSIZE, (i+1)*GSIZE,al_color_name("blue"));
									
									for(int j = 0 ; j<linea->cant_obj ; j++){
										for(int m = 0 ; m<linea->size ; m++){
											ALLEGRO_COLOR color;
											if(m == 0 || m == linea->size-1){
												color = al_color_name("brown");
											}
											else{
												color = al_color_name("yellow");
											}

											al_draw_filled_rectangle((((linea->po)+j)->x+m) * GSIZE, i*GSIZE, ((linea->po+j)->x+m+1) * GSIZE, (i+1)*GSIZE,color);
										}
									}
								}
								else{
									al_draw_filled_rectangle(c * GSIZE, i*GSIZE, (c+1) * GSIZE, (i+1)*GSIZE,al_color_name("black"));
								}
								
							}
						}
						
						fpsCounter++;
						break;
					case PAUSE:
						break;
					}
					
					al_flip_display();
					
										
                    
		    	}
				else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
					do_exit = true;
		    	}
				else if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
					//leftClick = 1;
				}
				else if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP){
					//leftClick = 0;
				}
				else if(ev.type == ALLEGRO_EVENT_MOUSE_AXES){
					//x = (ev.mouse.x / (DISPLAY_X/COL)) + 1;
					//y = (ev.mouse.y / (DISPLAY_Y/ROW)) + 1;
		    	}
                else if(ev.type == ALLEGRO_EVENT_KEY_DOWN){

                    switch(ev.keyboard.keycode){
                        case ALLEGRO_KEY_DOWN:
                            //MoveRana(&rana, DOWN);
                            keyPressed = 1;
                            break;
                        case ALLEGRO_KEY_UP:
                            //MoveRana(&rana, UP);
                            keyPressed = 1;
							//Cada vez que va para arriba se fija si se debe inc score
							inscreenscore = ct_score(rana.posy,TIME,time_left,0,rana.vidas,0);
							printf ("%u\n",inscreenscore);

                            break;
                        case ALLEGRO_KEY_LEFT:
                            //MoveRana(&rana, LEFT);
                            keyPressed = 1;
                            break;
                        case ALLEGRO_KEY_RIGHT:
                            //MoveRana(&rana, RIGHT);
                            keyPressed = 1;
                            break;

                    }
			    }
		    }
		}
        FreeWorldData(pl, HEIGHT);
		al_destroy_display(display);
		al_destroy_bitmap(background);
		al_destroy_event_queue(event_queue);
		al_destroy_font(font);
		al_destroy_timer(timer);

	return 0;
}
