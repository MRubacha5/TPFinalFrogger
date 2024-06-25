#include "Rana.h"
#include "Objetos.h"
#include <time.h>

int Collisions(rana_t rana, linea_t * pl){
    linea_t * linea_actual = pl+rana.posy; // linea actual se marca como la linea de la rana

    int * plinea = linea_actual->p_linea; //accede al puntero de las posiciones de la linea

    int col_val=0; //inicializo la colision como que no colisiona con nada

    for(int i = 0; i < pl->cant_obj; i++){ //recorro los objetos en la linea
        for(int j = 0 ; j<(pl->po+i)->size;j++){ //recorro las posiciones x de los objetos

            if( ((pl->po+i)->x+j) == rana.posx){ //si la posicion x de la rana es igual a la de algun objeto
                col_val = (pl->po)[i].val;

            }
        }
    }
    return col_val;
}
