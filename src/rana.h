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
    //Saque estado, no es necesario
    // Agrego Direccion a la rana
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

/**
* @brief Desarrolla el protocolo al haber entregado la rana y devuelve un numero != de 0 si todas las ranas ya estan entregadas.
* @param pRana Se pide para reiniciar la posicion de la rana.
* @param winPos Se utiliza para enviar la posicion en particular donde acaba de llegar la rana
*/
int8_t Ganar (rana_t * pRana, uint8_t winPos);

#endif //RANA_H
