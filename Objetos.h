#include <stdint.h>
#define IZQ -1
#define DER 1
#define HEIGHT 10
#define WIDTH 10

typedef struct {
    uint8_t size; //ancho
    uint8_t x; //posicion x (desde izquierda)
    uint8_t val; //valor de la linea negada
} objeto_t;

typedef struct{
    uint8_t dir; //direccion de los objetos
    uint8_t v; //velocidad de los objectos
    uint8_t val_def; //valor default de la linea
    uint8_t cant_obj;
    int * p_linea; //puntero a coordenada (0, linea)
    objeto_t * po; //puntero a objetos
} linea_t;