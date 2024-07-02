/*
testlibraries es un ejemplo de uso de las librerías disdrv y joydrv
Permite mover con el joystick un LED encendido en la matriz de LEDs.
*/
//Como compilar: gcc testLibraries.c disdrv.o joydrv.o -Wall -o testLibs
#include <stdio.h>
#include "disdrv.h"
#include "joydrv.h"
#include "Objetos.h"
#include "Rana.h"
#include <time.h>

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
                        {0,1,1,1,1,0,1,1,1,1,1,1,1,0,0,0},
                        {0,1,0,1,1,0,1,0,1,0,0,1,0,0,0,0},
                        {0,1,1,1,1,0,1,0,1,0,0,1,0,0,0,0},
                        {0,0,0,1,1,0,1,0,1,0,0,1,0,0,0,0},
                        {0,0,0,1,1,1,1,1,1,1,0,1,0,0,0,0},
                        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}};

int main(void)
{
    clock_t before = clock(); //agarro tiempo antes de arrancar
    clock_t difference = 0;
    clock_t ini = clock();
    clock_t lap_time;
    int msec = 0;
    linea_t * pl = CreateWorld(16, 10);
    rana_t rana = {.posx=10/2, .posy=0, .vidas=3};
	
	joy_init();										//inicializa el joystick
	disp_init();									//inicializa el display
	disp_clear();									//limpia todo el display
	dcoord_t pos = {DISP_MAX_X>>1 , DISP_MAX_Y>>1};	//pos es la posición actual, empieza en el centro de la matriz
	joyinfo_t coord = {0,0,J_NOPRESS};							//coordenadas medidas del joystick
	
    CreateObject(pl+3);

    int fpsCounter = 0;
    int screen = MENU;

    do
	{
        lap_time = clock();
        difference = lap_time - before;
        msec = difference * 1000 / CLOCKS_PER_SEC;

        if(msec > (1/FPS)*1000){ //falta el /FPS
            disp_update();	//Actualiza el display con el contenido del buffer
            coord = joy_read();	//Guarda las coordenadas medidas
            disp_clear();

            switch (screen)
            {
            case MENU:
                int i, j;
                for(i = 0 ; i < 16 ; i++){
                    for (j = 0 ; j < 16 ; j++){
                        pos.x = j;
                        pos.y = i;
                        disp_write(pos, mainMenu[i][j]);
                    }
                }
                break;
            
            default:
                break;
            }


            fpsCounter++;
            if(fpsCounter >= FPS){
                fpsCounter = 0;
            }

            int i, c;

            for(i = 0 ; i < 16 ; i++){
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
                
                for(c = 0 ; c < 10 ; c++){
                    pos.x = c;
                    pos.y = i;
                    disp_write(pos, !(*((linea->p_linea)+c)));
                }
            }
            before = clock();
        }
		

		
	} while( coord.sw == J_NOPRESS );	//termina si se presiona el switch
	
	//Borro el display al salir
	disp_clear();
    disp_update();
}
