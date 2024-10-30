/*******************************************************************************
 * HEADERS
 ******************************************************************************/

#include <stdlib.h>
#include <stdio.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include<allegro5/allegro_ttf.h>
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

// Pantallas; se cambia entre ellas con un switch case statement
enum {MENU, GAME, PAUSE, HISCORE, GAMEOVER};

/*******************************************************************************
 * MACROS
 ******************************************************************************/
#define DRAW_TIMELEFT(color) al_draw_filled_rectangle(GSIZEX*3.5,(HEIGHT + 2)*GSIZEY,3.5*GSIZEX + ((timeLeft) * GSIZEX/6.333) , (HEIGHT+2.5)*GSIZEY, al_color_name(color))
#define DRAW_GRASSWINFRAME(x) (al_draw_scaled_bitmap(grassWinFrame_bitmap,0,0,32,24,(x)-GSIZEX, (HEIGHT-i-1) * GSIZEY, GSIZEX *2,GSIZEY*2,0))

/*******************************************************************************
 * VARIABLES GLOBALES E INICIALIZACIONES
 ******************************************************************************/

int do_exit = 0;
int keyPressed = 0;
int keyPressedValue = 0;
unsigned int timeLeft;

uint16_t inscreenscore;
char strscore [6] = {"00000"};
int entregada;

linea_t map[HEIGHT];
rana_t rana;
rana_t * pRana = &rana;

extern int winPosStates[5];
extern int vidas;
extern int currentScore;
extern char topNames[10][4];
extern uint16_t topScores[10];

/*******************************************************************************
 * PROTOTIPOS DE FUNCIONES
 ******************************************************************************/

static void drawTopScores (ALLEGRO_FONT * font, const char* name, const char* score, double nameX, double scoreX, double y);

static void drawTopScores (ALLEGRO_FONT * font, const char* name, const char* score, double nameX, double scoreX, double y)
{
	al_draw_text(font, al_color_name("white"), nameX, y, ALLEGRO_ALIGN_CENTER, name);
	al_draw_text(font, al_color_name("white"), scoreX, y, ALLEGRO_ALIGN_CENTER, score);
}

int main (void) {

		/**********************
		 * INICIALIZO ALLEGRO *
		 **********************/
		al_init_font_addon();
		al_init_ttf_addon();
		
		ALLEGRO_FONT * font, * fontL;
		ALLEGRO_DISPLAY * display = NULL;
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

	    font = al_load_font("../assets/Sprites/arcadeFont.ttf",GSIZEX*0.5,0);
		fontL = al_load_font("../assets/Sprites/arcadeFont.ttf",GSIZEX,0);
	    if (!font && !fontL) {
	    	printf("failed to load fonts!\n");
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
			printf("failed to initialize image\n");
			return -1;
		}

		/*************** | BITMAPS | ******************************************/
		//Cars
		ALLEGRO_BITMAP * car1_bitmap = al_load_bitmap("../assets/Sprites/car1.png");
		ALLEGRO_BITMAP * car2_bitmap = al_load_bitmap("../assets/Sprites/car2.png");
		ALLEGRO_BITMAP * car3_bitmap = al_load_bitmap("../assets/Sprites/car3.png");
		ALLEGRO_BITMAP * car4_bitmap = al_load_bitmap("../assets/Sprites/car4.png");
		ALLEGRO_BITMAP * truck_bitmap = al_load_bitmap("../assets/Sprites/truck.png");

		//Death animations
		ALLEGRO_BITMAP * crash1_bitmap = al_load_bitmap("../assets/Sprites/crash1.png");
		ALLEGRO_BITMAP * crash2_bitmap = al_load_bitmap("../assets/Sprites/crash2.png");
		ALLEGRO_BITMAP * crash3_bitmap = al_load_bitmap("../assets/Sprites/crash3.png");
		ALLEGRO_BITMAP * death_bitmap = al_load_bitmap("../assets/Sprites/death.png");
		ALLEGRO_BITMAP * drown1_bitmap = al_load_bitmap("../assets/Sprites/drown1.png");
		ALLEGRO_BITMAP * drown2_bitmap = al_load_bitmap("../assets/Sprites/drown2.png");
		ALLEGRO_BITMAP * drown3_bitmap = al_load_bitmap("../assets/Sprites/drown3.png");

		//Frog animations
		ALLEGRO_BITMAP * frogIdleBack_bitmap = al_load_bitmap("../assets/Sprites/frogIdleBack.png");
		ALLEGRO_BITMAP * frogIdleFwd_bitmap = al_load_bitmap("../assets/Sprites/frogIdleFwd.png");
		ALLEGRO_BITMAP * frogIdleLeft_bitmap = al_load_bitmap("../assets/Sprites/frogIdleLeft.png");
		ALLEGRO_BITMAP * frogIdleRight_bitmap = al_load_bitmap("../assets/Sprites/frogIdleRight.png");
		ALLEGRO_BITMAP * frogLeapBack_bitmap = al_load_bitmap("../assets/Sprites/frogLeapBack.png");
		ALLEGRO_BITMAP * frogLeapFwd_bitmap = al_load_bitmap("../assets/Sprites/frogLeapFwd.png");
		ALLEGRO_BITMAP * frogLeapLeft_bitmap = al_load_bitmap("../assets/Sprites/frogLeapLeft.png");
		ALLEGRO_BITMAP * frogLeapRight_bitmap = al_load_bitmap("../assets/Sprites/frogLeapRight.png");
		ALLEGRO_BITMAP * frogWin_bitmap = al_load_bitmap("../assets/Sprites/frogWin.png");

		//Grass
		ALLEGRO_BITMAP * grassWinFrame_bitmap = al_load_bitmap("../assets/Sprites/grassWinFrame.png");
		ALLEGRO_BITMAP * grassWinSeparator_bitmap = al_load_bitmap("../assets/Sprites/grassWinSeparator.png");
		ALLEGRO_BITMAP * purpleGrass_bitmap = al_load_bitmap("../assets/Sprites/purpleGrass.png");

		//Logs
		ALLEGRO_BITMAP * logLeft_bitmap = al_load_bitmap("../assets/Sprites/logLeft.png");
		ALLEGRO_BITMAP * logMiddle_bitmap = al_load_bitmap("../assets/Sprites/logMiddle.png");
		ALLEGRO_BITMAP * logRight_bitmap = al_load_bitmap("../assets/Sprites/logRight.png");

		//Title Text
		ALLEGRO_BITMAP * titleE_bitmap = al_load_bitmap("../assets/Sprites/titleE.png");
		ALLEGRO_BITMAP * titleF_bitmap = al_load_bitmap("../assets/Sprites/titleF.png");
		ALLEGRO_BITMAP * titleG_bitmap = al_load_bitmap("../assets/Sprites/titleG.png");
		ALLEGRO_BITMAP * titleO_bitmap = al_load_bitmap("../assets/Sprites/titleO.png");
		ALLEGRO_BITMAP * titleR_bitmap = al_load_bitmap("../assets/Sprites/titleR.png");

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
						al_draw_text(fontL, al_color_name("white"), DISPLAY_X/2, DISPLAY_Y*4.0/8, ALLEGRO_ALIGN_CENTER, "START");
						al_draw_text(fontL, al_color_name("white"), DISPLAY_X/2, DISPLAY_Y*5.0/8, ALLEGRO_ALIGN_CENTER, "HIGH SCORES");
						al_draw_text(fontL, al_color_name("white"), DISPLAY_X/2, DISPLAY_Y*6.0/8, ALLEGRO_ALIGN_CENTER, "QUIT");

						// Los Botones cambian de color cuando el mouse esta por encima
						if(mouse_x > DISPLAY_X/8 && mouse_x < DISPLAY_X*7/8){
							if(mouse_y > DISPLAY_Y*7.0/16 && mouse_y < DISPLAY_Y*8.5/16+GSIZEY){
								al_draw_text(fontL, al_color_name("yellow"), DISPLAY_X/2, DISPLAY_Y*4.0/8, ALLEGRO_ALIGN_CENTER, "START");
								if(leftClick){
									leftClick = 0;
									screen = GAME;
									vidas = 3;
									createMap(map,0);
									spawnRana(map, pRana);
								}
							}
							else if(mouse_y > DISPLAY_Y*8.5/16+GSIZEY && mouse_y < DISPLAY_Y*9.5/16+2*GSIZEY)
							{
								al_draw_text(fontL, al_color_name("yellow"), DISPLAY_X/2, DISPLAY_Y*5.0/8, ALLEGRO_ALIGN_CENTER, "HIGH SCORES");
								if(leftClick){
									leftClick = 0;
									screen = HISCORE;
								}
							}
							else if(mouse_y > DISPLAY_Y*9.5/16+2*GSIZEY && mouse_y < DISPLAY_Y*10.5/16+3*GSIZEY){
								al_draw_text(fontL, al_color_name("yellow"), DISPLAY_X/2, DISPLAY_Y*6.0/8, ALLEGRO_ALIGN_CENTER, "QUIT");
								if(leftClick){
									leftClick = 0;
									do_exit = 1;
								}
							}
						}

						al_flip_display();
						break;

					case HISCORE:
						// Fondo
						al_clear_to_color(al_color_name("black"));
						
						//Botones
						//al_draw_filled_rectangle(DISPLAY_X/8, DISPLAY_Y*6/8, DISPLAY_X*7/8, DISPLAY_Y, al_color_name("black"));
						al_draw_text(font, al_color_name("white"), DISPLAY_X/2, DISPLAY_Y*7/8, ALLEGRO_ALIGN_CENTER, "MAIN MENU");

						if((mouse_x > DISPLAY_X/8 && mouse_x < DISPLAY_X*7/8) && (mouse_y > DISPLAY_Y*6/8 && mouse_y < DISPLAY_Y)){
							al_draw_text(font, al_color_name("yellow"), DISPLAY_X/2, DISPLAY_Y*7/8, ALLEGRO_ALIGN_CENTER, "MAIN MENU");
							if(leftClick){
								leftClick = 0;
								screen = MENU;
							
							}
						}

						al_draw_text(fontL, al_color_name("white"), DISPLAY_X/2, DISPLAY_Y*0.5/8, ALLEGRO_ALIGN_CENTER, "HIGH SCORES");

						// Fetch top scores
						getTopScores("score.txt");
						
						// Imprimo los 10 scores
						for (int s = 0; s < 10; s++)
						{
							// Convierto el score a string
							char buffer[6]; 
							intToChar(6, buffer ,topScores[s]);
							
							drawTopScores(font, topNames[s], buffer, DISPLAY_X*9/24, DISPLAY_X*7/12, DISPLAY_Y*(s+2.5)/15);
						}
						
						al_flip_display();
						break;

					case PAUSE:
						//Fondo
						al_draw_filled_rectangle(DISPLAY_X/8, DISPLAY_Y*7/16, DISPLAY_X*7/8, DISPLAY_Y*9/16, al_color_name("black"));

						//PAUSE Text
						al_draw_text(fontL, al_color_name("red"), DISPLAY_X/2, (DISPLAY_Y-GSIZEY)/2, ALLEGRO_ALIGN_CENTER, "PAUSE");

						//Botones
						al_draw_filled_rectangle(DISPLAY_X/8, DISPLAY_Y/8, DISPLAY_X*7/8, DISPLAY_Y*3/8, al_color_name("black"));
						al_draw_filled_rectangle(DISPLAY_X/8, DISPLAY_Y*5/8, DISPLAY_X*7/8, DISPLAY_Y*7/8, al_color_name("black"));
						al_draw_text(font, al_color_name("white"), DISPLAY_X/2, DISPLAY_Y/4, ALLEGRO_ALIGN_CENTER, "CONTINUE");
						al_draw_text(font, al_color_name("white"), DISPLAY_X/2, DISPLAY_Y*3/4, ALLEGRO_ALIGN_CENTER, "MAIN MENU");

						if(mouse_x > DISPLAY_X/8 && mouse_x < DISPLAY_X*7/8){
							if(mouse_y > DISPLAY_Y/8 && mouse_y < DISPLAY_Y*3/8){
								al_draw_text(font, al_color_name("yellow"), DISPLAY_X/2, DISPLAY_Y/4, ALLEGRO_ALIGN_CENTER, "CONTINUE");
								if(leftClick){
									leftClick = 0;
									screen = GAME;
								}
							}
							else if(mouse_y > DISPLAY_Y*5/8 && mouse_y < DISPLAY_Y*7/8){
								al_draw_text(font, al_color_name("yellow"), DISPLAY_X/2, DISPLAY_Y*3/4, ALLEGRO_ALIGN_CENTER, "MAIN MENU");
								if(leftClick){
									leftClick = 0;
									screen = MENU;
								}
							}
						}
						
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
						al_draw_text(font,al_color_name("yellow"),GSIZEX,GSIZEY*(HEIGHT+2),0,"TIME");

						if (timeLeft > 30)
						{
							DRAW_TIMELEFT("green");
						}
						else if (timeLeft > 10)
						{
							DRAW_TIMELEFT("yellow");
						}
						else if (timeLeft > 0)
						{
							DRAW_TIMELEFT("red");
						}
						else if (deathTimer == 0) //La rana muere si se queda sin tiempo
						{
							deathTimer = FPS;
						}

						//dibujo el score
						al_draw_text(font,al_color_name("white"),GSIZEX, (HEIGHT+2.75)*GSIZEY,0,"SCORE");
						al_draw_textf(font, al_color_name("white"), GSIZEX*4,(HEIGHT+2.75)*GSIZEY, 0, strscore);

						//high score
						al_draw_text(font,al_color_name("white"),GSIZEX*9, (HEIGHT+2.75)*GSIZEY,0,"HI");
						al_draw_text(font,al_color_name("white"),GSIZEX*10.5, (HEIGHT+2.75)*GSIZEY,0,"99999");

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
								#ifdef DEBUG
										#define HITBOX_WINPOS(x) (al_draw_filled_rectangle((x)-HITBOXWIDTH/3.0, GSIZEY *0.75, (x)+HITBOXWIDTH/3.0, GSIZEY *1.75,al_color_name("red")))
										//al_draw_filled_rectangle(WINPOS1-0.25*HITBOXWIDTH, GSIZEY *0.75, 
										//	WINPOS1+0.25*HITBOXWIDTH, GSIZEY *1.75,al_color_name("red"));
										HITBOX_WINPOS(WINPOS1);
										HITBOX_WINPOS(WINPOS2);
										HITBOX_WINPOS(WINPOS3);
										HITBOX_WINPOS(WINPOS4);
										HITBOX_WINPOS(WINPOS5);
								#endif //DEBUG (Hitbox display)

								DRAW_GRASSWINFRAME(WINPOS1);
								DRAW_GRASSWINFRAME(WINPOS2);
								DRAW_GRASSWINFRAME(WINPOS3);
								DRAW_GRASSWINFRAME(WINPOS4);
								DRAW_GRASSWINFRAME(WINPOS5);
			
								//Separadores
								al_draw_scaled_bitmap(grassWinSeparator_bitmap,0,0,16,24,
									GSIZEX*2,(HEIGHT-i-1) * GSIZEY, GSIZEX, GSIZEY*2,0);
								al_draw_scaled_bitmap(grassWinSeparator_bitmap,0,0,16,24,
									GSIZEX*2 + GSIZEX/2.0,(HEIGHT-i-1) * GSIZEY, GSIZEX, GSIZEY*2,0);
								al_draw_scaled_bitmap(grassWinSeparator_bitmap,0,0,16,24,
									WINPOS2+GSIZEX,(HEIGHT-i-1) * GSIZEY, GSIZEX, GSIZEY*2,0);
								al_draw_scaled_bitmap(grassWinSeparator_bitmap,0,0,16,24,
									WINPOS2 +GSIZEX + GSIZEX/2.0,(HEIGHT-i-1) * GSIZEY, GSIZEX, GSIZEY*2,0);
								al_draw_scaled_bitmap(grassWinSeparator_bitmap,0,0,16,24,
									WINPOS3+GSIZEX,(HEIGHT-i-1) * GSIZEY, GSIZEX, GSIZEY*2,0);
								al_draw_scaled_bitmap(grassWinSeparator_bitmap,0,0,16,24,
									WINPOS3 +GSIZEX+ GSIZEX/2.0,(HEIGHT-i-1) * GSIZEY, GSIZEX, GSIZEY*2,0);
								al_draw_scaled_bitmap(grassWinSeparator_bitmap,0,0,16,24,
									WINPOS4+GSIZEX,(HEIGHT-i-1) * GSIZEY, GSIZEX, GSIZEY*2,0);
								al_draw_scaled_bitmap(grassWinSeparator_bitmap,0,0,16,24,
									WINPOS4 + GSIZEX + GSIZEX/2.0,(HEIGHT-i-1) * GSIZEY, GSIZEX, GSIZEY*2,0);

								/// Dibujo ranas que ya llegaron
								#define DRAW_FROGWIN(x) (al_draw_scaled_bitmap(frogWin_bitmap,0,0,16,16,(x)-0.5*GSIZEX, GSIZEY *0.75, GSIZEX,GSIZEY,0))
								if(winPosStates[0] == WIN_OCC){
									DRAW_FROGWIN(WINPOS1);
								}
								if(winPosStates[1] == WIN_OCC){
									DRAW_FROGWIN(WINPOS2);
								}
								if(winPosStates[2] == WIN_OCC){
									DRAW_FROGWIN(WINPOS3);
								}
								if(winPosStates[3] == WIN_OCC){
									DRAW_FROGWIN(WINPOS4);
								}
								if(winPosStates[4] == WIN_OCC){
									DRAW_FROGWIN(WINPOS5);
								}
								
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
								if (deathTimer == 1 && i == HEIGHT-1) // Respawn rana (i == HEIGHT-1 para asegurarse que lo haga solamente una vez por pasada)
								{
									RestarVidas(pRana,0,"score.txt");
									frog_bitmap = frogIdleFwd_bitmap;
									timeLeft = START_TIME;
								}
							
							}
						}

						long int ranax = pRana->posx;
						long int ranay = pRana->posy;
						long int deathX;
						long int deathY;
						unsigned int m = 8; //Velocidad de movimiento de la rana

						/**********************************************************************************************************************
						 * DIBUJO LA RANA Y LA MUEVO CON UNA CADENA DE IFS PARA PERMITIR FLUIDEZ EN LOS MOVIMIENTOS SIN COMPROMETER LA LOGICA *
						 * ********************************************************************************************************************/
						// SI LA RANA ESTA MURIENDO, NO LA DIBUJO

						#ifdef DEBUG
						al_draw_filled_rectangle(ranax-HITBOXWIDTH/2.0,(HEIGHT-ranay)*GSIZEY, 
								ranax+HITBOXWIDTH/2,(HEIGHT-ranay)*GSIZEY+GSIZEY,al_color_name("red"));
						#endif //DEBUG (Hitbox display)

						if (deathTimer == FPS) 
						{
							//Inhibo el movimiento de la rana y guardo su posicion de muerte
							isMovingDown = 0;
							isMovingUp = 0;
							isMovingLeft = 0;
							isMovingRight = 0;
							deathX = pRana->posx;
							deathY = pRana->posy;

							deathTimer--;
							
						}
						// Animacion de ahogado solo en las lineas con troncos. Si se muere en otro lugar (o por tiempo) la animacion es explosion
						if (deathTimer >= FPS * 0.75)
						{
							if (deathY > HEIGHT/2 && timeLeft && deathY != HEIGHT-1)
							{
								al_draw_scaled_bitmap(drown1_bitmap,0,0,16,16,
										deathX - GSIZEX/2.0, (HEIGHT - deathY) * GSIZEY, GSIZEX,GSIZEY,0);
							}
							else
							{
								al_draw_scaled_bitmap(crash1_bitmap,0,0,16,16,
										deathX - GSIZEX/2.0, (HEIGHT - deathY) * GSIZEY, GSIZEX,GSIZEY,0);
							}
								deathTimer--;
						}
						else if (deathTimer >= FPS / 2)
						{
							if (deathY > HEIGHT/2 && timeLeft && deathY != HEIGHT-1)
							{
								al_draw_scaled_bitmap(drown2_bitmap,0,0,16,16,
										deathX - GSIZEX/2.0, (HEIGHT - deathY) * GSIZEY, GSIZEX,GSIZEY,0);
							}
							else
							{
								al_draw_scaled_bitmap(crash2_bitmap,0,0,16,16,
										deathX - GSIZEX/2.0, (HEIGHT - deathY) * GSIZEY, GSIZEX,GSIZEY,0);
							}
							deathTimer--;
						}
						else if (deathTimer > FPS/4)
						{
							if (deathY > HEIGHT/2 && timeLeft && deathY != HEIGHT-1)
							{
								al_draw_scaled_bitmap(drown3_bitmap,0,0,16,16,
										deathX - GSIZEX/2.0, (HEIGHT - deathY) * GSIZEY, GSIZEX,GSIZEY,0);
							}
							else
							{
								al_draw_scaled_bitmap(crash3_bitmap,0,0,16,16,
										deathX - GSIZEX/2.0, (HEIGHT - deathY) * GSIZEY, GSIZEX,GSIZEY,0);
							}
							deathTimer--;
							
						}
						else if (deathTimer > 0)
						{
							al_draw_scaled_bitmap(death_bitmap,0,0,16,16,
										deathX - GSIZEX/2.0, (HEIGHT - deathY) * GSIZEY, GSIZEX,GSIZEY,0);
						
							deathTimer--;
						}

						// SI LA RANA ESTA VIVA, SI LA DIBUJO
						// ARRIBA
						else if (isMovingUp == GSIZEY)
						{
							isMovingUp = isMovingUp/m;
							al_draw_scaled_bitmap(frogLeapFwd_bitmap,0,0,16,16,
									ranax - GSIZEX/2.0, (HEIGHT - pRana->posy - 1 + (isMovingUp*m/(double)GSIZEY)) * GSIZEY, GSIZEX,GSIZEY,0);
							isMovingUp--;
						}
						else if (isMovingUp > m/2)
						{
							al_draw_scaled_bitmap(frogLeapFwd_bitmap,0,0,16,16,
									ranax - GSIZEX/2.0, (HEIGHT - pRana->posy - 1 + (isMovingUp*m/(double)GSIZEY)) * GSIZEY, GSIZEX,GSIZEY,0);
							isMovingUp--;
						}
						else if (isMovingUp == m/2 || (GSIZEY/m < m/2 && isMovingUp == GSIZEY/m - 1))//Backend move occurs halfway through animation; second condition accounts for small screen sizes
						{
							al_draw_scaled_bitmap(frogLeapFwd_bitmap,0,0,16,16,
									ranax - GSIZEX/2.0, (HEIGHT - pRana->posy - 1 + (isMovingUp*m/(double)GSIZEY)) * GSIZEY, GSIZEX,GSIZEY,0);
							MoveRana(pRana, UP, map+rana.posy);

							//printf ("%d\n", rana.posy);
							
							inscreenscore = ct_score(rana.posy, timeLeft, HEIGHT, vidas, entregada);
							intToChar (6, strscore, inscreenscore);

							isMovingUp--;

						}
						else if (isMovingUp > 0)
						{
							al_draw_scaled_bitmap(frogLeapFwd_bitmap,0,0,16,16,
									ranax - GSIZEX/2.0, (HEIGHT - pRana->posy + (isMovingUp*m/(double)GSIZEY)) * GSIZEY, GSIZEX,GSIZEY,0);
							isMovingUp--;
						}
						// ABAJO
						else if (isMovingDown == GSIZEY && ranay == 0) //No permite que la rana baje del origen
						{
							isMovingDown = 0;
							al_draw_scaled_bitmap(frog_bitmap,0,0,16,16,
								ranax - GSIZEX/2.0, (HEIGHT - ranay) * GSIZEY, GSIZEX,GSIZEY,0);
						}
						else if (isMovingDown == GSIZEY)
						{
							isMovingDown = isMovingDown/m;
							al_draw_scaled_bitmap(frogLeapBack_bitmap,0,0,16,16,
									ranax - GSIZEX/2.0, (HEIGHT - pRana->posy + 1 - (isMovingDown*m)/(double)GSIZEY) * GSIZEY, GSIZEX,GSIZEY,0);
							isMovingDown--;
						}
						else if (isMovingDown > m/2)
						{
							al_draw_scaled_bitmap(frogLeapBack_bitmap,0,0,16,16,
									ranax - GSIZEX/2.0, (HEIGHT - pRana->posy + 1 - (isMovingDown*m)/(double)GSIZEY) * GSIZEY, GSIZEX,GSIZEY,0);
							isMovingDown--;
						}
						else if (isMovingDown == m/2 || (GSIZEY/m < m/2 && isMovingDown == GSIZEY/m - 1))
						{
							
							al_draw_scaled_bitmap(frogLeapBack_bitmap,0,0,16,16,
									ranax - GSIZEX/2.0, (HEIGHT - pRana->posy + 1 - (isMovingDown*m)/(double)GSIZEY) * GSIZEY, GSIZEX,GSIZEY,0);
							MoveRana(pRana, DOWN, map+rana.posy);
							isMovingDown--;
						}
						else if (isMovingDown > 0)
						{
							al_draw_scaled_bitmap(frogLeapBack_bitmap,0,0,16,16,
									ranax - GSIZEX/2.0, (HEIGHT - pRana->posy - (isMovingDown*m)/(double)GSIZEY) * GSIZEY, GSIZEX,GSIZEY,0);
							isMovingDown--;
						}
						// IZQUIERDA	
						else if (isMovingLeft)
						{
							
							al_draw_scaled_bitmap(frogLeapLeft_bitmap,0,0,16,16,
								ranax - GSIZEX/2.0, (HEIGHT - ranay) * GSIZEY, GSIZEX,GSIZEY,0);
							for (int n = 1; isMovingLeft > 0 && n < m; n++)
							{
								isMovingLeft = (isMovingLeft-1 > 0)? isMovingLeft-1 : 0;
								MoveRana(pRana, LEFT, map+rana.posy);
							}
								
						}
						// DERECHA
						else if (isMovingRight)
						{
							
							al_draw_scaled_bitmap(frogLeapRight_bitmap,0,0,16,16,
								ranax - GSIZEX/2.0, (HEIGHT - ranay) * GSIZEY, GSIZEX,GSIZEY,0);
							for (int n = 1; isMovingRight > 0 && n < m; n++)
							{
								isMovingRight = (isMovingRight-1 > 0)? isMovingRight-1 : 0;
								MoveRana(pRana, RIGHT, map+rana.posy);
							}
						}
						else{
							switch(pRana->dir)
							{
								case UP:
									frog_bitmap = frogIdleFwd_bitmap;
									break;
								case DOWN:
									frog_bitmap = frogIdleBack_bitmap;
									break;
								case LEFT:
									frog_bitmap = frogIdleLeft_bitmap;
									break;
								case RIGHT:
									frog_bitmap = frogIdleRight_bitmap;
									break;
								default:
									break;
							}
							al_draw_scaled_bitmap(frog_bitmap,0,0,16,16,
								ranax - GSIZEX/2.0, (HEIGHT - ranay) * GSIZEY, GSIZEX,GSIZEY,0);
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
						//inscreenscore = ct_score(rana.posy, timeLeft, HEIGHT, vidas, entregada);
						if (ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE) //Escape key fuera del switch case para permitir pausar durante movimiento/muerte
						{
							screen = PAUSE;
						}
						else if (!isMovingUp && !isMovingDown && !isMovingLeft && !isMovingRight && !deathTimer)
						{
							switch(ev.keyboard.keycode){
								case ALLEGRO_KEY_DOWN:
									isMovingDown = GSIZEY;
									break;
								case ALLEGRO_KEY_UP:
									isMovingUp = GSIZEY;
									break;
								case ALLEGRO_KEY_LEFT:
									isMovingLeft = GSIZEX;
									break;
								case ALLEGRO_KEY_RIGHT:
									isMovingRight = GSIZEX;
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
