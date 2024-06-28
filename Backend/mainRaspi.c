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

#define THRESHOLD 40	//Límite a partir del cual se mueve el LED encendido

int main(void)
{
    linea_t * pl = CreateWorld(16, 10);
    rana_t rana = {.posx=10/2, .posy=0, .vidas=3};
	
	joy_init();										//inicializa el joystick
	disp_init();									//inicializa el display
	disp_clear();									//limpia todo el display
	dcoord_t pos = {DISP_MAX_X>>1 , DISP_MAX_Y>>1};	//pos es la posición actual, empieza en el centro de la matriz
	joyinfo_t coord = {0,0,J_NOPRESS};							//coordenadas medidas del joystick
	do
	{
		disp_update();	//Actualiza el display con el contenido del buffer
		coord = joy_read();	//Guarda las coordenadas medidas
		disp_clear();
        int i, c;
		for(i = 0 ; i < 16 ; i++){
            linea_t * linea = pl+i;
            for(c = 0 ; c < 10 ; c++){
                pos.x = c;
                pos.y = i;
                disp_write(pos, !(linea->val_def));
            }
        }

		
	} while( coord.sw == J_NOPRESS );	//termina si se presiona el switch
	
	//Borro el display al salir
	disp_clear();
    disp_update();
}
