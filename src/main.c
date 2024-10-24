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

#define DISPLAY_X (WIDTH)
#define DISPLAY_Y ((HEIGHT+4)*GSIZEY)

#define MENU 0
#define GAME 1
#define PAUSE 2
#define GAMEOVER 3
#define GAMEOVERTOP 4

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
extern int vidas;
unsigned int timeLeft = START_TIME; // valor en segundos 

int main (void) {

		/**********************
		 * INICIALIZO ALLEGRO *
		 **********************/
		ALLEGRO_DISPLAY * display = NULL;
		ALLEGRO_FONT * font;
		ALLEGRO_EVENT_QUEUE * event_queue;
		ALLEGRO_TIMER * timer;

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
		ALLEGRO_BITMAP * yellowT_bitmap = al_load_bitmap("../assets/Sprites/yellowT.png");
		ALLEGRO_BITMAP * yellowI_bitmap = al_load_bitmap("../assets/Sprites/yellowI.png");
		ALLEGRO_BITMAP * yellowM_bitmap = al_load_bitmap("../assets/Sprites/yellowM.png");
		ALLEGRO_BITMAP * yellowE_bitmap = al_load_bitmap("../assets/Sprites/yellowE.png");

		// Variable que se va a utilizar para guardar el estado de la rana (direccion y animacion)
		ALLEGRO_BITMAP * frog_bitmap = frogIdleFwd_bitmap;
		/**************************************************************************/

		al_register_event_source(event_queue, al_get_display_event_source(display));
		al_register_event_source(event_queue, al_get_timer_event_source(timer));
		al_register_event_source(event_queue, al_get_keyboard_event_source());
		al_register_event_source(event_queue, al_get_mouse_event_source());

		al_start_timer(timer);

		al_clear_to_color(al_color_name("black"));

        al_flip_display();

		/***********************
		* INICIALIZO VARIABLES *
		************************/
		int mouse_x=0;
		int mouse_y=0;
		int leftClick = 0;
		int fpsCounter = 0;
		int screen = MENU;
		int optionSelected = 0;
		int i;

		// Valores para movimiento. Se encargan de hacer que el movimiento se vea fluido. Funcionan tanto como flags como contadores
		uint8_t isMovingRight = 0, isMovingLeft = 0, isMovingUp = 0, isMovingDown = 0; 

		//Se setea como FPS cuando hay una muerte. Inhibe el movimiento y el contador hasta que termine la animacion
		uint8_t deathTimer = 0; 

		/*******************
		* SCREEN LOOP CODE *
		********************/
		while(!do_exit){

			ALLEGRO_EVENT ev;
			

			if(al_get_next_event(event_queue, &ev)){

				if(ev.type == ALLEGRO_EVENT_TIMER){

					switch (screen)
					{
					case MENU:
						// Fondo
						al_clear_to_color(al_color_name("darkblue"));
						
						// Letras de FROGGER
						al_draw_scaled_bitmap(titleF_bitmap,0,0,32,32,
									GSIZEX*1.7, 2*GSIZEY, GSIZEX*3.0,GSIZEY*3.0,0);
						al_draw_scaled_bitmap(titleR_bitmap,0,0,32,32,
									GSIZEX*3.2, 2*GSIZEY, GSIZEX*3.0,GSIZEY*3.0,0);
						al_draw_scaled_bitmap(titleO_bitmap,0,0,32,32,
									GSIZEX*4.7, 2*GSIZEY, GSIZEX*3.0,GSIZEY*3.0,0);
						al_draw_scaled_bitmap(titleG_bitmap,0,0,32,32,
									GSIZEX*6.2, 2*GSIZEY, GSIZEX*3.0,GSIZEY*3.0,0);
						al_draw_scaled_bitmap(titleG_bitmap,0,0,32,32,
									GSIZEX*7.7, 2*GSIZEY, GSIZEX*3.0,GSIZEY*3.0,0);
						al_draw_scaled_bitmap(titleE_bitmap,0,0,32,32,
									GSIZEX*9.2, 2*GSIZEY, GSIZEX*3.0,GSIZEY*3.0,0);
						al_draw_scaled_bitmap(titleR_bitmap,0,0,32,32,
									GSIZEX*10.7, 2*GSIZEY, GSIZEX*3.0,GSIZEY*3.0,0);
						
						// Botones
						al_draw_filled_rectangle(DISPLAY_X/8, DISPLAY_Y*3/8, DISPLAY_X*7/8, DISPLAY_Y*5/8, al_color_name("white"));
						al_draw_filled_rectangle(DISPLAY_X/8, DISPLAY_Y*5/8, DISPLAY_X*7/8, DISPLAY_Y*7/8, al_color_name("white"));
						
						// Los Botones cambian de color cuando el mouse esta por encima
						if(mouse_x > DISPLAY_X/8 && mouse_x < DISPLAY_X*7/8){
							if(mouse_y > DISPLAY_Y*3/8 && mouse_y < DISPLAY_Y*5/8){
								al_draw_filled_rectangle(DISPLAY_X/8, DISPLAY_Y*3/8, DISPLAY_X*7/8, DISPLAY_Y*5/8, al_color_name("grey"));
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
						al_draw_text(font, al_color_name("black"), DISPLAY_X/2, DISPLAY_Y/2, ALLEGRO_ALIGN_CENTER, "START");
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
							if(!deathTimer)
							{
								timeLeft--;
							}
							
						}
						
						al_clear_to_color(al_color_name("black"));

						/***************
						* DIBUJO EL UI *
						****************/
						// dibujo las ranas que simbolizan vidas
						for (int a = 0; a < vidas; a++)
						{
							al_draw_scaled_bitmap(frogIdleFwd_bitmap,0,0,16,16,
									GSIZEX*(a+1), (HEIGHT +1) * GSIZEY, GSIZEX,GSIZEY,0);
						}
						
						//dibujo el tiempo restante
						/*COMENTADO PORQUE ALLEGRO ESTA SIENDO CAPRICHOSO
						al_draw_scaled_bitmap(yellowT_bitmap,0,0,8,8,
									GSIZEX, (HEIGHT +2) * GSIZEY, GSIZEX/2.0,GSIZEY/2.0,0);
						al_draw_scaled_bitmap(yellowI_bitmap,0,0,8,8,
									GSIZEX*1.5, (HEIGHT +2) * GSIZEY, GSIZEX/2.0,GSIZEY/2.0,0);
						al_draw_scaled_bitmap(yellowM_bitmap,0,0,8,8,
									GSIZEX*2, (HEIGHT +2) * GSIZEY, GSIZEX/2.0,GSIZEY/2.0,0);
						al_draw_scaled_bitmap(yellowE_bitmap,0,0,8,8,
									GSIZEX*2.5, (HEIGHT +2) * GSIZEY, GSIZEX/2.0,GSIZEY/2.0,0);
						*/
						if (timeLeft > 0)
						{
							
							if (timeLeft > 30)
							{
								al_draw_filled_rectangle(GSIZEX*5,(HEIGHT + 2)*GSIZEY,
										5*GSIZEX + ((timeLeft) * GSIZEX/10.0) , (HEIGHT+2.5)*GSIZEY, al_color_name("green"));
							}
							else if (timeLeft > 10)
							{
								al_draw_filled_rectangle(GSIZEX*5,(HEIGHT + 2)*GSIZEY,
										5*GSIZEX + ((timeLeft) * GSIZEX/10.0) , (HEIGHT+2.5)*GSIZEY, al_color_name("yellow"));
							}
							else 
							{
								al_draw_filled_rectangle(GSIZEX*5,(HEIGHT + 2)*GSIZEY,
										5*GSIZEX + ((timeLeft) * GSIZEX/10.0) , (HEIGHT+2.5)*GSIZEY, al_color_name("red"));
							}
							
						}
						else if (deathTimer == 0)
						{
							deathTimer = FPS;
						}

						//dibujo el score (TBD)
						
						/*****************************
						* DIBUJO LAS LINEAS DEL MAPA *
						******************************/
						for (i = 0; i < HEIGHT ; i++){

							linea_t * linea = map+i;
							
							/******************
							* LINEAS DE PASTO *
							*******************/
							if (i == 0 || i == HEIGHT/2) 
							{

								if(i==HEIGHT/2){
									al_draw_filled_rectangle(0,(HEIGHT-i-1)*GSIZEY,
										WIDTH, (HEIGHT-i)*GSIZEY + GSIZEY/2.0, al_color_name("darkblue"));
								}
								for(int j = 0; j < WIDTH/GSIZEX; j++){
									al_draw_scaled_bitmap(purpleGrass_bitmap,0,0,16,16,
										j*GSIZEX, (HEIGHT-i) * GSIZEY, GSIZEX,GSIZEY,0);
								}
							}

							/******************
							* LINEAS DE CALLE *
							*******************/
							else if(i > 0 && i < HEIGHT/2){ 
							
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

							/******************
							* LINEAS DE AGUA *
							*******************/			
							else if(i > HEIGHT/2 && i < HEIGHT-1){ 
								//imprimo el agua en si 
								al_draw_filled_rectangle(0,(HEIGHT-i-1)*GSIZEY,
								WIDTH, (HEIGHT-i)*GSIZEY, al_color_name("darkblue"));


								//imprimo troncos
								for (int obj = 0; obj < linea->cant_obj; obj++)
								{
									float objx = linea->po[obj];
									for (int size = 0; size < linea->size; size++)
									{
										if(size == 0){
											al_draw_scaled_bitmap(logLeft_bitmap,0,0,16,16,
												objx, (HEIGHT-i) * GSIZEY, GSIZEX, GSIZEY, 0);
										}
										else if (size == linea->size - 1){
											al_draw_scaled_bitmap(logRight_bitmap,0,0,16,16,
												(objx+GSIZEX*size), (HEIGHT-i) * GSIZEY, GSIZEX,GSIZEY,0);
										}
										else{
											al_draw_scaled_bitmap(logMiddle_bitmap,0,0,16,16,
												(objx+GSIZEX*size), (HEIGHT-i) * GSIZEY, GSIZEX,GSIZEY,0);
										}
									}
								}
							}

							/****************************************************************************
							* ULTIMA LINEA DEL MAPA: LOS OBJETIVOS, SEPARADORES Y RANAS QUE YA LLEGARON *
							*****************************************************************************/
							else if(i == HEIGHT - 1){
								al_draw_filled_rectangle(0, (HEIGHT-i)*GSIZEY,
									WIDTH, (HEIGHT-i-1)*GSIZEY, al_color_name("darkblue"));

								//Espacios libres
								al_draw_scaled_bitmap(grassWinFrame_bitmap,0,0,32,24,
										WINPOS1, (HEIGHT-i-1) * GSIZEY, GSIZEX *2,GSIZEY*2,0);
								al_draw_scaled_bitmap(grassWinFrame_bitmap,0,0,32,24,
										WINPOS2, (HEIGHT-i-1) * GSIZEY, GSIZEX*2,GSIZEY*2,0);
								al_draw_scaled_bitmap(grassWinFrame_bitmap,0,0,32,24,
										WINPOS3, (HEIGHT-i-1) * GSIZEY, GSIZEX*2,GSIZEY*2,0);
								al_draw_scaled_bitmap(grassWinFrame_bitmap,0,0,32,24,
										WINPOS4, (HEIGHT-i-1) * GSIZEY, GSIZEX*2,GSIZEY*2,0);
								al_draw_scaled_bitmap(grassWinFrame_bitmap,0,0,32,24,
										WINPOS5, (HEIGHT-i-1) * GSIZEY, GSIZEX*2,GSIZEY*2,0);
								
								//Separadores
								al_draw_scaled_bitmap(grassWinSeparator_bitmap,0,0,16,24,
									GSIZEX*2,(HEIGHT-i-1) * GSIZEY, GSIZEX, GSIZEY*2,0);
								al_draw_scaled_bitmap(grassWinSeparator_bitmap,0,0,16,24,
									GSIZEX*2 + GSIZEX/2.0,(HEIGHT-i-1) * GSIZEY, GSIZEX, GSIZEY*2,0);
								al_draw_scaled_bitmap(grassWinSeparator_bitmap,0,0,16,24,
									WINPOS2+GSIZEX*2,(HEIGHT-i-1) * GSIZEY, GSIZEX, GSIZEY*2,0);
								al_draw_scaled_bitmap(grassWinSeparator_bitmap,0,0,16,24,
									WINPOS2 +GSIZEX*2 + GSIZEX/2.0,(HEIGHT-i-1) * GSIZEY, GSIZEX, GSIZEY*2,0);
								al_draw_scaled_bitmap(grassWinSeparator_bitmap,0,0,16,24,
									WINPOS3+GSIZEX*2,(HEIGHT-i-1) * GSIZEY, GSIZEX, GSIZEY*2,0);
								al_draw_scaled_bitmap(grassWinSeparator_bitmap,0,0,16,24,
									WINPOS3 +GSIZEX*2+ GSIZEX/2.0,(HEIGHT-i-1) * GSIZEY, GSIZEX, GSIZEY*2,0);
								al_draw_scaled_bitmap(grassWinSeparator_bitmap,0,0,16,24,
									WINPOS4+GSIZEX*2,(HEIGHT-i-1) * GSIZEY, GSIZEX, GSIZEY*2,0);
								al_draw_scaled_bitmap(grassWinSeparator_bitmap,0,0,16,24,
									WINPOS4 + GSIZEX*2 + GSIZEX/2.0,(HEIGHT-i-1) * GSIZEY, GSIZEX, GSIZEY*2,0);

								/// Dibujo ranas que ya llegaron
								if(winPosStates[0] == WIN_OCC){
									al_draw_scaled_bitmap(frogWin_bitmap,0,0,16,16,
										WINPOS1+0.5*GSIZEX, GSIZEY *0.75, GSIZEX,GSIZEY,0);
								}
								if(winPosStates[1] == WIN_OCC){
									al_draw_scaled_bitmap(frogWin_bitmap,0,0,16,16,
										WINPOS2+0.5*GSIZEX, GSIZEY *0.75, GSIZEX,GSIZEY,0);
								}
								if(winPosStates[2] == WIN_OCC){
									al_draw_scaled_bitmap(frogWin_bitmap,0,0,16,16,
										WINPOS3+0.5*GSIZEX, GSIZEY *0.75, GSIZEX,GSIZEY,0);
								}
								if(winPosStates[3] == WIN_OCC){
									al_draw_scaled_bitmap(frogWin_bitmap,0,0,16,16,
										WINPOS4+0.5*GSIZEX, GSIZEY *0.75, GSIZEX,GSIZEY,0);
								}
								if(winPosStates[4] == WIN_OCC){
									al_draw_scaled_bitmap(frogWin_bitmap,0,0,16,16,
										WINPOS5+0.5*GSIZEX, GSIZEY *0.75, GSIZEX,GSIZEY,0);
								}
								
							}	

							
							long int ranax = pRana->posx;
							long int ranay = pRana->posy;
							long int deathX;
							long int deathY;

							/**********************************************************************************************************************
							 * DIBUJO LA RANA Y LA MUEVO CON UNA CADENA DE IFS PARA PERMITIR FLUIDEZ EN LOS MOVIMIENTOS SIN COMPROMETER LA LOGICA *
							 * ********************************************************************************************************************/

							// SI LA RANA ESTA MURIENDO, NO LA DIBUJO
							if (deathTimer == FPS) 
							{
								//Inhibo el movimiento de la rana y guardo su posicion de muerte
								isMovingDown = 0;
								isMovingUp = 0;
								isMovingLeft = 0;
								isMovingRight = 0;
								deathX = pRana->posx;
								deathY = pRana->posy;

								if (fpsCounter % 12 == 0)
								{
									deathTimer--;
								}
								
							}
							// Animacion de ahogado solo en las lineas con troncos. Si se muere en otro lugar (o por tiempo) la animacion es explosion
							if (deathTimer >= FPS * 3 / 4)
							{
								if (deathY > HEIGHT/2 && timeLeft && deathY != HEIGHT-1)
								{
									al_draw_scaled_bitmap(drown1_bitmap,0,0,16,16,
											deathX, (HEIGHT - deathY) * GSIZEY, GSIZEX,GSIZEY,0);
								}
								else
								{
									al_draw_scaled_bitmap(crash1_bitmap,0,0,16,16,
											deathX, (HEIGHT - deathY) * GSIZEY, GSIZEX,GSIZEY,0);
								}
								if (fpsCounter % 12 == 0)
								{
									deathTimer--;
								}
								
							}
							else if (deathTimer >= FPS / 2 && deathTimer < FPS*2/3)
							{
								if (deathY > HEIGHT/2 && timeLeft && deathY != HEIGHT-1)
								{
									al_draw_scaled_bitmap(drown2_bitmap,0,0,16,16,
											deathX, (HEIGHT - deathY) * GSIZEY, GSIZEX,GSIZEY,0);
								}
								else
								{
									al_draw_scaled_bitmap(crash2_bitmap,0,0,16,16,
											deathX, (HEIGHT - deathY) * GSIZEY, GSIZEX,GSIZEY,0);
								}
								if (fpsCounter % 12 == 0)
								{
									deathTimer--;
								}
								
							}
							else if (deathTimer > FPS/4)
							{
								if (deathY > HEIGHT/2 && timeLeft && deathY != HEIGHT-1)
								{
									al_draw_scaled_bitmap(drown3_bitmap,0,0,16,16,
											deathX, (HEIGHT - deathY) * GSIZEY, GSIZEX,GSIZEY,0);
								}
								else
								{
									al_draw_scaled_bitmap(crash3_bitmap,0,0,16,16,
											deathX, (HEIGHT - deathY) * GSIZEY, GSIZEX,GSIZEY,0);
								}
								if (fpsCounter % 12 == 0)
								{
									deathTimer--;
								}
								
							}
							else if (deathTimer > 0)
							{
								al_draw_scaled_bitmap(death_bitmap,0,0,16,16,
											deathX, (HEIGHT - deathY) * GSIZEY, GSIZEX,GSIZEY,0);
							
								if (fpsCounter % 24 == 0)
								{
									deathTimer--;
								}
								
							}

							// SI LA RANA ESTA VIVA, SI LA DIBUJO
							else if (isMovingUp)
							{
								if (isMovingUp == FPS)
								{
									MoveRana(pRana, UP, map+rana.posy);
								}
								al_draw_scaled_bitmap(frogLeapFwd_bitmap,0,0,16,16,
										ranax, (HEIGHT - ranay - (isMovingUp)/FPS) * GSIZEY, GSIZEX,GSIZEY,0);
								isMovingUp--;
							}
							else if (isMovingDown)
							{
								if (isMovingDown == FPS)
								{
									MoveRana(pRana, DOWN, map+rana.posy);
								}
								if(ranay > 0)
								{
									al_draw_scaled_bitmap(frogLeapBack_bitmap,0,0,16,16,
											ranax, (HEIGHT - ranay + (isMovingDown)/FPS) * GSIZEY, GSIZEX,GSIZEY,0);
								}
								else
								{
									al_draw_scaled_bitmap(frog_bitmap,0,0,16,16,
											ranax, (HEIGHT - ranay) * GSIZEY, GSIZEX,GSIZEY,0);
								}
								isMovingDown--;
							}
							else if (isMovingLeft)
							{
								MoveRana(pRana, LEFT, map+rana.posy);
								al_draw_scaled_bitmap(frogLeapLeft_bitmap,0,0,16,16,
									ranax, (HEIGHT - ranay) * GSIZEY, GSIZEX,GSIZEY,0);
								isMovingLeft--;
							}
							else if (isMovingRight)
							{
								MoveRana(pRana, RIGHT, map+rana.posy);
								al_draw_scaled_bitmap(frogLeapRight_bitmap,0,0,16,16,
									ranax, (HEIGHT - ranay) * GSIZEY, GSIZEX,GSIZEY,0);
								isMovingRight--;
							}
							else{
								al_draw_scaled_bitmap(frog_bitmap,0,0,16,16,
									ranax, (HEIGHT - ranay) * GSIZEY, GSIZEX,GSIZEY,0);
							}

							
							/**********************************************************************************************************************
							 * MOVIMIENTO DE LOS OBJETOS SEGUN SU VELOCIDAD. VELOCIDAD V = V PIXELES POR FOTOGRAMA (ESCENCIALMENTE UNA FRECUENCIA)*
							 * ********************************************************************************************************************/
							if(linea->cant_obj > 0)
							{
								for(int f = 1; f <= linea->v; f++)
								{
									moveLine(linea, i, pRana);
								}
								
							}

							// Por ultimo, calculo colisiones
							if (deathTimer != 0 || RanaCollisions(pRana, &map[pRana->posy]) == 1) //Aprovecho el lazy evaluation para deshabilitar colisiones durante una muerte
							{
								if(deathTimer == 0) // Kill rana
								{
									deathTimer = FPS;
								} 
								if (deathTimer == 1) // Respawn rana
								{
									RestarVidas(pRana,0,"score.txt");
									frog_bitmap = frogIdleFwd_bitmap;
									timeLeft = START_TIME;
								}
							
							}
						}

						// Game tick updates & display updates
						fpsCounter++;
						al_flip_display();

						break;
						
					/*
					case GAMEOVER:
					{
						char finalScoreStr[6];
						al_clear_to_color(al_color_name("black"));
						al_draw_text(font, al_color_name("white"), DISPLAY_X/2.0, DISPLAY_Y/4, ALLEGRO_ALIGN_CENTER, "FINAL SCORE:");
						sprintf(finalScoreStr, '%d', inscreenscore );
						al_draw_text(font, al_color_name("white"), DISPLAY_X/2.0, DISPLAY_Y*3/4, ALLEGRO_ALIGN_CENTER, finalScoreStr);
						al_flip_display();
						break;
					}*/
					/*case GAMEOVERTOP:
					{
						char c1[1] = 'A',c2[1] = 'B',c3[1] = 'C';
						al_clear_to_color(al_color_name("black"));
						al_draw_text(font, al_color_name("white"), DISPLAY_X/2.0, DISPLAY_Y/6, ALLEGRO_ALIGN_CENTER, "Introduce your nickname:");
						al_draw_text(font, al_color_name("white"), DISPLAY_X/2.0, DISPLAY_Y/2.0, ALLEGRO_ALIGN_CENTER, c1);
						al_draw_text(font, al_color_name("white"), DISPLAY_X/2.0, DISPLAY_Y/2.0, ALLEGRO_ALIGN_CENTER, c2);
						al_draw_text(font, al_color_name("white"), DISPLAY_X/2.0, DISPLAY_Y*4/6, ALLEGRO_ALIGN_CENTER, c3);
						
					}
					*/
						
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
						if (ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
						{
							screen = PAUSE;
						}
						else if (!isMovingUp && !isMovingDown && !isMovingLeft && !isMovingRight && !deathTimer)
						{
							switch(ev.keyboard.keycode){
								case ALLEGRO_KEY_DOWN:
									isMovingDown = FPS;
									frog_bitmap = frogIdleBack_bitmap;
									break;
								case ALLEGRO_KEY_UP:
									isMovingUp = FPS;
									frog_bitmap = frogIdleFwd_bitmap;
									//Cada vez que va para arriba se fija si se debe inc score
									//inscreenscore = ct_score(rana.posy,TIME,time_left,0,rana.vidas,0);
									//printf ("%u\n",inscreenscore);

									break;
								case ALLEGRO_KEY_LEFT:
									isMovingLeft = FPS;
									frog_bitmap = frogIdleLeft_bitmap;
									break;
								case ALLEGRO_KEY_RIGHT:
									isMovingRight = FPS;
									frog_bitmap = frogIdleRight_bitmap;
									break;
							}

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
