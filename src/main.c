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
#include "platformConfig.h"

/*******************************************************************************
 * CONSTANTES CON DEFINE
 ******************************************************************************/


#define FPS 60

#define DISPLAY_X (WIDTH)
#define DISPLAY_Y ((HEIGHT+1)*GSIZEY)

#define MENU 0
#define GAME 1
#define PAUSE 2

#define TIME 45 //cantidad de tiempo en segundos para pasar el nivel

/*******************************************************************************
 * VARIABLES GLOBALES E INICIALIZACIONES
 ******************************************************************************/

int do_exit = 0;
int keyPressed = 0;
int keyPressedValue = 0;

int flag = 0;
int contadores[HEIGHT];
uint16_t inscreenscore;

linea_t map[HEIGHT];
rana_t rana;
rana_t * pRana = &rana;

extern int winPosStates[5];

void * line(); //?? No se que es

int main (void) {
		ALLEGRO_DISPLAY * display = NULL;
		ALLEGRO_FONT * font;
		ALLEGRO_EVENT_QUEUE * event_queue;
		ALLEGRO_TIMER * timer;
	
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

		/*************** | BITMAPS | ******************************************/
		ALLEGRO_BITMAP * car1_bitmap = al_load_bitmap("../assets/Sprites/car1.png");
		ALLEGRO_BITMAP * car2_bitmap = al_load_bitmap("../assets/Sprites/car2.png");
		ALLEGRO_BITMAP * car3_bitmap = al_load_bitmap("../assets/Sprites/car3.png");
		ALLEGRO_BITMAP * car4_bitmap = al_load_bitmap("../assets/Sprites/car4.png");
		ALLEGRO_BITMAP * crash1_bitmap = al_load_bitmap("../assets/Sprites/crash1.png");
		ALLEGRO_BITMAP * crash2_bitmap = al_load_bitmap("../assets/Sprites/crash2.png");
		ALLEGRO_BITMAP * crash3_bitmap = al_load_bitmap("../assets/Sprites/crash3.png");
		ALLEGRO_BITMAP * death_bitmap = al_load_bitmap("../assets/Sprites/death.png");
		ALLEGRO_BITMAP * drown1_bitmap = al_load_bitmap("../assets/Sprites/drown1.png");
		ALLEGRO_BITMAP * drown2_bitmap = al_load_bitmap("../assets/Sprites/drown2.png");
		ALLEGRO_BITMAP * drown3_bitmap = al_load_bitmap("../assets/Sprites/drown3.png");
		ALLEGRO_BITMAP * frogIdleBack_bitmap = al_load_bitmap("../assets/Sprites/frogIdleBack.png");
		ALLEGRO_BITMAP * frogIdleFwd_bitmap = al_load_bitmap("../assets/Sprites/frogIdleFwd.png");
		ALLEGRO_BITMAP * frogIdleLeft_bitmap = al_load_bitmap("../assets/Sprites/frogIdleLeft.png");
		ALLEGRO_BITMAP * frogIdleRight_bitmap = al_load_bitmap("../assets/Sprites/frogIdleRight.png");
		ALLEGRO_BITMAP * frogLeapBack_bitmap = al_load_bitmap("../assets/Sprites/frogLeapBack.png");
		ALLEGRO_BITMAP * frogLeapFwd_bitmap = al_load_bitmap("../assets/Sprites/frogLeapFwd.png");
		ALLEGRO_BITMAP * frogLeapLeft_bitmap = al_load_bitmap("../assets/Sprites/frogLeapLeft.png");
		ALLEGRO_BITMAP * frogLeapRight_bitmap = al_load_bitmap("../assets/Sprites/frogLeapRight.png");
		ALLEGRO_BITMAP * frogWin_bitmap = al_load_bitmap("../assets/Sprites/frogWin.png");
		ALLEGRO_BITMAP * grassWinFrame_bitmap = al_load_bitmap("../assets/Sprites/grassWinFrame.png");
		ALLEGRO_BITMAP * grassWinSeparator_bitmap = al_load_bitmap("../assets/Sprites/grassWinSeparator.png");
		ALLEGRO_BITMAP * logLeft_bitmap = al_load_bitmap("../assets/Sprites/logLeft.png");
		ALLEGRO_BITMAP * logMiddle_bitmap = al_load_bitmap("../assets/Sprites/logMiddle.png");
		ALLEGRO_BITMAP * logRight_bitmap = al_load_bitmap("../assets/Sprites/logRight.png");
		ALLEGRO_BITMAP * purpleGrass_bitmap = al_load_bitmap("../assets/Sprites/purpleGrass.png");
		ALLEGRO_BITMAP * titleE_bitmap = al_load_bitmap("../assets/Sprites/titleE.png");
		ALLEGRO_BITMAP * titleF_bitmap = al_load_bitmap("../assets/Sprites/titleF.png");
		ALLEGRO_BITMAP * titleG_bitmap = al_load_bitmap("../assets/Sprites/titleG.png");
		ALLEGRO_BITMAP * titleO_bitmap = al_load_bitmap("../assets/Sprites/titleO.png");
		ALLEGRO_BITMAP * titleR_bitmap = al_load_bitmap("../assets/Sprites/titleR.png");
		ALLEGRO_BITMAP * truck_bitmap = al_load_bitmap("../assets/Sprites/truck.png");
		/**************************************************************************/

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
		int i;


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

						al_clear_to_color(al_color_name("black"));

						for (i = 0; i < HEIGHT ; i++){

							linea_t * linea = map+i;
								
							if (i == 0 || i == HEIGHT/2) //Pasto
							{

								if(i==HEIGHT/2){
									al_draw_filled_rectangle(0,(HEIGHT-i-1)*GSIZEY,
										WIDTH, (HEIGHT-i)*GSIZEY + GSIZEY/2, al_color_name("blue"));
								}
								for(int j = 0; j < WIDTH/GSIZEX; j++){
									al_draw_scaled_bitmap(purpleGrass_bitmap,0,0,16,16,
										j*GSIZEX, (HEIGHT-i) * GSIZEY, GSIZEX,GSIZEY,0);
								}
							}
							else if(i > 0 && i < HEIGHT/2){ //Calle
							
								for (int obj = 0; obj < linea->cant_obj; obj++)
								{
									float objx = linea->po[obj];

									// Autos y Camiones
									switch (linea->size)
									{
									case 1:
										switch (linea->dir)
										{
										case IZQ:
											if (i%3 == 1){
												al_draw_scaled_bitmap(car2_bitmap,0,0,16,16,
													objx, (HEIGHT-i) * GSIZEY, GSIZEX, GSIZEY, 0);
											}
											else{
												al_draw_scaled_bitmap(car1_bitmap,0,0,16,16,
													objx, (HEIGHT-i) * GSIZEY, GSIZEX, GSIZEY, 0);
											}
											break;
										case DER:
											if (i%3 == 1){
												al_draw_scaled_bitmap(car3_bitmap,0,0,16,16,
													objx, (HEIGHT-i) * GSIZEY, GSIZEX, GSIZEY, 0);
											}
											else{
												al_draw_scaled_bitmap(car4_bitmap,0,0,16,16,
													objx, (HEIGHT-i) * GSIZEY, GSIZEX, GSIZEY, 0);
											}
										}
											break;
									case 2:
										al_draw_scaled_bitmap(truck_bitmap,0,0,32,16,
											objx, (HEIGHT-i) * GSIZEY, GSIZEX *2, GSIZEY, 0);
										break;
									default:
										break;
									}
								}
								
							}					
							else if(i > HEIGHT/2 && i < HEIGHT-1){  //Agua
								//imprimo agua 
								al_draw_filled_rectangle(0,(HEIGHT-i-1)*GSIZEY,
								WIDTH, (HEIGHT-i)*GSIZEY, al_color_name("blue"));


								//imprimo troncos
								for (int obj = 0; obj < linea->cant_obj; obj++)
								{
									float objx = linea->po[obj];
									for (int size = 0; size < linea->size; size++)
									{
										if(size == 0){
											al_draw_scaled_bitmap(logLeft_bitmap,0,0,16,16,
												objx, (HEIGHT-i-0.25) * GSIZEY, GSIZEX, GSIZEY, 0);
										}
										else if (size == linea->size - 1){
											al_draw_scaled_bitmap(logRight_bitmap,0,0,16,16,
												(objx+GSIZEX*size), (HEIGHT-i-0.25) * GSIZEY, GSIZEX,GSIZEY,0);
										}
										else{
											al_draw_scaled_bitmap(logMiddle_bitmap,0,0,16,16,
												(objx+GSIZEX*size), (HEIGHT-i-0.25) * GSIZEY, GSIZEX,GSIZEY,0);
										}
									}
								}
							}
							else if(i == HEIGHT - 1){ //ultima linea
								al_draw_filled_rectangle(0, (HEIGHT-i)*GSIZEY,
									WIDTH, (HEIGHT-i-1)*GSIZEY, al_color_name("blue"));

								// Dibujo la ultima linea
								//Espacios libres
								al_draw_scaled_bitmap(grassWinFrame_bitmap,0,0,32,32,
										WINPOS1, (HEIGHT-i-1) * GSIZEY, GSIZEX *2,GSIZEY*2,0);
								al_draw_scaled_bitmap(grassWinFrame_bitmap,0,0,32,32,
										WINPOS2, (HEIGHT-i-1) * GSIZEY, GSIZEX*2,GSIZEY*2,0);
								al_draw_scaled_bitmap(grassWinFrame_bitmap,0,0,32,32,
										WINPOS3, (HEIGHT-i-1) * GSIZEY, GSIZEX*2,GSIZEY*2,0);
								al_draw_scaled_bitmap(grassWinFrame_bitmap,0,0,32,32,
										WINPOS4, (HEIGHT-i-1) * GSIZEY, GSIZEX*2,GSIZEY*2,0);
								al_draw_scaled_bitmap(grassWinFrame_bitmap,0,0,32,32,
										WINPOS5, (HEIGHT-i-1) * GSIZEY, GSIZEX*2,GSIZEY*2,0);
								
								//Separadores
								al_draw_scaled_bitmap(grassWinSeparator_bitmap,0,0,16,32,
									GSIZEX*2,(HEIGHT-i-1) * GSIZEY, GSIZEX, GSIZEY*2,0);
								al_draw_scaled_bitmap(grassWinSeparator_bitmap,0,0,16,32,
									GSIZEX*2 + GSIZEX/2,(HEIGHT-i-1) * GSIZEY, GSIZEX, GSIZEY*2,0);
								al_draw_scaled_bitmap(grassWinSeparator_bitmap,0,0,16,32,
									WINPOS2+GSIZEX*2,(HEIGHT-i-1) * GSIZEY, GSIZEX, GSIZEY*2,0);
								al_draw_scaled_bitmap(grassWinSeparator_bitmap,0,0,16,32,
									WINPOS2 +GSIZEX*2 + GSIZEX/2,(HEIGHT-i-1) * GSIZEY, GSIZEX, GSIZEY*2,0);
								al_draw_scaled_bitmap(grassWinSeparator_bitmap,0,0,16,32,
									WINPOS3+GSIZEX*2,(HEIGHT-i-1) * GSIZEY, GSIZEX, GSIZEY*2,0);
								al_draw_scaled_bitmap(grassWinSeparator_bitmap,0,0,16,32,
									WINPOS3 +GSIZEX*2+ GSIZEX/2,(HEIGHT-i-1) * GSIZEY, GSIZEX, GSIZEY*2,0);
								al_draw_scaled_bitmap(grassWinSeparator_bitmap,0,0,16,32,
									WINPOS4+GSIZEX*2,(HEIGHT-i-1) * GSIZEY, GSIZEX, GSIZEY*2,0);
								al_draw_scaled_bitmap(grassWinSeparator_bitmap,0,0,16,32,
									WINPOS4 + GSIZEX*2 + GSIZEX/2,(HEIGHT-i-1) * GSIZEY, GSIZEX, GSIZEY*2,0);

								/// Dibujo ranas que ya llegaron
								if(winPosStates[0] == WIN_OCC){
									al_draw_scaled_bitmap(frogWin_bitmap,0,0,16,16,
										WINPOS1+0.5*GSIZEX, GSIZEY *0.5, GSIZEX,GSIZEY,0);
								}
								if(winPosStates[1] == WIN_OCC){
									al_draw_scaled_bitmap(frogWin_bitmap,0,0,16,16,
										WINPOS2+0.5*GSIZEX, GSIZEY *0.5, GSIZEX,GSIZEY,0);
								}
								if(winPosStates[2] == WIN_OCC){
									al_draw_scaled_bitmap(frogWin_bitmap,0,0,16,16,
										WINPOS3+0.5*GSIZEX, GSIZEY *0.5, GSIZEX,GSIZEY,0);
								}
								if(winPosStates[3] == WIN_OCC){
									al_draw_scaled_bitmap(frogWin_bitmap,0,0,16,16,
										WINPOS4+0.5*GSIZEX, GSIZEY *0.5, GSIZEX,GSIZEY,0);
								}
								if(winPosStates[4] == WIN_OCC){
									al_draw_scaled_bitmap(frogWin_bitmap,0,0,16,16,
										WINPOS5+0.5*GSIZEX, GSIZEY *0.5, GSIZEX,GSIZEY,0);
								}
								
							}	

							float ranax = pRana->posx;
							float ranay = pRana->posy;

							al_draw_scaled_bitmap(frogIdleFwd_bitmap,0,0,16,16,
									 		ranax*GSIZEX, (ranay-i) * GSIZEY, GSIZEX,GSIZEY,0);

							/* movimiento de los objetos segun la velocidad */
							if(linea->cant_obj > 0)
							{
								switch (linea->v)
								{
								case 1:
									moveLine(linea, i, pRana);
									break;
								case 2:
									moveLine(linea, i, pRana);
									moveLine(linea, i, pRana);
									break;
								case 3:
									moveLine(linea, i, pRana);
									moveLine(linea, i, pRana);
									moveLine(linea, i, pRana);
									break;
								case 4:
									moveLine(linea, i, pRana);
									moveLine(linea, i, pRana);
									moveLine(linea, i, pRana);
									moveLine(linea, i, pRana);
									break;
								default:
									break;
								}
							}

							RanaCollisions(pRana, &map[pRana->posy]);
						}
						
						fpsCounter++;
						al_flip_display();
					}
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
		al_destroy_bitmap(purpleGrass_bitmap);
		al_destroy_event_queue(event_queue);
		al_destroy_font(font);
		al_destroy_timer(timer);

	return 0;
}
