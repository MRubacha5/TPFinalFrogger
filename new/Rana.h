#ifndef RANA_H
#define RANA_H

/*******************************************************************************
 * HEADERS
 ******************************************************************************/

#include <stdint.h>
#include "worldData.h"

/*******************************************************************************
 * CONSTANTES
 ******************************************************************************/

enum ARROW_KEYS {UP, DOWN, LEFT, RIGHT};
#define POSX_INI (WIDTH/2)
#define POSY_INI (HEIGHT-1)


/*******************************************************************************
 * ESTRUCTURAS Y TIPOS DE DATOS
 ******************************************************************************/

typedef struct{
    uint8_t estado; //estado de actividad de la rana. 1 si puede ser controlada y 0 si ya llego al final y no puede ser controlada 
    int8_t posx;
    int8_t posy;
} rana_t;

/*******************************************************************************
 * PROTOTIPOS DE FUNCIONES
 ******************************************************************************/

/**
 * @brief Mueve la rana (prana) en la direccion pedidad (dir). Se ocupa tambien de llamar a ranaCollisions
 * @param prana rana a mover
 * @param dir direccion en la que moverse
 * @param pl linea en la que se encuentra la rana
*/
void MoveRana(rana_t* prana, uint8_t dir, linea_t * pl);

/**
 * @brief Se ocupa de que la rana interactue con el mundo. Tanto para morir si colisiona con algo fatal como para moverse si esta encima de algo como un tronco
 * @param prana rana en cuestion
 * @param pl linea en la que se encuentra la rana
*/
void RanaCollisions(rana_t * prana, linea_t * pl);

/**
 * @brief Resta una vida cuando es llamada. En caso de llegar a cero, se ocupa de accionar el game over.
 * @param pRana se pide para poder reiniciar la posicion de la rana en caso de que no haya game over. 
*/
void RestarVidas(rana_t * pRana);

#endif //RANA_H
