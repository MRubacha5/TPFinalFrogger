#ifndef WORLDDATA_H
#define WORLDDATA_H

/*******************************************************************************
 * HEADERS
 ******************************************************************************/

#include <stdint.h>

/*******************************************************************************
 * CONSTANTES
 ******************************************************************************/
#define MAX_OBJ 10

//Constantes de logica para las interacciones en el mapa
enum {UNSAFE, SAFE, WIN_FREE, WIN_OCC};
/*******************************************************************************
 * ESTRUCTURAS Y TIPOS DE DATOS
 ******************************************************************************/

typedef struct{
    uint8_t size; //ancho de los objetos en la linea
    int8_t dir; //direccion de los objetos
    int v; //velocidad de los objectos
    uint8_t val_def; //valor default de la linea. 0 es agua y 1 es tierra
    uint8_t cant_obj; //cantidad maxima de objetos que hay cargada en un momento 
    int po[MAX_OBJ]; //arreglo que guarda posicion x mas a la izquierda de los objetos en la linea
} linea_t;

typedef struct worldData
{
    int difficulty;
    int winPosStates[5];
    int timeLeft;
} worldData_t;

/*******************************************************************************
 * PROTOTIPOS DE FUNCIONES
 ******************************************************************************/

/**
 * @brief Inicializa el mapa con las distintas propiedades que deben tener sus lineas
 * @param p Puntero a la primera linea del mapa
 * @param pWorldData puntero a los datos del mundo que inicializara
*/
void createMap(linea_t * p,  worldData_t * pWorldData);

/**
 * @brief Funcion para empezar el juego desde cero
 * @param map puntero al mapa
 * @param pWorldData puntero a estructura world data con la informacion del juego
 */
void gameStart (linea_t * map, worldData_t * pWorldData);

#endif //WORLDDATA_H
