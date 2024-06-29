/*
testlibraries es un ejemplo de uso de las librerías disdrv y joydrv
Permite mover con el joystick un LED encendido en la matriz de LEDs.
*/
//Como compilar: gcc testLibraries.c disdrv.o joydrv.o -Wall -o testLibs
#include <stdio.h>
#include "Objetos.h"
#include "Rana.h"
#include <time.h>

#define FPS 60
#define THRESHOLD 40	//Límite a partir del cual se mueve el LED encendido

int main(void)
{
    clock_t ini = clock();      //clock inicial
    clock_t before = clock();   //agarro tiempo antes de arrancar
    clock_t lap_time;
    clock_t difference = 0;
    int msec = 0, dsec = 0;
    linea_t * pl = CreateWorld(16, 10);
    rana_t rana = {.posx=10/2, .posy=0, .vidas=3};
	CreateObject(pl+3);

    do
	{
        lap_time = clock();
        difference = lap_time - before;
        msec = difference * 1000 / CLOCKS_PER_SEC;
        dsec = (((lap_time - ini) * 10 / CLOCKS_PER_SEC));

        if(msec > (1/FPS)*1000){ //falta el /FPS
            
            int i, c;

            for(i = 0 ; i < 16 ; i++){

                if((pl+i)->cant_obj > 0 && dsec % (10/((pl+i)->v)) == 0){
                    MoveObject(pl+i);
                }

                linea_t * linea = pl+i;
                for(c = 0 ; c < 10 ; c++){
                    printf("%d\t", *(((pl+i)->p_linea)+c));
                }
                printf("\n");
            }
            printf("Pos x: %d, size of obj: %d\n", (pl+3)->po->x, (pl+3)->size);
            printf("\n\n");
            before = clock();
        }
		

		
	} while(1);	//termina si se presiona el switch
	
	//Borro el display al salir
}