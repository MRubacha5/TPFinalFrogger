#include "Rana.h"
#include "Objetos.h"
#include <time.h>

void Collisions(rana_t rana, linea_t * pl){
    while(1){
        linea_t * linea_actual = pl+rana.posy; // linea actual se marca como la linea de la rana
        int * plinea = linea_actual->p_linea; //accede al puntero de las posiciones de la linea
        if(!plinea[rana.posx]){ // Si la rana esta en una casilla de valor cero (agua, auto, o cualquier cosa que la mate)
            RestarVidas(rana);
        }
    }
}