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

int winPosStates[5] = {WIN_OCC,WIN_OCC,WIN_OCC,WIN_FREE,WIN_OCC};
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
        if((!pl->val_def) || (prana->posx <= WIDTH - 2*GSIZEX)) //Evita que la rana vaya OOB en la calle
        {
            prana->posx += GSIZEX;
        }

        break;
    case LEFT:
         if((!pl->val_def) || (prana->posx >= GSIZEX)) //Evita que la rana vaya OOB en la calle
        {
            prana->posx -= GSIZEX;
        }

        break;
    }

}

void RanaCollisions(rana_t * prana, linea_t * pl){

    if(!(pl->val_def) && ((prana->posx) > WIDTH - GSIZEX || (prana->posx) < 0)){ //La rana se muere si se va por un costado del agua
        RestarVidas(prana,0, "score.txt");
    }
    int i;

    switch(pl->val_def){
        case UNSAFE:

            if(prana->posy == HEIGHT)//Check for winning frog
            {
                if(WINPOS1 <= prana->posx + RANAWIDTH && WINPOS1 >= prana->posx)
                {
                    if (winPosStates[0] == WIN_FREE)
                    {
                        Ganar(prana,1);
                    }
                    else 
                    {
                        RestarVidas(prana, 0, "score.txt");
                    }
                }
                if(WINPOS2 <= prana->posx + RANAWIDTH && WINPOS2 >= prana->posx)
                {
                    if (winPosStates[1] == WIN_FREE)
                    {
                        Ganar(prana,2);
                    }
                    else 
                    {
                        RestarVidas(prana, 0, "score.txt");
                    }
                }
                if(WINPOS3 <= prana->posx + RANAWIDTH && WINPOS3 >= prana->posx)
                {
                    if (winPosStates[2] == WIN_FREE)
                    {
                        Ganar(prana,3);
                    }
                    else 
                    {
                        RestarVidas(prana, 0, "score.txt");
                    }
                }
                if(WINPOS4 <= prana->posx + RANAWIDTH && WINPOS4 >= prana->posx)
                {
                    if (winPosStates[3] == WIN_FREE)
                    {
                        Ganar(prana,4);
                    }
                    else 
                    {
                        RestarVidas(prana, 0, "score.txt");
                    }
                }
                if(WINPOS5 <= prana->posx + RANAWIDTH && WINPOS5 >= prana->posx)
                {
                    if (winPosStates[4] == WIN_FREE)
                    {
                        Ganar(prana,5);
                    }
                    else 
                    {
                        RestarVidas(prana, 0, "score.txt");
                    }
                }
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
                    // printf("COLISION: RanaX = %ld, ObjX = %d", prana->posx, pl->po[i]);
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


