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
#include "score.h"

/*******************************************************************************
 * CONSTANTES CON DEFINE
 ******************************************************************************/

#define LEVELPOSIBILITIES 5

#if defined(ALLEGRO)
    #define LOGMOVEMENTCOND (((pRana->posx - HITBOXWIDTH/2.0 >= pl->po[i]) && (pRana->posx - HITBOXWIDTH/2.0 <= pl->po[i] + (pl->size)*GSIZEX)) || ((pRana->posx + HITBOXWIDTH/2.0 >= pl->po[i]) && (pRana->posx + HITBOXWIDTH/2.0 <= pl->po[i] + (pl->size)*GSIZEX)))
#elif defined(RASPI)
    #define LOGMOVEMENTCOND ((pRana->posx >= pl->po[i]) && (pRana->posx <= pl->po[i] + (pl->size-1)))    
#else
    #error("No platform defined")
#endif

/**************************************************************************************************************
 * PRESETS MAPAS --> 2 niveles hardcodeados; a partir del tercer nivel, se genera pseudo-aleatoriamente
 *************************************************************************************************************/
 
 //Difficulty 0
 
static const linea_t agua0[] =  {   {.size = 3, .cant_obj = 4, .v = 2, .po = {0, 4*GSIZEX, 8*GSIZEX, 12*GSIZEX}},
                        {.size = 2, .cant_obj = 3, .v = 2, .po = {WIDTH, WIDTH - 4*GSIZEX, WIDTH - 8*GSIZEX}},
                        {.size = 6, .cant_obj = 2, .v = 2, .po = {2*GSIZEX, 10*GSIZEX}},
                        {.size = 3, .cant_obj = 2, .v = 2, .po = {GSIZEX, 7*GSIZEX}},
                        {.size = 2, .cant_obj = 4, .v = 1, .po = {0, 3*GSIZEX, 6*GSIZEX, 9*GSIZEX}}};
 
static const linea_t piso0[] =  {   {.size = 1, .cant_obj = 3, .v = 2, .po = {WIDTH + 2*GSIZEX, WIDTH - 4*GSIZEX+2*GSIZEX, WIDTH - 8*GSIZEX+2*GSIZEX}},
                        {.size = 1, .cant_obj = 3, .v = 2, .po = {WIDTH, WIDTH - 4*GSIZEX, WIDTH - 8*GSIZEX}},
                        {.size = 1, .cant_obj = 3, .v = 2, .po = {WIDTH, WIDTH - 4*GSIZEX, WIDTH - 8*GSIZEX}},
                        {.size = 1, .cant_obj = 2, .v = 5, .po = {0, 4*GSIZEX}},
                        {.size = 2, .cant_obj = 2, .v = 1, .po = {0, 6*GSIZEX}}};         

 //Difficulty 1
 
static const linea_t agua1[] =  {   {.size = 3, .cant_obj = 4, .v = 4, .po = {0, 4*GSIZEX, 8*GSIZEX, 12*GSIZEX}},
                        {.size = 2, .cant_obj = 3, .v = 2, .po = {WIDTH, WIDTH - 4*GSIZEX, WIDTH - 8*GSIZEX}},
                        {.size = 6, .cant_obj = 2, .v = 2, .po = {2*GSIZEX, 10*GSIZEX}},
                        {.size = 3, .cant_obj = 2, .v = 2, .po = {GSIZEX, 7*GSIZEX}},
                        {.size = 2, .cant_obj = 4, .v = 1, .po = {0, 3*GSIZEX, 6*GSIZEX, 9*GSIZEX}}};
 
static const  linea_t piso1[] =  {    {.size = 1, .cant_obj = 3, .v = 4, .po = {WIDTH + 2*GSIZEX, WIDTH - 4*GSIZEX+2*GSIZEX, WIDTH - 8*GSIZEX+2*GSIZEX}},
                        {.size = 1, .cant_obj = 3, .v = 2, .po = {WIDTH, WIDTH - 4*GSIZEX, WIDTH - 8*GSIZEX}},
                        {.size = 1, .cant_obj = 3, .v = 2, .po = {WIDTH, WIDTH - 4*GSIZEX, WIDTH - 8*GSIZEX}},
                        {.size = 1, .cant_obj = 2, .v = 5, .po = {0, 4*GSIZEX}},
                        {.size = 2, .cant_obj = 2, .v = 1, .po = {0, 6*GSIZEX}}};

 //Difficulty 2 (No son constantes asi la generacion puede modificar algunos parametros)
 
static linea_t agua2[] =  {   {.size = 3, .cant_obj = 4, .v = 4, .po = {0, 4*GSIZEX, 8*GSIZEX, 12*GSIZEX}},
                        {.size = 2, .cant_obj = 3, .v = 2, .po = {WIDTH, WIDTH - 4*GSIZEX, WIDTH - 8*GSIZEX}},
                        {.size = 6, .cant_obj = 2, .v = 2, .po = {2*GSIZEX, 10*GSIZEX}},
                        {.size = 3, .cant_obj = 2, .v = 2, .po = {GSIZEX, 7*GSIZEX}},
                        {.size = 2, .cant_obj = 4, .v = 1, .po = {0, 3*GSIZEX, 6*GSIZEX, 9*GSIZEX}}};
 
static linea_t piso2[] =  {    {.size = 1, .cant_obj = 3, .v = 2, .po = {WIDTH + 2*GSIZEX, WIDTH - 4*GSIZEX+2*GSIZEX, WIDTH - 8*GSIZEX+2*GSIZEX}},
                        {.size = 1, .cant_obj = 3, .v = 2, .po = {WIDTH, WIDTH - 4*GSIZEX, WIDTH - 8*GSIZEX}},
                        {.size = 1, .cant_obj = 3, .v = 2, .po = {WIDTH, WIDTH - 4*GSIZEX, WIDTH - 8*GSIZEX}},
                        {.size = 1, .cant_obj = 2, .v = 5, .po = {0, 4*GSIZEX}},
                        {.size = 2, .cant_obj = 2, .v = 1, .po = {0, 6*GSIZEX}}};


/*******************************************************************************/

static const linea_t *aguaPresets[] = {agua0, agua1, agua2};
static const linea_t *pisoPresets[] = {piso0, piso1, piso2};

void createMap(linea_t * p, worldData_t * worldData){ 
    srand(time(NULL));
    int i;

    // Reinicio tiempo (menor a mayor nivel de forma asintotica)
    worldData->timeLeft = START_TIME/(1+(worldData->difficulty/10.0)); // valor en segundos 

    // Seteo todas las posiciones de victoria vacias
    for (i = 0; i < 5; i++)
    {
        worldData->winPosStates[i] = WIN_FREE;
    }

    for(i = 0 ; i < HEIGHT ; i++){
        linea_t * linea = p + i;

        if (worldData->difficulty < 2)
        {
            //Asigno objetos a cada linea
            if(i<HEIGHT/2 && i != 0){
                *(linea) = pisoPresets[worldData->difficulty][i-1];
            }
            else if(i > HEIGHT/2 && i != HEIGHT-1){
                *(linea) = aguaPresets[worldData->difficulty][i-HEIGHT/2-1];
            }
            else{
                linea->cant_obj = 0;
            }
        }
        else // Generacion aleatoria a partir del nivel 3; usa presets[2] pero varia los parametros
        {
            if(i<HEIGHT/2 && i != 0){
                *(linea) = pisoPresets[2][rand()%5];
            }
            else if(i > HEIGHT/2 && i != HEIGHT-1){
                *(linea) = aguaPresets[2][rand()%5];
            }
            else{
                linea->cant_obj = 0;
            }
        }

        //Asigno direccion de movimiento. Consistente para asegurar jugabilidad
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

        linea->val_def = (i <= HEIGHT/2)?SAFE:UNSAFE; //SAFE es la calle y UNSAFE es el agua

    
       if(worldData->difficulty > 2)
       {
            //25% mas velocidad (recortado al valor entero) por nivel a partir del 4
            linea->v = (int)((linea->v)*((worldData->difficulty)/4.0)); 
       }
 
    }
}

void moveLine(linea_t * pl, int lineaPosY, rana_t* pRana){
    int i,j;
    
    if(lineaPosY > HEIGHT/2 && lineaPosY == pRana->posy){
        for(i=0; i < pl->cant_obj; i++){
            if(LOGMOVEMENTCOND){ //Si la rana esta parada en un tronco, se mueve con el 
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

void gameStart (linea_t * map, rana_t * pRana, worldData_t * pWorldData)
{
    pRana->vidas = 3;
    pWorldData->difficulty = 0;
    createMap(map,pWorldData->difficulty);
    spawnRana(map, pRana);
    currentScore = 0;
    intToChar (6,scorestr,currentScore);
    ct_score (0,5,0,5,0);
}