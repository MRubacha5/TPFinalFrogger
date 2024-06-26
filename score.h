#ifndef SCORE_H 
#define SCORE_H
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

uint16_t ct_score (uint8_t y,uint8_t t_time, uint8_t time, uint8_t lines, uint8_t vidas, uint8_t lvlend);
// pos y , Tiempo total nivel, tiempo sobrante, cant de lineas nivel, vidas, lvlend(valor booleano)
// lleva la cuanta del puntaje, se actualiza cada vez que el jugador avanza en el eje y


int max_scores (uint16_t fscore, char* filename,  char* alias); 
//corrobora al final del juego si el jugador esta en el top 10
//si lo esta,lo agrega en una lista en filename
//formato de filename:
/*
TAG  SCORE      (TAG ocupa 3 caracteres, luego se ponen 2 espacios y luego SCORE con 5 pos. decimales)
EJEMPLO:

YYY  16800
XXX  15700
ZZZ  08600
...  00000
...  00000
...  00000
...  00000
*/

#endif//SCORE_H