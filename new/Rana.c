#include "Rana.h"
#include "worldData.h"

extern int vidas;
void MoveRana(rana_t* prana, uint8_t dir, linea_t * pl){
    switch (dir)
    {
    case UP:

        prana->posy++;
        (pl+1)->plinea[prana->posx] = RANA_VAL;
        break;
    case DOWN:

        prana->posy--;
        (pl-1)->plinea[prana->posx] = RANA_VAL;
        break;
    case RIGHT:

        prana->posx++;
        (pl)->plinea[prana->posx] = RANA_VAL;
        break;
    case LEFT:

        prana->posx--;
        (pl)->plinea[prana->posx] = RANA_VAL;
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
        pRana->dir = UP;

    }
}

int8_t Ganar (rana_t* pRana, linea_t * pl){
    int8_t i ,ganar = 0;

    ((pl+HEIGHT)-> plinea)[pRana -> posx] = 4; 
    //Asignar valor 4 a la posicion actual de la rana,ese valor marca que esa casilla esta ocupada x una rana entregada.
    

    for(i=0; i<WIDTH ; i++){

        if(((pl+HEIGHT)->plinea)[i] == 3) ganar = 0;
        
    }
    //leer linea final, para ver si aun quedan posiciones donde entregar la rana
    //si ya no quedan, asignar valor !0 a variable tipo int8_t (cambio Nivel)
    //Si quedan solo resetear la posicion
    
    pRana->posx = POSX_INI;
    pRana->posy = POSY_INI;
    pRana->dir = UP;

    return ganar;
}
