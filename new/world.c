#include "worldData.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int vidas = 3;

void createMap(linea_t * p){ 
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
                if(linea->dir == DER){
                    (linea->po)[c] = (c == 0)?(0 - rand()%5):((linea->po)[c-1]-linea->size-rand()%5); //modificar 5 para spawn rate
                }
                else if(linea->dir == IZQ){
                    (linea->po)[c] = (c == 0)?(WIDTH + rand()%5):((linea->po)[c-1]+linea->size+rand()%5); //modificar 5 para spawn rate
                }
            }
            else{
                if(linea->dir == DER){
                    (linea->po)[c] = (c == 0)?(0 - rand()%3):((linea->po)[c-1]-linea->size-rand()%3); //modificar 3 para spawn rate
                }
                else if(linea->dir == IZQ){
                    (linea->po)[c] = (c == 0)?(WIDTH + rand()%3):((linea->po)[c-1]+linea->size+rand()%3); //modificar 3 para spawn rate
                }
            }
            
        }
    }
}

void moveLine(linea_t * pl){
    int i, j;
    for(j = 0; j < pl->cant_obj; j++){ //recorre los objetos de la linea
        
        switch(pl->dir){ // mueve los objetos en base a la direccion de la linea
            case DER:
                pl->po[j] += 1; 
                if(pl->po[j] > WIDTH){ //si los objetos se van del mapa (esperan un tick mas ya que es mayor y no mayor o igual)
                    pl->po[j] = -pl->size; //reiniciar el objeto al principio
                }
                break;

            case IZQ:
                pl->po[j] -= 1; 
                if(pl->po[j] < 0){ //si los objetos se van del mapa (esperan un tick mas ya que es mayor y no mayor o igual)
                    pl->po[j] = WIDTH; //reiniciar el objeto al principio
                }
                break;
        }
        for(i=0 ; i<WIDTH; i++){
            (pl->plinea)[i] = pl->val_def;
        }
        for(i = 0; i < WIDTH; i++){ //recorre las posiciones de la linea
            if(i==pl->po[j]){ // si hay un objeto que comienza en la posicion
                for(int k = 0; k < pl->size; k++){ // asigna el valor opuesto al default para todo el size del objeto
                     pl->plinea[k] = !pl->val_def;
                }
            }
        }
    }
}