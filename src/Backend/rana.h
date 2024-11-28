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

#define POSX_INI (WIDTH/2)
#define POSY_INI (0)

#define NEXTLEVELTRUE 3
#define NEXTLEVELFALSE 2

/*******************************************************************************
 * ESTRUCTURAS Y TIPOS DE DATOS
 ******************************************************************************/

typedef struct{ 
    int8_t dir; //Direccion en la que mira. Se usa para el sprite
    long posx;
    long posy;
    int vidas;
} rana_t;

/*******************************************************************************
 * PROTOTIPOS DE FUNCIONES
 ******************************************************************************/

/** 
* @brief Inicializa (PERO NO DEFINE) la rana con su posicion, vidas y direccion inicial
* @param pRana rana a inicializar
*/
void spawnRana(rana_t* pRana);

/**
 * @brief Resta una vida cuando es llamada. En caso de llegar a cero, se ocupa de accionar el game over.
 * @param pRana se pide para poder bajar las vidas y reiniciar la posicion de la rana en caso de que no haya game over.
 * @param pWD se pide para poder reiniciar el tiempo
*/
void RestarVidas(rana_t * pRana, worldData_t * pWD);

#endif //RANA_H
