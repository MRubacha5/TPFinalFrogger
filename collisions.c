#include "Rana.h"
#include "Objetos.h"
#include <stdio.h>

/***************************************************************************************************************************************************
* Esta funcion revisa la colision de la rana que recibe en todas las lineas contenidas en el arreglo que recibe mediante el puntero a lineas world.*
* De ser necesario, llama a las funcioes que matan a la rana.                                                                                      *
* Devuelve un puntero al objeto con el que colisiono la rana. Si no colisiono con ningun objeto, devuelve NULL                                     *
***************************************************************************************************************************************************/
objeto_t* Collisions(rana_t* prana, linea_t* world){
    linea_t* linea_actual = world+(prana->posy);//Linea en la que se encuentra la rana 
    int i,j;
    int col_val= linea_actual->val_def; //inicializo la colision como el valor default de la linea 
    objeto_t* col_obj=NULL;
    for(i = 0; i < linea_actual->cant_obj; i++){ //recorro los objetos en la linea
        for(j = 0 ; j<linea_actual->size;j++){ //recorro las posiciones x de los objetos

            if( ((linea_actual->po+i)->x+j) == (prana->posx)){ //si colisiono con algo
                col_val = (linea_actual->po)[i].val;//anoto el valor del objeto para saber si mata a la rana
                col_obj = linea_actual->po+i;//guardo un puntero al objeto para devolver
            }
        }
    }
    if(col_val){
        RestarVidas(prana);
        //cualquier otra funcion que se deba llamar cuando la rana muere
    }
    if(col_obj->val && !(linea_actual->val_def)){//Si el objeto esta flotando en el agua
        // ENCONTRAR ALGUNA FORMA DE HACER QUE SI EL OBJETO SE MUEVE QUE LA RANA SE MUEVA TAMBIEN SIN FIJAR LA RANA AL LUGAR EN EL QUE COLISIONO
        //PROBABLEMENTE NECESITE USAR FREDS
    }
    return col_obj;
}
