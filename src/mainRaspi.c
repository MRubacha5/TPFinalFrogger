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

unsigned int timeLeft = START_TIME; // valor en segundos 

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
    int isMoving = 0;

    int ranaColor = 0;
    int ranaColorTimer = 0;

    int optionSelected = 0;

    int do_exit = 0;

    dcoord_t timerCoord;

    extern int winPosStates[5];
    extern int vidas;
    extern int currentScore;

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
                        screen = GAME;
                        createMap(map,0);
					    spawnRana(map, pRana);
                        timerCoord.x = 0;
                        timerCoord.y = DISP_MAX_Y;
                        
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
                int timerSetup = 1;
                if(timerSetup){
                    for(c = 0 ; c <= DISP_MAX_X ; c++){
                        pos.x = c;
                        pos.y = 0;
                        disp_write(pos, 1);
                        pos.y = DISP_MAX_Y;
                        disp_write(pos, 1);
                    }
                    for(c = 1 ; c < DISP_MAX_Y ; c++){
                        pos.y = c;
                        pos.x = 0;
                        disp_write(pos, 1);
                        pos.x = DISP_MAX_X;
                        disp_write(pos, 1);
                    }
                    timeLeft = START_TIME;
                    timerSetup = 0;
                }

                fpsCounter++;
                if(fpsCounter >= FPS){
                    fpsCounter = 0;
                    timeLeft--;

                    if(timerCoord.x < DISP_MAX_X && timerCoord.y == DISP_MAX_Y){
                        timerCoord.x++;
                    }
                    else if (timerCoord.x == DISP_MAX_X && timerCoord.y > 0){
                        timerCoord.y--;
                    }
                    else if (timerCoord.x > 0 && timerCoord.y == 0){
                        timerCoord.x--;
                    }
                    else if(timerCoord.x == 0 && timerCoord.y < DISP_MAX_Y){
                        timerCoord.y++;
                    }
                    disp_write(timerCoord, 0);

                }
                
                for(i = 0 ; i < HEIGHT ; i++){
                    linea_t * linea = map+i;
                    pos.y = HEIGHT - i;

                    if(i == 0 || i == HEIGHT/2){
                        for(c = 0 ; c < WIDTH ; c++){
                            pos.x = c+1;
                            disp_write(pos, 0);
                        }
                    }
                    else if(i < HEIGHT/2){
                        for(c = 0 ; c < WIDTH ; c++){
                            pos.x = c+1;
                            disp_write(pos, 0);
                        }
                        for(c = 0 ; c < linea->cant_obj ; c++){
                            int sizePos = 0;
                            for(sizePos = 0 ; sizePos < linea->size ; sizePos++){
                                pos.x = linea->po[c] + sizePos;
                                if(pos.x >= 0 && pos.x <= WIDTH-1){
                                    pos.x++;
                                    disp_write(pos, 1);
                                } 
                            } 
                        } 
                    } 
                    else if (i > HEIGHT/2 && i != HEIGHT-1){
                        for(c = 0 ; c < WIDTH ; c++){
                            pos.x = c+1;
                            disp_write(pos, 1);
                        }
                        
                        for(c = 0 ; c < linea->cant_obj ; c++){
                            int sizePos = 0;
                            for(sizePos = 0 ; sizePos < linea->size ; sizePos++){
                                pos.x = linea->po[c] + sizePos;
                                if(pos.x >= 0 && pos.x <= WIDTH-1){
                                    pos.x++;
                                    disp_write(pos, 0);
                                }
                            }
                        }
                        
                    } 
                    else if(i == HEIGHT-1){
                        for(c = 0 ; c < WIDTH ; c++){
                            pos.x = c+1;
                            disp_write(pos, 1);
                        }
                        if(winPosStates[0] != WIN_OCC){
                            pos.x = WINPOS1 + 1;
                            disp_write(pos, 0);
                        }
                        if(winPosStates[1] != WIN_OCC){
                            pos.x = WINPOS2 + 1;
                            disp_write(pos, 0);
                        }
                        if(winPosStates[2] != WIN_OCC){
                            pos.x = WINPOS3 + 1;
                            disp_write(pos, 0);
                        }
                        if(winPosStates[3] != WIN_OCC){
                            pos.x = WINPOS4 + 1;
                            disp_write(pos, 0);
                        }
                        if(winPosStates[4] != WIN_OCC){
                            pos.x = WINPOS5 + 1;
                            disp_write(pos, 0);
                        }                   
                    }

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
                        default:
                            if(fpsCounter == FPS/5 || fpsCounter == FPS*2/5 || fpsCounter == FPS*3/5 || fpsCounter == FPS*4/5 || fpsCounter == 0){
                                moveLine(linea, i, pRana);
                            }
                        break;
                        }                        
                    }

                    if(RanaCollisions(pRana, &map[pRana->posy]) || !timeLeft){
                        RestarVidas(pRana, 0, "score.txt");
                        for(c = 0 ; c < DISP_MAX_X ; c++){
                            pos.x = c;
                            pos.y = 0;
                            disp_write(pos, 1);
                            pos.y = DISP_MAX_Y;
                            disp_write(pos, 1);
                        }
                        timeLeft = START_TIME;
                    }
                }

                pos.x = pRana->posx;
                pos.y = HEIGHT - pRana->posy;
                ranaColorTimer++;
                if(ranaColorTimer == 5){
                    ranaColorTimer = 0;
                    ranaColor = !(ranaColor);
                }
                
                disp_write(pos, ranaColor); 

                if(!joyMoved){
                    isMoving = 0;
                }
                
                if(joyMoved && !isMoving){
                    isMoving = 1;
                    switch (joyValue)
                    {
                    case UP:
                        MoveRana(pRana, UP, map+rana.posy);
                        break;
                    case DOWN:
                        MoveRana(pRana, DOWN, map+rana.posy);
                        break;
                    case LEFT:
                        MoveRana(pRana, LEFT, map+rana.posy);
                        break;
                    case RIGHT:
                        MoveRana(pRana, RIGHT, map+rana.posy);
                        break;
                    default:
                        break;
                    }
                }

                if(coord.sw == J_PRESS && joyPressed == 0){
                    joyPressed = 1;
                    screen = PAUSE;
                }
                disp_update();
                break;
            }      
            before = clock();
        }
		

		
	} while(!do_exit);	//termina si se presiona el switch
	
	//Borro el display al salir
	disp_clear();
    disp_update();
}
