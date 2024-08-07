#include "Rana.h"
#include "Objetos.h"

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

void UpdateRanaData(rana_t * prana, linea_t * pl){
    if((prana->posx) > 15 || (prana->posx) < 0){
        RestarVidas(prana);
    }
    *(((pl+(prana->posy))->plinea)+(prana->posx)) = 1;
}

void RestarVidas(rana_t* pRana){
    vidas--;
    if(!vidas){
        //game over
    }
    else{
        pRana->posx = POSX_INI;
        pRana->posy = POSY_INI;
    }
}
