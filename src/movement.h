#ifndef MOVEMENT_H
#define MOVEMENT_H

/*******************************************************************************
 * HEADERS
 ******************************************************************************/

#include <stdint.h>

#include "rana.h"
#include "worldData.h"

/*******************************************************************************
 * CONSTANTES
 ******************************************************************************/

enum ARROW_KEYS {UP, DOWN, LEFT, RIGHT}; 

// direcciones de movimiento para objetos
#define IZQ -1
#define DER 1

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
 * @brief Se ocupa de mover todos los objetos en el mundo. NO TIENE EN CUENTA LA VELOCIDAD Y DEBERA SER LLAMADA ACORDEMENTE
 * @param plinea Puntero a la linea en cuestion
*/
void moveLine(linea_t * plinea);

#endif //MOVEMENT_H