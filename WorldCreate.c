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
        
        if(i <= (h/2)){ //agua
            linea_actual->v = (rand()%3 + 1);
            linea_actual->val_def = 0;
            linea_actual->size = rand()%3+1;
        }
        else{ //cemento
            linea_actual->v = (rand()%2 + 1);
            linea_actual->val_def = 1;
            linea_actual->size = rand()%2+1;
        }

        linea_actual->p_linea = (int *)malloc(sizeof(int) * w); //creo las celdas en x y las poblo con le val def
        if(linea_actual->p_linea == NULL){
            return NULL;
        }
        int * px = linea_actual->p_linea;
        for(c = 0 ; c < w ; c++){
            *(px+c) = linea_actual->val_def;
        }

        linea_actual->cant_obj = 0;
        linea_actual->po = (objeto_t *)malloc(sizeof(objeto_t));
        if(linea_actual->po == NULL){
            return NULL;
        }
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
    printf("segment reached");
}

//funcion crear instancia de objeto
void CreateObject(linea_t * pl){
    objeto_t * po = pl->po;
    int s = pl->cant_obj;
    (po+s)->val = !(pl->val_def);
    (po+s)->x = (pl->dir == DER ? 1-pl->size : WIDTH-1); // si direccion es derecha arranca en 0 si no al final
    printf("X: %d\n",(po+s)->x);
    (pl->cant_obj)++;
    pl->po = realloc(po, (pl->cant_obj)+1);
    if(pl->po == NULL){
        printf("ERROR WITH REALLOC");
    }
    
}

//funcion destroyobjects --> hace falta un flip array por si cambia la direccion del movimiento
void DestroyObject(linea_t * pl){
    ShiftArr(pl->po, (pl->po)+(pl->cant_obj), (pl->po)+(pl->cant_obj), *((pl->po)+(pl->cant_obj)));
    objeto_t * po = pl->po;
    pl->po = realloc(po, (pl->cant_obj));
    if(pl->po == NULL){
        printf("ERROR CON REALLOC EN DESTROY");
    }
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

            for (c = 0; c < pl->size; c++)
            {
                *((pl->p_linea) + (((pl->po) + i)->x) + c) = !(pl->val_def);
            }
        }
    }
}

void ObjectSpawner(unsigned int spawn_chance, unsigned int size, unsigned int num_cur_obj, linea_t * pl){
    static int spawned = 0;
    static int timeBuffer = 0;
    if(spawned == 0 && num_cur_obj < 4){

        if (rand()%spawn_chance == 0){
            CreateObject(pl);
        }
        spawned = 1;
    }
    else if (spawned == 1) {
        if (timeBuffer <= size){
            timeBuffer++;
        }
        else {
            timeBuffer = 0;
            spawned = 0;
        }
    }
}

void ShiftArr(objeto_t * ppri, objeto_t * pult, objeto_t * pstage ,objeto_t copia){
    if(ppri == pstage){
        *pult = copia;
        return;
    }
    else {
        objeto_t temp = *(pstage-1);
        *(pstage-1) = copia;
        ShiftArr(ppri, pult, pstage-1, temp);
        return;
    }
}


//en el agua siempre tiene que haber algo para pasar, no siempre random
