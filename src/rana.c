/*******************************************************************************
 * HEADERS
 ******************************************************************************/

#include "rana.h"
#include "worldData.h"
#include "movement.h"

extern int vidas;

void spawnRana(linea_t* map, rana_t* pRana){
    pRana->posx = POSX_INI;
    pRana->posy = POSY_INI;
    pRana->dir = UP;
    (map+pRana->posy)->plinea[pRana->posx] = RANA_VAL;
}

void MoveRana(rana_t* prana, uint8_t dir, linea_t * pl){
    switch (dir)
    {
    case UP:
        (pl)->plinea[prana->posx] = pl->val_def;
        prana->posy++;
        (pl+1)->plinea[prana->posx] = RANA_VAL;
        
        break;
    case DOWN:
        if(prana->posy){
            (pl)->plinea[prana->posx] = pl->val_def;
            prana->posy--;
            (pl-1)->plinea[prana->posx] = RANA_VAL;
        }
        break;
    case RIGHT:
        (pl)->plinea[prana->posx] = pl->val_def;
        prana->posx++;
        (pl)->plinea[prana->posx] = RANA_VAL;
        
        break;
    case LEFT:
        (pl)->plinea[prana->posx] = pl->val_def;
        prana->posx--;
        (pl)->plinea[prana->posx] = RANA_VAL;
        break;
    }

}

void RanaCollisions(rana_t * prana, linea_t * pl){

    if((prana->posx) >= WIDTH || (prana->posx) < 0){ //Resta vidas si la rana se va por un costado del mapa
        RestarVidas(prana);
    }
        int i,j;

    switch(pl->val_def){
        case UNSAFE:
            uint8_t isFloating = 0;
            for(i = 0; i < pl->cant_obj; i++){
                for(j = 0; j < pl->size; j++){
                    if(prana->posx == (pl->po[i])+j){ //Si la rana esta parada en un tronco
                        isFloating = 1;
                    }
                }
            }
            if(!isFloating){
                RestarVidas(prana);
            }
            break;
        case SAFE:
            for(i = 0; i < pl->cant_obj; i++){
                for(j = 0; j < pl->size; j++){
                    if(prana->posx == (pl->po[i])+j){
                        RestarVidas(prana);
                    }
                }
            }
    }

    
}

void RestarVidas(rana_t* pRana){
    //LLAMAR ANIMACION DE MUERTE CORRESPONDIENTE AL FRONTEND QUE SE ESTE USANDO
    vidas--;
    if(!vidas){
        //game over
    }
    else{ //si quedan vidas, reinicia la posicion de la rana
        pRana->posx = POSX_INI;
        pRana->posy = POSY_INI;
        pRana->dir = UP;

    }
}

int8_t Ganar (rana_t* pRana, linea_t * pl){
    int8_t i ,ganar = 0;

    ((pl+HEIGHT)-> plinea)[pRana -> posx] = WIN_OCC; 
    //Asignar valor 4 a la posicion actual de la rana,ese valor marca que esa casilla esta ocupada x una rana entregada.
    

    for(i=0; i<WIDTH ; i++){

        if(((pl+HEIGHT)->plinea)[i] != WIN_FREE) ganar = 1;
        
    }
    //leer linea final, para ver si aun quedan posiciones donde entregar la rana
    //si ya no quedan, asignar valor !0 a variable tipo int8_t (cambio Nivel)
    //Si quedan solo resetear la posicion
    
    pRana->posx = POSX_INI;
    pRana->posy = POSY_INI;
    pRana->dir = UP;

    return ganar;
}
