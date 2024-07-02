#include "Rana.h"
#include "Objetos.h"
#include <stdio.h>

/************************************************************************************************
 * WorldInteract: Todas las funciones que se ocupan de que el mundo funcione de forma constante. 
 * WorldCreate es como el void setup() y WorldInteract es como el void loop().
*************************************************************************************************/

/***************************************************************************************************************************************************
 Esta funcion revisa la colision de la rana que recibe en todas las lineas contenidas en el arreglo que recibe mediante el puntero a lineas world.
 De ser necesario, llama a las funciones que matan a la rana.                                                                                     
 Devuelve un puntero al objeto con el que colisiono la rana. Si no colisiono con ningun objeto, devuelve NULL.
 Tambien se encarga de que, si la rana esta sobre un objeto flotando en el agua, moverlos en conjunto.                                    
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
       MoveRana(prana,linea_actual->dir,world);
    }
    return col_obj;
}

/********************************************************************************************************************
    Funcion mover objetos: Recibe la linea en la que debe mover los objetos y los mueve 
    como valores booleanos (negando el valor del terreno donde estan) a lo largo de la linea.
    Se encarga de llamar a LoopObject para asegurarse que los objetos regresen a la pantalla una vez que se fueron.
*********************************************************************************************************************/
void MoveObject(linea_t * pl){
    if(pl->cant_obj > 0){
        int cobjs = pl->cant_obj; 
        int vel = pl->v;
        int dir = pl->dir;
        int i, c;
        for (i = 0; i < WIDTH; i++)// recorro la linea
        {
            *((pl->p_linea) + i) = pl->val_def; // asigno valor default (1 para tierra y 0 para agua)
        }    
        for (i = 0 ; i < cobjs ; i++)// recorro la cantidad de objetos en la linea
        {
            ((pl->po) + i)->x += dir; //los muevo en su direccion correspondiente (***FALTA AGREGAR MULTIPLICADOR DE VELOCIDAD***)

            switch (dir) // Analizo si se fueron del tablero para llamar a LoopObject. Solo llamo si el objeto entero ya salio de la pantalla
            {
            case DER:
                printf(" AVANZA DER");
                if(((pl->po)+i)->x > WIDTH){
                    
                    LoopObject((pl->po)+i, pl);
                }
                break;
            case IZQ:
                printf(" AVANZA IZQ");
                if((((pl->po)+i)->x) + ((pl)->size) - 1 < 0){
                    
                    LoopObject((pl->po)+i, pl);
                }
                break;
            }

            for (c = 0; c < pl->size; c++)// itero por el ancho del objeto
            {
                int temp = pl->po->x;
                *((pl->p_linea) + (((pl->po) + i)->x) + c) = !(pl->val_def);// muevo los valores booleanos del objeto a la nueva posicion x
                pl->po->x=temp;
            }

        }
    }
}

/*********************************************************************************************************
    LoopObject: Recibe puntero al objeto y puntero a la linea del objeto para las propiedades del mismo. 
    Se le puede agregar un offset random para modificar el spacing entre cada looping.
**********************************************************************************************************/

void LoopObject (objeto_t* pobj, linea_t* plinea){
    switch(plinea->dir){ //En base a la direccion de movimiento decido donde mover el x del objeto 
        case(DER):
            pobj->x = 1- plinea->size; //Reinicio el objeto del lado izquierdo
            break;
        case(IZQ):
            pobj->x = WIDTH;//Reinicio el objeto del lado derecho 
        break;
    }
    return;
}

