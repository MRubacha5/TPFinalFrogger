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
#define WIDTH 10
#define MAX_OBJ 5

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

#endif //WORLDDATA_H