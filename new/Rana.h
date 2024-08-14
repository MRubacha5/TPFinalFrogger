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
    //Saque estado, no es necesario
    // Agrego Direccion a la rana
    int8_t dir; //Direccion en la que mira. Se usa para el sprite
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

/**
* @brief Desarrolla el protocolo al haber entregado la rana y devuelve un numero != de 0 si todas las ranas ya estan entregadas.
* @param pRana Se pide para reiniciar la posicion de la rana.
* @param pl puntero a linea para poder leer y modificar el mapa.
*/
int8_t Ganar (rana_t * pRana, linea_t * pl);
#endif //RANA_H
