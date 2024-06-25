/**************************************************************************************** 
Creo el mundo. Uso dimeniones fijas y creo matriz. Cada linea es un struct con informacion
como la direccion del movimiento, la velocidad de los objetos, el valor default del terreno
****************************************************************************************/

#include "Objetos.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

/*
int main(void)
{
    linea_t *pl = CreateWorld(HEIGHT, WIDTH);

    for (int i = 0; i < 10; i++)
    {
        for (int c = 0; c < 10; c++)
        {
            printf("%d\t", *(((pl + i)->p_linea) + c));
        }
        printf("\n");
    }

    FreeWorldData(pl, HEIGHT);

    return 1;
}
*/

linea_t * CreateWorld(unsigned int h, unsigned int w){
    linea_t * pl = (linea_t *)malloc(h*sizeof(linea_t));
    int i, c;
    srand(time(NULL));
    for(i = 0 ; i < h ; i++){
        linea_t * linea_actual = pl+i;
        linea_actual->dir = (rand()%2) ? DER : IZQ;
        linea_actual->v = 1; //a cambiar despues, variar segun delays por procesadores (movimiento por segundo y ajustar)

        if(i <= (h/2)){
            linea_actual->val_def = 1; // se puede caminar
        }
        else{
            linea_actual->val_def = 0;
        }

        linea_actual->p_linea = (int *)malloc(sizeof(int) * w); //creo las celdas en x y las poblo con le val def
        int * px = linea_actual->p_linea;
        for(c = 0 ; c < w ; c++){
            *(px+c) = linea_actual->val_def;
        }

        linea_actual->cant_obj = 0;
        linea_actual->po = (objeto_t *)malloc(sizeof(objeto_t));
    }

    return pl;
}

//libero memoria
void FreeWorldData(linea_t * pl, unsigned int h){
    int i;
    for(i = 0 ; i < h ; i++){
        free((pl+i)->p_linea);
        free((pl+i)->po);
    }
    free(pl);
}

//funcion crear instancia de objeto
void CreateObject(linea_t * pl){
    objeto_t * po = pl->po;
    int s = pl->cant_obj;
    (po+s)->size = 1; //modificar para distintos tipo (switch?)
    (po+s)->val = !(pl->val_def);
    (po+s)->x = (pl->dir == DER ? 0 : WIDTH-1); // si direccion es derecha arranca en 0 si no al final
    (pl->cant_obj)++;
    pl->po = realloc(po, (pl->cant_obj)+1);
}

//funcion destroyobjects --> hace falta un flip array por si cambia la direccion del movimiento
void DestroyObject(linea_t * pl){
    ShiftArr((pl->cant_obj)+1, pl->po);
    objeto_t * po = pl->po;
    pl->po = realloc(po, (pl->cant_obj));
    (pl->cant_obj)--;
}

//funcion mover objetos, uso threads?
void MoveObject(linea_t * pl){
    if(pl->cant_obj > 0){
        int cobjs = pl->cant_obj;
        int vel = pl->v;
        int dir = pl->dir;
        int i, c;
        for (i = 0; i < WIDTH; i++)
        {
            *((pl->p_linea) + i) = pl->val_def;
        }
        for (i = 0; i < cobjs; i++)
        {
            ((pl->po) + i)->x += vel * dir;

            for (c = 0; i < pl->po->size; i++)
            {
                *((pl->p_linea) + (((pl->po) + i)->x) + c) = !(pl->val_def);
            }
        }
    }
}


void ShiftArr (int len, objeto_t* p2obj)
{
	
	objeto_t temp;
	
	if (len = 1)
	{
		return;
	}
	else
	{
		temp = *p2obj;
		*p2obj = *(p2obj+1);
		*(p2obj+1) = temp;
		ShiftArr (len-1, p2obj+1);
	}	
	return;
}

//en el agua siempre tiene que haber algo para pasar, no siempre random