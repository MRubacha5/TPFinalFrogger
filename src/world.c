/*******************************************************************************
 * HEADERS
 ******************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "worldData.h"
#include "movement.h"
#include "rana.h"
#include "platformConfig.h"

/*******************************************************************************
 * CONSTANTES CON DEFINE
 ******************************************************************************/

#define LEVELPOSIBILITIES 5

/**************************************************************************************************************
 * PRESETS MAPAS --> 2 niveles hardcodeados; a partir del tercer nivel, se genera pseudo-aleatoriamente
 *************************************************************************************************************/
 
 //Difficulty 0
 
 linea_t agua0[] =  {   {.size = 3, .cant_obj = 4, .v = 2, .po = {0, 4*GSIZEX, 8*GSIZEX, 12*GSIZEX}},
                        {.size = 2, .cant_obj = 3, .v = 2, .po = {WIDTH, WIDTH - 4*GSIZEX, WIDTH - 8*GSIZEX}},
                        {.size = 6, .cant_obj = 2, .v = 2, .po = {2*GSIZEX, 10*GSIZEX}},
                        {.size = 3, .cant_obj = 2, .v = 2, .po = {GSIZEX, 7*GSIZEX}},
                        {.size = 2, .cant_obj = 4, .v = 1, .po = {0, 3*GSIZEX, 6*GSIZEX, 9*GSIZEX}}};
 
 linea_t piso0[] =  {   {.size = 1, .cant_obj = 3, .v = 2, .po = {WIDTH + 2*GSIZEX, WIDTH - 4*GSIZEX+2*GSIZEX, WIDTH - 8*GSIZEX+2*GSIZEX}},
                        {.size = 1, .cant_obj = 3, .v = 2, .po = {WIDTH, WIDTH - 4*GSIZEX, WIDTH - 8*GSIZEX}},
                        {.size = 1, .cant_obj = 3, .v = 2, .po = {WIDTH, WIDTH - 4*GSIZEX, WIDTH - 8*GSIZEX}},
                        {.size = 1, .cant_obj = 2, .v = 5, .po = {0, 4*GSIZEX}},
                        {.size = 2, .cant_obj = 2, .v = 1, .po = {0, 6*GSIZEX}}};         

 //Difficulty 1
 
 linea_t agua1[] =  {   {.size = 4, .cant_obj = 1, .v = 2},
                        {.size = 4, .cant_obj = 1, .v = 1},
                        {.size = 3, .cant_obj = 2, .v = 2},
                        {.size = 3, .cant_obj = 2, .v = 2},
                        {.size = 2, .cant_obj = 4, .v = 1},
                        {.size = 2, .cant_obj = 3, .v = 1},
                        {.size = 2, .cant_obj = 3, .v = 2}};
 
 linea_t piso1[] =  {    {.size = 1, .cant_obj = 0, .v = 1},
                        {.size = 1, .cant_obj = 0, .v = 1},
                        {.size = 1, .cant_obj = 0, .v = 1},
                        {.size = 1, .cant_obj = 3, .v = 1},
                        {.size = 1, .cant_obj = 3, .v = 2},
                        {.size = 2, .cant_obj = 2, .v = 1},
                        {.size = 2, .cant_obj = 2, .v = 2}};

 //Difficulty 2
 
 linea_t agua2[] =  {   {.size = 5, .cant_obj = 1, .v = 2},
                        {.size = 5, .cant_obj = 1, .v = 2},
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

linea_t *aguaPresets[] = {agua0, agua1, agua2};
linea_t *pisoPresets[] = {piso0, piso1, piso2};

int vidas;
int winPosStates[5];
extern int timeLeft;

void createMap(linea_t * p, int difficulty){ 
    srand(time(NULL));
    int i;

    // Reinicio tiempo
    timeLeft = START_TIME; // valor en segundos 

    // Seteo todas las posiciones de victoria vacias
    for (i = 0; i < 5; i++)
    {
        winPosStates[i] = WIN_FREE;
    }

    for(i = 0 ; i < HEIGHT ; i++){
        linea_t * linea = p + i;

        //Asigno objetos a cada linea
        if(i<HEIGHT/2 && i != 0){
            *(linea) = pisoPresets[difficulty][i-1];
        }
        else if(i > HEIGHT/2 && i != HEIGHT-1){
            *(linea) = aguaPresets[difficulty][i-HEIGHT/2-1];
        }
        else{
            linea->cant_obj = 0;
        }

        //Asigno direccion de movimiento
        if(linea->size == 2 && i < HEIGHT/2)
        {
            linea->dir = IZQ;
        }
        else if(i < HEIGHT/2 && i != 0)
        {
            linea->dir = (i%2?IZQ:DER);
        }
        else if(i > HEIGHT/2 && i != HEIGHT-1)
        {
            linea->dir = ((i+2)%3?DER:IZQ);
        }

        linea->val_def = (i <= HEIGHT/2)?SAFE:UNSAFE; // 1 es piso 0 es agua

        //Espaciado entre objetos; aleatorio a partir del nivel 3
        /*for(c = 0 ; c < linea->cant_obj ; c++){
            if(i <= HEIGHT/2){
                if(linea->dir == DER){
                    (linea->po)[c] = (c == 0)?(-1):GSIZEX*((linea->po)[c-1]-linea->size-rand()%5-1); //modificar 5 para spawn rate
                }
                else if(linea->dir == IZQ){
                    (linea->po)[c] = (c == 0)?(WIDTH + GSIZEX):GSIZEX*((linea->po)[c-1]+linea->size+rand()%5+1); //modificar 5 para spawn rate
                }
            }
            else{
                if(linea->dir == DER){
                    (linea->po)[c] = (c == 0)?(-1):GSIZEX*((linea->po)[c-1]-linea->size-rand()%3-1); //modificar 3 para spawn rate
                }
                else if(linea->dir == IZQ){
                    (linea->po)[c] = (c == 0)?(WIDTH + GSIZEX):GSIZEX*((linea->po)[c-1]+linea->size+rand()%3+1); //modificar 3 para spawn rate
                }
            }
        }*/
    }
}

void moveLine(linea_t * pl, int lineaPosY, rana_t* pRana){
    int i,j;
    
    if(lineaPosY > HEIGHT/2 && lineaPosY == pRana->posy){
        for(i=0; i < pl->cant_obj; i++){
            if(((pRana->posx >= pl->po[i]) && (pRana->posx <= pl->po[i] + pl->size*GSIZEX)) || ((pRana->posx + GSIZEX >= pl->po[i]) && (pRana->posx + GSIZEX <= pl->po[i] + pl->size*GSIZEX))){ //Si la rana esta parada en un tronco, se mueve con el 
                        pRana->posx += pl->dir;
                    }
        }   
    } 

    for(j = 0; j < pl->cant_obj; j++){ //recorre los objetos de la linea
        
        switch(pl->dir){ // mueve los objetos en base a la direccion de la linea
            case DER:
                (pl->po)[j] += 1; 
                if(pl->po[j] > WIDTH + GSIZEX){ 
                    pl->po[j] = -GSIZEX*pl->size; //reiniciar el objeto al principio
                }
                break;

            case IZQ:
                (pl->po)[j] -= 1; 
                if((pl->po)[j] < -pl->size*GSIZEX){ //si los objetos se van del mapa (esperan un tick mas ya que es mayor y no mayor o igual)
                    (pl->po)[j] = WIDTH + GSIZEX; //reiniciar el objeto al principio
                }
                break;
        }
        
    }
}
