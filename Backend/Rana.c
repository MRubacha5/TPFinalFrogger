#include "Rana.h"
#include "Objetos.h"


void MoveRana(rana_t rana, uint8_t dir){
    switch (dir)
    {
    case UP:
        rana.posy++;
        break;
    case DOWN:
        rana.posy--;
        break;
    case RIGHT:
        rana.posx++;
        break;
    case LEFT:
        rana.posx--;
        break;
    }
    /*
    if(rana.posx > WIDTH || rana.posx < 0 || rana.posy > HEIGHT || rana.posy < 0){
        RestarVidas(rana);
    }
    */
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
