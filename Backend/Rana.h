#ifndef RANA_H

#define RANA_H
#include <stdint.h>
#include "Objetos.h"
enum ARROW_KEYS {UP, DOWN, LEFT, RIGHT};
#define POSX_INI ((int)WIDTH/2)
#define POSY_INI (HEIGHT-1)

typedef struct{
    uint8_t vidas;
    int8_t posx;
    int8_t posy;
} rana_t;

void MoveRana(rana_t* prana, uint8_t dir, linea_t * pl);
void RestarVidas(rana_t* pRana);

#endif //RANA_H
