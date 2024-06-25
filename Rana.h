#include <stdint.h>
enum ARROW_KEYS {UP, DOWN, LEFT, RIGHT};
#define POSX_INI 5
#define POSY_INI 0

void MoveRana(rana_t rana, uint8_t dir);
void RestarVidas(rana_t rana);

typedef struct{
    uint8_t vidas;
    uint8_t posx;
    uint8_t posy;
} rana_t;