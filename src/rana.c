/*******************************************************************************
 * HEADERS
 ******************************************************************************/

#include "rana.h"
#include "worldData.h"
#include "movement.h"
#include "platformConfig.h"
#include "score.h"

/*******************************************************************************
 * MACROS PARA SIMPLIFICAR CODIGO; SON ESPECIFICAS A SUS FUNCIONES 
 ******************************************************************************/
#if defined(ALLEGRO)
    #define ISCOLLIDING (((prana->posx - HITBOXWIDTH/2.0 >= pl->po[i]) && (prana->posx - HITBOXWIDTH/2.0 <= pl->po[i] + (pl->size)*GSIZEX)) || ((prana->posx + HITBOXWIDTH/2.0 >= pl->po[i]) && (prana->posx + HITBOXWIDTH/2.0 <= pl->po[i] + (pl->size)*GSIZEX)))
    #define WINS(x) (((prana->posx - HITBOXWIDTH/2.0 >= (x) - HITBOXWIDTH/3.0) && (prana->posx - HITBOXWIDTH/2.0 <= (x) + HITBOXWIDTH/3.0)) || ((prana->posx + HITBOXWIDTH/2.0 >= (x) - HITBOXWIDTH/3.0 && (prana->posx + HITBOXWIDTH/2.0 <= (x) + HITBOXWIDTH/3.0))) || ((prana->posx - HITBOXWIDTH/2.0 <= (x) - HITBOXWIDTH/3.0 && (prana->posx + HITBOXWIDTH/2.0 >= (x) + HITBOXWIDTH/3.0))))
#elif defined(RASPI)
    #define ISCOLLIDING ((prana->posx >= pl->po[i]) && (prana->posx <= pl->po[i] + (pl->size-1)*GSIZEX))
    #define WINS(x) (((prana->posx - HITBOXWIDTH/2.0 >= (x) - HITBOXWIDTH/3.0) && (prana->posx - HITBOXWIDTH/2.0 <= (x) + HITBOXWIDTH/3.0)) || ((prana->posx + HITBOXWIDTH/2.0 >= (x) - HITBOXWIDTH/3.0 && (prana->posx + HITBOXWIDTH/2.0 <= (x) + HITBOXWIDTH/3.0))) || ((prana->posx - HITBOXWIDTH/2.0 <= (x) - HITBOXWIDTH/3.0 && (prana->posx + HITBOXWIDTH/2.0 >= (x) + HITBOXWIDTH/3.0))))
#else
    #error("No platform defined")
#endif

extern int winPosStates[5];
extern int vidas;
extern int timeLeft;

/*******************************************************************************
 * PROTOTIPOS DE FUNCIONES
 ******************************************************************************/

static void reSpawnRana(rana_t* pRana);
static int8_t Ganar (rana_t* pRana, uint8_t winPos);

void spawnRana(linea_t* map, rana_t* pRana){
    pRana->posx = POSX_INI;
    pRana->posy = POSY_INI;
    pRana->dir = UP;
    
}

static void reSpawnRana(rana_t* pRana){
    pRana->posx = POSX_INI;
    pRana->posy = POSY_INI;
    pRana->dir = UP;
    //ct_score (0,5,0,3,0);
}

void MoveRana(rana_t* prana, uint8_t dir, linea_t * pl){
    switch (dir)
    {
    case UP:
        prana->posy++;
        
        break;
    case DOWN:
        if(prana->posy){
            prana->posy--;
        }
        break;
    case RIGHT:
        if((!pl->val_def) || (prana->posx <= WIDTH - HITBOXWIDTH/2.0)) //Evita que la rana vaya OOB en la calle
        {
            prana->posx++;
        }

        break;
    case LEFT:
         if((!pl->val_def) || (prana->posx >= HITBOXWIDTH/2.0)) //Evita que la rana vaya OOB en la calle
        {
            prana->posx--;
        }

        break;
    }
    prana->dir = dir;

}

int RanaCollisions(rana_t * prana, linea_t * pl){

    if(!(pl->val_def) && ((prana->posx) > WIDTH - HITBOXWIDTH/2.0 || (prana->posx) < HITBOXWIDTH/2.0)){ //La rana se muere si se va por un costado del agua
        return 1;
    }

    int i;
    switch(pl->val_def){
        case UNSAFE:
            if(prana->posy == HEIGHT-1)//Check for winning frog
            {
                if(WINS(WINPOS1))
                {
                    if (winPosStates[0] == WIN_FREE)
                    {
                        return Ganar(prana,1);
                        timeLeft = START_TIME;
                        
                    }
                    else
                    {
                        return 1;
                    }
                }
                else if(WINS(WINPOS2))
                {
                    if (winPosStates[1] == WIN_FREE)
                    {
                        return Ganar(prana,2);
                        timeLeft = START_TIME;
                    }
                    else 
                    {
                        return 1;
                    }
                }
                else if(WINS(WINPOS3))
                {
                    if (winPosStates[2] == WIN_FREE)
                    {
                        return Ganar(prana,3);
                        timeLeft = START_TIME;
                    }
                    else 
                    {
                        return 1;
                    }
                }
                else if(WINS(WINPOS4))
                {
                    if (winPosStates[3] == WIN_FREE)
                    {
                        return Ganar(prana,4);
                        timeLeft = START_TIME;
                    }
                    else 
                    {
                        return 1;
                    }
                }
                else if(WINS(WINPOS5))
                {
                    if (winPosStates[4] == WIN_FREE)
                    {
                        return Ganar(prana,5);
                        timeLeft = START_TIME;
                    }
                    else 
                    {
                        return 1;
                    }
                }
                else
                {
                    return 1;
                }
            }
            else
            {
                uint8_t isFloating = 0;

                for(i = 0; i < pl->cant_obj; i++){

                    if(ISCOLLIDING){ //Si la rana esta parada en un tronco
                        isFloating = 1;
                    }
        
                }
                if(!isFloating){
                    return 1;
                }
            }
            break;

        case SAFE:
            for(i = 0; i < pl->cant_obj; i++){
                if(ISCOLLIDING){
                    return 1;
                }
            }
            break;
    }
    return 0;
    
}

int RestarVidas(rana_t* pRana, int score, char* filename){
    vidas--;
    if(!vidas){
        return 0;

    }
    else{ //si quedan vidas, reinicia la posicion de la rana
        reSpawnRana(pRana);
        return 0;
    }
}

static int8_t Ganar (rana_t* pRana, uint8_t winPos){
    int8_t iterations ,winningFlag = 2; // 2 para diferenciar del 1 en colisiones (que significa muerte)

    switch (winPos)
    {
        case 1:
            winPosStates[0] = WIN_OCC;
            break;
        case 2:
            winPosStates[1] = WIN_OCC;
            break;
        case 3:
            winPosStates[2] = WIN_OCC;
            break;
        case 4:
            winPosStates[3] = WIN_OCC;
            break;
        case 5:
            winPosStates[4] = WIN_OCC;
            break;
        default:
            break;

    }
    
    iterations = 0;

    for(iterations=0; iterations < 5 ; iterations++){

        if(winPosStates[iterations] == WIN_FREE){
            winningFlag = 0;
        }
        
    }

    reSpawnRana(pRana);
    
    timeLeft = START_TIME;

    return winningFlag;
}


