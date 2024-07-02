#ifndef RANA_H
#define RANA_H
#include <stdint.h>
enum ARROW_KEYS {UP, DOWN, LEFT, RIGHT};
#define POSX_INI 5
#define POSY_INI 0

typedef struct{
    uint8_t vidas;
    int8_t posx;
    int8_t posy;
} rana_t;

void MoveRana(rana_t* prana, uint8_t dir);
void RestarVidas(rana_t* pRana);

#endif //RANA_H
