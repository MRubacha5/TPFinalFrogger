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

void RestarVidas(rana_t rana){
    rana.vidas--;
    if(rana.vidas == 0){
        //death
    }
    else{
        rana.posx = POSX_INI;
        rana.posy = POSY_INI;
    }
}
