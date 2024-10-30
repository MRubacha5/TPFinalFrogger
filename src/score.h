#ifndef SCORE_H 
#define SCORE_H

/*******************************************************************************
 * HEADERS
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

/*******************************************************************************
 * PROTOTIPOS DE FUNCIONES
 ******************************************************************************/
/**
* @brief Lleva la cuenta del puntaje. Se actualiza cada vez que el jugador avanza en el eje y
* @param y la posicion en y 
* @param t_time tiempo total del nivel 
* @param time tiempo sobrante 
* @param lines cantidad de lineas en el nivel
* @param vidas cantidad de vidas restantes
* @param lvlend valor booleano que describe el estado del nivel
* @return el puntaje
*/
uint16_t ct_score (uint8_t y,unsigned int timeleft, uint8_t lines, uint8_t vidas, uint8_t lvlend);

/**
* @brief Se ocupa de registrar un puntaje dentro del top 10 si es que este califica
* @param fscore 
* @param filename
* @param alias
* @return 
*/
int max_scores (uint16_t fscore, char* filename,  char* alias); 

/**
*
	@brief Returns 1 if fscore is on TOP 10 and 0 if it isnt
	@param fscore id the final score
	@param filename TOPSCORESLIST 
*/


/**
* 
    @brief Calculates final Score and returns 1 if 
*/
int gameOver (uint16_t fscore, char* filename);

/*******************************************************************************
 * FORMATO DEL FILENAME
 ******************************************************************************/

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


int IsMax (uint16_t fscore, char* filename);

void intToChar (int strLong, char* str, uint16_t score);

int getTopScores (char* filename);

#endif //SCORE_H
