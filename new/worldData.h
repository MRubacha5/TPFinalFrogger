#ifndef WORLDDATA_H
#define WORLDDATA_H

/*******************************************************************************
 * HEADERS
 ******************************************************************************/

#include <stdint.h>

/*******************************************************************************
 * CONSTANTES
 ******************************************************************************/

#define IZQ -1
#define DER 1
#define HEIGHT 16
#define WIDTH 12
#define MAX_OBJ 5

//Constantes de logica para las interacciones en el mapa
#define UNSAFE 0
#define SAFE 1
#define RANA_VAL 2
#define WIN_FREE 3
#define WIN_OCC 4

/*******************************************************************************
 * ESTRUCTURAS Y TIPOS DE DATOS
 ******************************************************************************/

typedef struct{
    uint8_t size; //ancho de los objetos en la linea
    int8_t dir; //direccion de los objetos
    int8_t v; //velocidad de los objectos
    uint8_t val_def; //valor default de la linea. 0 es agua y 1 es tierra
    uint8_t cant_obj; //cantidad maxima de objetos que hay cargada en un momento 
    int po[MAX_OBJ]; //arreglo que guarda posicion x mas a la izquierda de los objetos en la linea
    uint8_t plinea[WIDTH]; //arreglo que contiene los valores de cada posicion en el mapa (1 si la rana puede estar en ellos, 0 si no y 2 si es un lilypad)
} linea_t;

/*******************************************************************************
 * PROTOTIPOS DE FUNCIONES
 ******************************************************************************/

/**
 * @brief Inicializa el mapa con las distintas propiedades que deben tener sus lineas
 * @param p Puntero a la primera linea del mapa
 * @param difficulty Entero que determina la dificultad. Modifica algunos parametros en la generacion
*/
void createMap(linea_t * p, int difficulty);

/**
 * @brief Se ocupa de mover todos los objetos en el mundo. NO TIENE EN CUENTA LA VELOCIDAD Y DEBERA SER LLAMADA ACORDEMENTE
 * @param plinea Puntero a la linea en cuestion
*/
void moveLine(linea_t * plinea);

#endif //WORLDDATA_H
