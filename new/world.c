#include "worldData.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

srand(time(NULL));

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