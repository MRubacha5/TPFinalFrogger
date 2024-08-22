#include "worldData.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

/*****************************************************************************
 * PRESETS MAPAS --> definimos presets de velocidad, cantidad objetos y tamano
 *****************************************************************************/
 
 //Dificulty 0
 
 linea_t agua0[] =  {   {.size = 4, .cant_obj = 2, .v = 2},
                        {.size = 4, .cant_obj = 2, .v = 1},
                        {.size = 3, .cant_obj = 3, .v = 2},
                        {.size = 3, .cant_obj = 2, .v = 2},
                        {.size = 2, .cant_obj = 5, .v = 1},
                        {.size = 2, .cant_obj = 4, .v = 1},
                        {.size = 2, .cant_obj = 3, .v = 2}};
 
linea_t piso0[] =  {    {.size = 1, .cant_obj = 5, .v = 1},
                        {.size = 1, .cant_obj = 4, .v = 1},
                        {.size = 1, .cant_obj = 3, .v = 2},
                        {.size = 2, .cant_obj = 3, .v = 1},
                        {.size = 2, .cant_obj = 2, .v = 2}};

 //Dificulty 1
 
 linea_t agua1[] =  {   {.size = 5, .cant_obj = 1, .v = 2},
                        {.size = 4, .cant_obj = 2, .v = 2},
                        {.size = 3, .cant_obj = 2, .v = 2},
                        {.size = 3, .cant_obj = 2, .v = 1},
                        {.size = 2, .cant_obj = 3, .v = 2},
                        {.size = 2, .cant_obj = 4, .v = 1}};
 
linea_t piso1[] =  {    {.size = 1, .cant_obj = 7, .v = 1},
                        {.size = 1, .cant_obj = 6, .v = 1},
                        {.size = 1, .cant_obj = 5, .v = 1},
                        {.size = 1, .cant_obj = 4, .v = 2},
                        {.size = 2, .cant_obj = 4, .v = 1},
                        {.size = 2, .cant_obj = 3, .v = 2},
                        {.size = 1, .cant_obj = 2, .v = 3}};

 //Dificulty 2
 
 linea_t agua2[] =  {   {.size = 5, .cant_obj = 1, .v = 2},
                        {.size = 4, .cant_obj = 2, .v = 2},
                        {.size = 3, .cant_obj = 2, .v = 2},
                        {.size = 3, .cant_obj = 2, .v = 1},
                        {.size = 2, .cant_obj = 3, .v = 2},
                        {.size = 2, .cant_obj = 4, .v = 1}};
 
linea_t piso2[] =  {    {.size = 1, .cant_obj = 7, .v = 1},
                        {.size = 1, .cant_obj = 6, .v = 1},
                        {.size = 1, .cant_obj = 5, .v = 1},
                        {.size = 1, .cant_obj = 4, .v = 2},
                        {.size = 2, .cant_obj = 4, .v = 1},
                        {.size = 2, .cant_obj = 3, .v = 2},
                        {.size = 1, .cant_obj = 2, .v = 3}};         

/*******************************************************************************/

int vidas = 3;

void createMap(linea_t * p, int difficulty){ 
    int i, c;
    srand(time(NULL));
    for(i = 0 ; i < HEIGHT ; i++){
        linea_t * linea = p + i;
        linea->cant_obj = (i==0||i==HEIGHT/2||i==HEIGHT-1)?0:3;
        linea->dir = (rand()%2?DER:IZQ);
        linea->size = 3;
        linea->v = 1;
        linea->val_def = (i <= HEIGHT/2)?SAFE:UNSAFE; // 1 es piso 0 es agua
        for(c = 0 ; c < WIDTH ; c++){
            (linea->plinea)[c] = linea->val_def;
        }
        for(c = 0 ; c < 5 ; c++){
            (linea->po)[c] = 0;
        }
        for(c = 0 ; c < linea->cant_obj ; c++){
            if(i <= HEIGHT/2){
                if(linea->dir == DER){
                    (linea->po)[c] = (c == 0)?(0 - rand()%5-1):((linea->po)[c-1]-linea->size-rand()%5-1); //modificar 5 para spawn rate
                }
                else if(linea->dir == IZQ){
                    (linea->po)[c] = (c == 0)?(WIDTH + rand()%5+1):((linea->po)[c-1]+linea->size+rand()%5+1); //modificar 5 para spawn rate
                }
            }
            else{
                if(linea->dir == DER){
                    (linea->po)[c] = (c == 0)?(0 - rand()%3-1):((linea->po)[c-1]-linea->size-rand()%3-1); //modificar 3 para spawn rate
                }
                else if(linea->dir == IZQ){
                    (linea->po)[c] = (c == 0)?(WIDTH + rand()%3+1):((linea->po)[c-1]+linea->size+rand()%3+1); //modificar 3 para spawn rate
                }
            }
            
        }
    }
    for(i = 0 ; i < WIDTH ; i++){
        if(i%3==1){
            (p+HEIGHT-1)->plinea[i] = 1;
        }
        else{
            (p+HEIGHT-1)->plinea[i] = 0;
        }
    }
}

void moveLine(linea_t * pl){
    int i, j, c;
 
    for(i=0 ; i<WIDTH; i++){
        if((pl->plinea)[i] != RANA_VAL){
            (pl->plinea)[i] = pl->val_def;
        }

    }
    for(j = 0; j < pl->cant_obj; j++){ //recorre los objetos de la linea
        
        switch(pl->dir){ // mueve los objetos en base a la direccion de la linea
            case DER:
                (pl->po)[j] += 1; 
                if(pl->po[j] > WIDTH){ //si los objetos se van del mapa (esperan un tick mas ya que es mayor y no mayor o igual)
                    pl->po[j] = 0 - (pl->size); //reiniciar el objeto al principio
                }
                break;

            case IZQ:
                (pl->po)[j] -= 1; 
                if((pl->po)[j] < 1-(pl->size)){ //si los objetos se van del mapa (esperan un tick mas ya que es mayor y no mayor o igual)
                    (pl->po)[j] = WIDTH; //reiniciar el objeto al principio
                }
                break;
        }
        
        int posx = (pl->po)[j];
        for(c = 0 ; c < pl->size ; c++){ //cambio la pos x y las siguientes size posiciones al valor  del obj
            if(posx+c >= 0 && posx+c < WIDTH){ //verifico que quiero modificar un valor dentro del rango de valores modificables
                (pl->plinea)[posx+c] = !(pl->val_def);
            }
        }

        

    }

}