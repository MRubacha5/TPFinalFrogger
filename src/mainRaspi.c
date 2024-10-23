/*
testlibraries es un ejemplo de uso de las librerías disdrv y joydrv
Permite mover con el joystick un LED encendido en la matriz de LEDs
*/
//Como compilar: gcc testLibraries.c disdrv.o joydrv.o -Wall -o testLibs
#include <stdio.h>
#include <time.h>

#include "disdrv.h"
#include "joydrv.h"
#include "worldData.h"
#include "score.h"
#include "rana.h"
#include "movement.h"
#include "platformConfig.h"

#define FPS 60
#define THRESHOLD 40	//Límite a partir del cual se mueve el LED encendido
#define MENU 0
#define GAME 1
#define PAUSE 2

int mainMenu[16][16] = {{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                        {0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                        {0,1,0,0,0,1,0,1,0,1,1,0,1,0,1,0},
                        {0,1,1,1,0,1,0,1,1,1,1,1,1,0,1,0},
                        {0,0,0,1,0,1,0,1,0,1,1,1,0,0,1,0},
                        {0,1,1,1,0,1,0,1,0,1,1,0,1,0,1,0},
                        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                        {0,1,1,1,0,1,0,1,0,1,1,1,0,1,1,1},
                        {0,1,0,1,0,1,0,1,0,0,1,0,0,0,1,0},
                        {0,1,1,1,0,1,0,1,0,0,1,0,0,0,1,0},
                        {0,0,0,1,0,1,0,1,0,0,1,0,0,0,1,0},
                        {0,0,0,1,0,1,1,1,0,1,1,1,0,0,1,0},
                        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}};

int pauseMenu[16][16]= {{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                        {0,1,1,1,0,1,0,0,0,1,1,1,0,1,0,1},
                        {0,1,0,1,0,1,0,0,0,1,0,1,0,1,0,1},
                        {0,1,1,1,0,1,0,0,0,1,1,1,0,0,1,0},
                        {0,1,0,0,0,1,0,0,0,1,0,1,0,0,1,0},
                        {0,1,0,0,0,1,1,1,0,1,0,1,0,0,1,0},
                        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                        {0,1,0,1,0,1,1,1,0,1,1,1,0,1,0,1},
                        {0,1,1,1,0,1,0,0,0,1,0,1,0,1,0,1},
                        {0,1,0,1,0,1,1,0,0,1,0,1,0,1,0,1},
                        {0,1,0,1,0,1,0,0,0,1,0,1,0,1,0,1},
                        {0,1,0,1,0,1,1,1,0,1,0,1,0,1,1,1},
                        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}};

int main(void)
{
    clock_t before = clock(); //agarro tiempo antes de arrancar
    clock_t difference = 0;
    clock_t ini = clock();
    clock_t lap_time;
    int msec = 0;
    linea_t * pl;
    rana_t rana;
    rana_t * pRana = &rana;
    linea_t map[HEIGHT];
	
	joy_init();										//inicializa el joystick
	disp_init();									//inicializa el display
	disp_clear();									//limpia todo el display
	dcoord_t pos = {DISP_MAX_X>>1 , DISP_MAX_Y>>1};	//pos es la posición actual, empieza en el centro de la matriz
	joyinfo_t coord = {0,0,J_NOPRESS};							//coordenadas medidas del joystick

    int fpsCounter = 0;
    int screen = MENU;

    int joyMoved = 0;
    int joyValue = -1;
    int joyPressed = 0;

    int optionSelected = 0;

    int do_exit = 0;

    do
	{
        lap_time = clock();
        difference = lap_time - before;
        msec = difference * 1000 / CLOCKS_PER_SEC;
        int i, c;



        if(msec > (1/FPS)*1000){ //falta el /FPS
            disp_update();	//Actualiza el display con el contenido del buffer
            coord = joy_read();	//Guarda las coordenadas medidas
            disp_clear();

            if(coord.y > THRESHOLD && !joyMoved){
                joyValue = UP;
                joyMoved = 1;
            }
            else if(coord.y < -THRESHOLD && !joyMoved) {
                joyValue = DOWN;
                joyMoved = 1;
            }
            else if(coord.x > THRESHOLD && !joyMoved){
                joyValue = RIGHT;
                joyMoved = 1;
            }
            else if (coord.x < -THRESHOLD && !joyMoved){
                joyValue = LEFT;
                joyMoved = 1;
            }

            if(coord.x < THRESHOLD && coord.x > -THRESHOLD && coord.y < THRESHOLD && coord.y > -THRESHOLD){
                joyMoved = 0;
            }

            if(coord.sw == J_NOPRESS){
                joyPressed = 0;
            }
            

            switch (screen)
            {
            case MENU:
                for(i = 0 ; i < 16 ; i++){
                    for (c = 0 ; c < 16 ; c++){
                        pos.x = c;
                        pos.y = i;
                        disp_write(pos, mainMenu[i][c]);
                    }
                }
                
                for(i=(optionSelected?8:0) ; i < (optionSelected?16:8) ; i++){
                    for(c = 0 ; c < 16 ; c++){
                        pos.x = c;
                        pos.y = i;
                        disp_write(pos, !mainMenu[i][c]);
                    }
                }

                if(joyMoved){
                    if(joyValue == UP){
                        optionSelected = 0;
                    }
                    if(joyValue == DOWN){
                        optionSelected = 1;
                    }
                }

                if(coord.sw == J_PRESS && joyPressed == 0){
                    joyPressed = 1;
                    if(optionSelected == 0){
                        createMap(map,0);
					    spawnRana(map, pRana);
                        screen = GAME;
                    }
                    else if (optionSelected == 1){
                        do_exit = 1;
                    }
                }
                
                break;
            case PAUSE:
                for(i = 0 ; i < 16 ; i++){
                    for (c = 0 ; c < 16 ; c++){
                        pos.x = c;
                        pos.y = i;
                        disp_write(pos, pauseMenu[i][c]);
                    }
                }
                
                for(i=(optionSelected?8:0) ; i < (optionSelected?16:8) ; i++){
                    for(c = 0 ; c < 16 ; c++){
                        pos.x = c;
                        pos.y = i;
                        disp_write(pos, !pauseMenu[i][c]);
                    }
                }

                if(joyMoved){
                    if(joyValue == UP){
                        optionSelected = 0;
                    }
                    if(joyValue == DOWN){
                        optionSelected = 1;
                    }
                }

                if(coord.sw == J_PRESS && joyPressed == 0){
                    joyPressed = 1;
                    if(optionSelected == 0){
                        screen = GAME;
                    }
                    else if (optionSelected == 1){
                        screen = MENU;
                    }
                }
                break;
            case GAME:
                fpsCounter++;
                if(fpsCounter >= FPS){
                    fpsCounter = 0;
                }
                for(i = 0 ; i < 16 ; i++){
                    linea_t * linea = pl+i;

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


                    
                    int objectSize = 0;
                    for(c = 0 ; c < linea->cant_obj ; c++){ 
                        pos.y = i;
                        for(objectSize = 0 ; objectSize < linea->size ; objectSize++){
                            pos.x = linea->po[c] + objectSize;
                            int lineValue = (i>HEIGHT/2)?(1):(0);
                            disp_write(pos, lineValue);
                        }  
                    }
                }

                pos.x = pRana->posx;
                pos.y = pRana->posy;
                if(fpsCounter % 2){
                    disp_write(pos, 1);
                }
                else{
                    disp_write(pos, 0);
                }
                
                
                if(coord.sw == J_PRESS && joyPressed == 0){
                    joyPressed = 1;
                    screen = PAUSE;
                }
                break;
            }      
            before = clock();
        }
		

		
	} while(!do_exit);	//termina si se presiona el switch
	
	//Borro el display al salir
	disp_clear();
    disp_update();
}
