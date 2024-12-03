#ifndef SCORE_H 
#define SCORE_H

/*******************************************************************************
 * HEADERS
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

/***********************************************************************************
 * GLOBAL SCORE VARIABLES
********************************************************************************** */

extern uint32_t currentScore;
extern char topNames[10][4];
extern uint32_t topScores[10];
extern char scorestr [6];
extern char highscorestr [6];
extern char name [4]; 

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

/*******************************************************************************
 * PROTOTIPOS DE FUNCIONES
 ******************************************************************************/


/**
* @brief Lleva la cuenta del puntaje. Se actualiza cada vez que el jugador avanza en el eje y
* @param y la posicion en y 
* @param timeleft tiempo sobrante 
* @param vidas cantidad de vidas restantes
* @param lvlend valor booleano que describe el estado del nivel
* @param reset indica si se volvio al comienzo por muerte 
* @return el puntaje
*/
uint32_t ct_score (uint8_t y, unsigned int timeleft, uint8_t vidas, uint8_t lvlend, uint8_t reset);



/**
* @brief Se ocupa de registrar un puntaje dentro del top 10 si es que este califica
* @param fscore 
* @param filename
* @param alias
* @return 
*/
int max_scores (uint32_t fscore, char* filename,  char* alias); 



/**
*
	@brief Returns 1 if fscore is on TOP 10 and 0 if it isnt
	@param fscore id the final score
	@param filename TOPSCORESLIST 
	@return boolean value indicating whether the score is top 10 or not
*/
int IsMax (uint32_t fscore, char* filename);



void intToChar (int strLong, char* str, uint32_t score);



int getTopScores (char* filename);

#endif //SCORE_H
