#include "worldData.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

linea_t map[HEIGHT];
int vidas = 3;
void createMap(linea_t * p){
    srand(time(NULL));
    int i, c;
    for(i = 0 ; i < HEIGHT ; i++){
        linea_t * linea = p + i;
        linea->cant_obj = (i==0||i==HEIGHT/2||i==HEIGHT-1)?0:3;
        linea->dir = (rand()%2?DER:IZQ);
        linea->size = 3;
        linea->v = 1;
        linea->val_def = (i <= HEIGHT/2)?1:0; // 1 es piso 0 es agua
        for(c = 0 ; c < WIDTH ; c++){
            (linea->plinea)[c] = linea->val_def;
        }
        for(c = 0 ; c < linea->cant_obj ; c++){
            if(i <= HEIGHT/2){
                if(linea->dir = DER){
                    (linea->po)[c] = (c = 0)?(0 - rand()%5):((linea->po)[c-1]-rand()%5); //modificar 5 para spawn rate
                }
                else if(linea->dir = IZQ){
                    (linea->po)[c] = (c = 0)?(WIDTH + rand()%5):((linea->po)[c-1]+rand()%5); //modificar 5 para spawn rate
                }
            }
            else{
                if(linea->dir = DER){
                    (linea->po)[c] = (c = 0)?(0 - rand()%3):((linea->po)[c-1]-rand()%3); //modificar 3 para spawn rate
                }
                else if(linea->dir = IZQ){
                    (linea->po)[c] = (c = 0)?(WIDTH + rand()%3):((linea->po)[c-1]+rand()%3); //modificar 3 para spawn rate
                }
            }
            
        }
    }
}