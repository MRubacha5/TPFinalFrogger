/*******************************************************************************
 * HEADERS
 ******************************************************************************/

#include "rana.h"
#include "worldData.h"
#include "movement.h"
#include "platformConfig.h"
#include "score.h"

/*******************************************************************************
 * MACROs PARA SIMPLIFICAR CODIGO; SON ESPECIFICAS A SUS FUNCIONES
 ******************************************************************************/
#define ISCOLLIDING (((prana->posx >= pl->po[i]) && (prana->posx <= pl->po[i] + pl->size)) || ((prana->posx + RANAWIDTH >= pl->po[i]) && (prana->posx + RANAWIDTH <= pl->po[i] + pl->size)))
#define WINS (WINPOS1 <= prana->posx + RANAWIDTH && WINPOS1 >= prana->posx) //FALTA REPETIR PARA TODAS LAS WINPOS
#define STILLALIVE 10
#define DEADTOP 1
#define DEADNOTOP 0


int winPosStates[5] = {WIN_FREE,WIN_FREE,WIN_FREE,WIN_FREE,WIN_FREE};
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
        prana->posx++;
        
        break;
    case LEFT:
        prana->posx--;
        break;
    }

}

void RanaCollisions(rana_t * prana, linea_t * pl){

    if(!(pl->val_def) && ((prana->posx) + RANAWIDTH >= WIDTH || (prana->posx) < 0)){ //La rana se muere si se va por un costado del agua
        RestarVidas(prana,0, "score.txt");
    }
    int i;

    switch(pl->val_def){
        case UNSAFE:

            if(prana->posy == HEIGHT)//Check for winning frog
            {
                if(WINS)
                Ganar(prana);
                return;
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
                    RestarVidas(prana,0,"score.txt");
                }
            }
            break;

        case SAFE:
            for(i = 0; i < pl->cant_obj; i++){
                if(ISCOLLIDING){
                    RestarVidas(prana,0,"score.txt");
                }
            }
            break;
    }
    
}

int RestarVidas(rana_t* pRana, int score, char* filename){
    //LLAMAR ANIMACION DE MUERTE CORRESPONDIENTE AL FRONTEND QUE SE ESTE USANDO
    vidas--;
    if(!vidas){
        
        int n = gameOver(score, filename);
        return n;

    }
    else{ //si quedan vidas, reinicia la posicion de la rana
        pRana->posx = POSX_INI;
        pRana->posy = POSY_INI;
        pRana->dir = UP;

        return 10;
    }
}

int8_t Ganar (rana_t* pRana){
    int8_t i ,winningFlag = 1;

    switch (pRana->posx)
    {
        case WINPOS1:
            winPosStates[0] = WIN_OCC;
        case WINPOS2:
            winPosStates[1] = WIN_OCC;
        case WINPOS3:
            winPosStates[2] = WIN_OCC;
        case WINPOS4:
            winPosStates[3] = WIN_OCC;
        case WINPOS5:
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


