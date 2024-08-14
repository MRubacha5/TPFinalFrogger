/*
testlibraries es un ejemplo de uso de las librerías disdrv y joydrv
Permite mover con el joystick un LED encendido en la matriz de LEDs.
*/
//Como compilar: gcc testLibraries.c disdrv.o joydrv.o -Wall -o testLibs
#include <stdio.h>
#include <time.h>
#include "worldData.h"

#define FPS 60
#define THRESHOLD 40	//Límite a partir del cual se mueve el LED encendido

linea_t map[HEIGHT];

int main(void)
{
    clock_t ini = clock();      //clock inicial
    clock_t before = clock();   //agarro tiempo antes de arrancar
    clock_t lap_time;
    clock_t difference = 0;
    int msec = 0, dsec = 0;

    createMap(map,1);

    do
	{
        lap_time = clock();
        difference = lap_time - before;
        msec = difference * 1000 / CLOCKS_PER_SEC;
        dsec = (((lap_time - ini) * 10 / CLOCKS_PER_SEC));

        if(msec > (1)*1000){ //falta el /FPS
            
            int i, c;

            for(i = HEIGHT-1 ; i >= 0 ; i--){
                linea_t * linea = map+i;

                for(c = 0 ; c < WIDTH ; c++){
                    printf("%d\t", *(((linea)->plinea)+c));
                }
                

                if(linea->cant_obj > 0 && dsec % (10/(linea->v)) == 0){      
                    moveLine(linea);
                    printf("Se movio: Linea: %d, X: %d,%d,%d,%d,%d, V: %d", i, linea->po[0],linea->po[1],linea->po[2],linea->po[3],linea->po[4] ,linea->v);
                } 
                printf("\n");
            }
            printf("\n\n");
            before = clock();
        }
		
		
	} while(1);	//termina si se presiona el switch
	
    
	//Borro el display al salir
}
