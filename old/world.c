#include "worldData.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

linea_t map[HEIGHT];
int vidas = 3;

void createMap(linea_t * p){ 
    int i, c;

    for(i = 0 ; i < HEIGHT ; i++){
        linea_t * linea = p + i;
        linea->cant_obj = 3;
        linea->dir = (rand()%2?DER:IZQ);
        linea->size = 3;
        linea->v = 1;
        linea->val_def = (i <= HEIGHT/2)?1:0; // 1 es piso 0 es agua

        for(c = 0 ; c < WIDTH ; c++){
            (linea->plinea)[c] = linea->val_def;
        }
    }
}

void moveWorld(linea_t * pmundo){
    int i , j;
    for(i = 0; i<HEIGHT; i++){ //recorre las lineas del mundo
        for(j = 0; j < pmundo[i].cant_obj; j++){ //recorre los objetos de la linea
            
            switch(pmundo[i].dir){ // mueve los objetos en base a la direccion de la linea
                case DER:
                    pmundo[i].po[j] += 1; 
                    if(pmundo[i].po[j] > WIDTH){ //si los objetos se van del mapa (esperan un tick mas ya que es mayor y no mayor o igual)
                        pmundo[i].po[j] = 0; //reiniciar el objeto al principio
                    }
                    break;

                case IZQ:
                    pmundo[i].po[j] -= 1; 
                    if(pmundo[i].po[j] < 0){ //si los objetos se van del mapa (esperan un tick mas ya que es mayor y no mayor o igual)
                        pmundo[i].po[j] = WIDTH; //reiniciar el objeto al principio
                    }
                    break;
            }
                
        }
    }
}