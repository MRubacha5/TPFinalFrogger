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
#define ISCOLLIDING (((prana->posx >= pl->po[i]) && (prana->posx <= pl->po[i] + pl->size*GSIZEX)) || ((prana->posx + GSIZEX >= pl->po[i]) && (prana->posx + GSIZEX <= pl->po[i] + pl->size*GSIZEX)))

int winPosStates[5] = {WIN_FREE,WIN_FREE,WIN_OCC,WIN_FREE,WIN_FREE};
extern int vidas;


void spawnRana(linea_t* map, rana_t* pRana){
    pRana->posx = POSX_INI;
    pRana->posy = POSY_INI;
    pRana->dir = UP;
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
        if((!pl->val_def) || (prana->posx <= WIDTH - GSIZEX)) //Evita que la rana vaya OOB en la calle
        {
            prana->posx++;
        }

        break;
    case LEFT:
         if((!pl->val_def) || (prana->posx >= 0)) //Evita que la rana vaya OOB en la calle
        {
            prana->posx--;
        }

        break;
    }

}

int RanaCollisions(rana_t * prana, linea_t * pl){

    if(!(pl->val_def) && ((prana->posx) > WIDTH - GSIZEX || (prana->posx) < 0)){ //La rana se muere si se va por un costado del agua
        return 1;
    }
    int i;

    switch(pl->val_def){
        case UNSAFE:
            if(prana->posy == HEIGHT)//Check for winning frog
            {
                
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
        
        int n = gameOver(score, filename);
        pRana->posx = POSX_INI;
        pRana->posy = POSY_INI;
        pRana->dir = UP;
        return n;

    }
    else{ //si quedan vidas, reinicia la posicion de la rana
        pRana->posx = POSX_INI;
        pRana->posy = POSY_INI;
        pRana->dir = UP;

        return 10;
    }
}

int8_t Ganar (rana_t* pRana, uint8_t winPos){
    int8_t i ,winningFlag = 1;

    switch (winPos)
    {
        case 1:
            winPosStates[0] = WIN_OCC;
        case 2:
            winPosStates[1] = WIN_OCC;
        case 3:
            winPosStates[2] = WIN_OCC;
        case 4:
            winPosStates[3] = WIN_OCC;
        case 5:
            winPosStates[4] = WIN_OCC;
        default:
            break;

    }
    
    for(i=0; i < 5 ; i++){

        if(winPosStates[i] == WIN_FREE){
            winningFlag = 0;
        }
        
    }
    
    pRana->posx = POSX_INI;
    pRana->posy = POSY_INI;
    pRana->dir = UP;

    return winningFlag;
}


