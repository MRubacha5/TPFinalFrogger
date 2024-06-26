#include "Rana.h"
#include "Objetos.h"


void MoveRana(rana_t* prana, uint8_t dir){
    switch (dir)
    {
    case UP:
        prana->posy++;
        break;
    case DOWN:
        prana->posy--;
        break;
    case RIGHT:
        prana->posx++;
        break;
    case LEFT:
        prana->posx--;
        break;
    }
   
}

void RestarVidas(rana_t* pRana){
    pRana->vidas--;
    if(pRana->vidas == 0){
        //game over
    }
    else{
        pRana->posx = POSX_INI;
        pRana->posy = POSY_INI;
    }
}
