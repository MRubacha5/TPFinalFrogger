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

/*******************************************************************************
 * ESTRUCTURAS Y TIPOS DE DATOS
 ******************************************************************************/

typedef struct{ 
    int8_t dir; //Direccion en la que mira. Se usa para el sprite
    long posx;
    long posy;
} rana_t;

/*******************************************************************************
 * PROTOTIPOS DE FUNCIONES
 ******************************************************************************/

/** 
* @brief Inicializa (PERO NO DEFINE) la rana en el mapa que se le indique con su posicion y direccion inicial
* @param map mapa donde estara la rana
* @param pRana rana a inicializar
*/
void spawnRana(linea_t* map, rana_t* pRana);

/**
 * @brief Resta una vida cuando es llamada. En caso de llegar a cero, se ocupa de accionar el game over.
 * @param pRana se pide para poder reiniciar la posicion de la rana en caso de que no haya game over.
 * @param score the current score in case it dies and has to be included in top 10.
 * @param filename score.txt, is a list of top 10 scores. 
*/
int RestarVidas(rana_t * pRana, int score, char *filename);

#endif //RANA_H
