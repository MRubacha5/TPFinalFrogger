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
    int8_t v; //velocidad de los objectos
    uint8_t val_def; //valor default de la linea. 0 es agua y 1 es tierra
    uint8_t cant_obj; //cantidad maxima de objetos que hay cargada en un momento 
    int po[MAX_OBJ]; //arreglo que guarda posicion x mas a la izquierda de los objetos en la linea
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

#endif //WORLDDATA_H
