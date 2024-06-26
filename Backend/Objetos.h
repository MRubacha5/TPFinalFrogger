#ifndef OBJETOS_H
#define OBJETOS_H
#include <stdint.h>
#define IZQ -1
#define DER 1
#define HEIGHT 20
#define WIDTH 13

typedef struct {
    int8_t x; //posicion x (desde izquierda)
    uint8_t val; //valor de la linea negada
} objeto_t;

typedef struct{
    uint8_t size; //ancho de los objetos en la linea
    int8_t dir; //direccion de los objetos
    int8_t v; //velocidad de los objectos
    uint8_t val_def; //valor default de la linea. 0 es agua y 1 es tierra
    uint8_t cant_obj; //cantidad maxima de objetos que hay cargada en un momento 
    int * p_linea; //puntero a coordenada (0, linea)
    objeto_t * po; //puntero a objetos
} linea_t;

linea_t * CreateWorld(unsigned int h, unsigned int w);
void FreeWorldData(linea_t * pl, unsigned int h);
void ShiftArr(objeto_t * ppri, objeto_t * pult, objeto_t * pstage ,objeto_t copia);
void CreateObject(linea_t * pl);
void DestroyObject(linea_t * pl);
void MoveObject(linea_t * pl);
void ObjectSpawner(unsigned int difficulty, unsigned int size, unsigned int num_cur_obj, linea_t * pl);
#endif //OBJETOS_H
