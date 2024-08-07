#include "Rana.h"
#include "worldData.h"

extern int vidas;
void MoveRana(rana_t* prana, uint8_t dir, linea_t * pl){
    switch (dir)
    {
    case UP:
        prana->posy--;
        break;
    case DOWN:
        prana->posy++;
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
    if((prana->posx) > WIDTH || (prana->posx) < 0){ //Resta vidas si la rana se va por un costado del mapa
        RestarVidas(prana);
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
    }
}
