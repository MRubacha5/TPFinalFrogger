#ifndef OBJETOS_H
#define OBJETOS_H



typedef struct {
    int8_t x; //posicion x (desde izquierda)
    uint8_t val; //valor de la linea negada
} objeto_t;



linea_t * CreateWorld(unsigned int h, unsigned int w);
void FreeWorldData(linea_t * pl, unsigned int h);
// void ShiftArr(objeto_t * ppri, objeto_t * pult, objeto_t * pstage ,objeto_t copia);
void CreateObject(linea_t * pl);
// void DestroyObject(linea_t * pl);
void MoveObject(linea_t * pl);
void LoopObject(objeto_t* pobj,linea_t* plinea);
// void ObjectSpawner(unsigned int difficulty, unsigned int size, unsigned int num_cur_obj, linea_t * pl);
#endif //OBJETOS_H
