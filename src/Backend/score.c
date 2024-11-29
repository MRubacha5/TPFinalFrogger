
/************************************************************************************************************-
															Score Module
*************************************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "score.h"
#define TOP 10

//variables globales (son multiarchivo)
uint16_t currentScore = 0;
char topNames [10] [4] = {"XXX","XXX" ,"XXX","XXX","XXX","XXX","XXX" ,"XXX","XXX","XXX"};
uint16_t topScores [10] = {0,0,0,0,0,0,0,0,0,0};
char scorestr [6];
char highscorestr [6];
char name [4] = {"AAA"};
/****************************************************************************************************/

static uint16_t time_bonus (unsigned int timeleft); //calcula el bonus

static uint16_t in_game_score (uint8_t y, uint8_t reset); //lleva el puntaje durante cada vida/nivel

static void fwr_sc (FILE* fp , int l);

static int compare_scores (uint16_t fscore); //devuelve posicion en el ranking

static void int_swap_sc (uint16_t* p2arr, int rank, uint16_t fscore);

static void str_swap_al (char plr [][4], int rank, char* alias);

/*************************************************************************************************** */


uint16_t ct_score (uint8_t y, unsigned int timeleft, uint8_t vidas, uint8_t lvlend, uint8_t reset)
{
	
	static uint16_t score, finalscore;
	score = currentScore;
	
	if (vidas != 0)
	{
		score += in_game_score(y, reset);
		if (lvlend)
		{
			score += time_bonus(timeleft);
		}
	}
	else 
	{
		finalscore = score;
		score = 0;
		return finalscore;
	}
	
	return score;
	
}



static uint16_t in_game_score (uint8_t y, uint8_t reset)
{
	
	static uint8_t yMax;
	uint16_t sc = 0;
	

	if (reset) //solo al principio de cada nivel/vida
	{
		yMax = 0;
	} 
	else if ( y > yMax) //si la posicion de la rana es mayor a una alcanzada previamente, el puntaje se incrementa
	{
		sc = 10;
		yMax = y;
	}
	else sc = 0;

	return sc;
}



static uint16_t time_bonus (unsigned int timeleft) //Bonus al ganar un nivel segun cuanto tiempo sobra
{
	uint16_t tb;
	int bonusMultiplier = 5;
	tb = bonusMultiplier * timeleft;
	return tb;
}



int max_scores (uint16_t fscore, char* filename, char* alias)
{ 
	int rank;

	FILE * fp;
	fp = fopen(filename,"r+");
	if (fp == NULL)
	{
		return-1;
	} 
	//obtengo del archivo score.txt los puntajes maximos y los nombres
	getTopScores (filename);
	
	// Devuelve que lugar debe ocupar fscore en el array (0-9) 
	//(si rank =10 -> no entra en el top)
	rank = compare_scores (fscore );

	int_swap_sc (topScores,rank, fscore);
	str_swap_al (topNames,rank, alias);
	fwr_sc (fp,TOP); //reimprimo la lista con las modificaciones ya hechas

	fclose(fp);
	return 1;
}



int IsMax (uint16_t fscore, char* filename)
{
	getTopScores (filename);
	int rank = compare_scores (fscore);
	if (rank < TOP)
	{
		return 1;
	}
	else 
	{
		return 0;
	}
}



static int compare_scores (uint16_t fscore)
{
	int i;
	for (i=10; i>0; i--)
	{
		if (fscore	<= topScores[i-1])
		{
			break;
		}
	}
	return i; // i = no elemento del array que debe ser fscore en orden decreciente
}



static void fwr_sc (FILE* fp, int l)
{
	fseek ( fp,0,SEEK_SET);
	int i;
	for (i=0; i<l;i++)
	{
		fprintf(fp,"%s %05d\n", topNames[i], topScores[i]);

	}
}



static void int_swap_sc (uint16_t* p2arr, int rank, uint16_t fscore)
{
	//printf("entro\n");
	uint16_t tempa;
	int n, i;
	if (rank < 10)
	{
		p2arr [9] = fscore;
		for (i=9, n=rank ; n<9; n++ ,i-- )
		{
			tempa=p2arr[i-1];
			p2arr[i-1] = p2arr[i];
			p2arr[i] = tempa;
		}
		//printf ("%d \n",p2arr[9]);
	}
	return;
}



static void str_swap_al (char plr [][4], int rank, char* alias)
{
	char temp [4];
	int n,i;
	if (rank < 10)
	{
		strcpy(plr[9],alias);
		for (i=9, n=rank ; n<9; n++ ,i-- )
		{
			strcpy(temp,plr[i-1]);
			strcpy(plr[i-1],plr[i]);
			strcpy(plr[i] , temp);
		}
	}
	return;
}


void intToChar (int strLong, char* str, uint16_t score)
{
    // Verificar que el tamaño del buffer sea adecuado
    if (strLong < 6) { // 5 dígitos + '\0'
        str[0] = '\0';  // Si el buffer es muy pequeño, retornar cadena vacía
        return;
    }
    // Convertir el número a string
    snprintf(str, strLong, "%05u" , score);
	return;
}

int getTopScores (char* filename)
{
	int i , c;
	FILE * fp;
	fp = fopen(filename,"r+");
	if (fp == NULL)
	{
		printf ("Error: Exit Code -1");
		return-1;
	} 
	//creo un buffer y voy leyendo los scores de los mejores jugadores
	unsigned int buf [TOP];
	char players [4];
    for (i=0;(fscanf(fp, "%*s %u ", buf) == 1) && (i<TOP); i++) //saltea 1er string (alias) y agarra el score
	{	
		//guardo los valores en el orden leido (mayor a menor) en mscores
		topScores [i] = *buf;
	}
	fseek ( fp,0,SEEK_SET); //vuelvo al comienzo del archivo
	for (i=0;(fscanf(fp, "%s %*s ", players) == 1) && (i<TOP); i++) //saltea 2do string (score) y agarra el alias
	{	
		//guardo los valores en el orden leido (mayor a menor) en plyr_list
		//strtok
		for (c=0; c<4; c++)
		{
			topNames[i][c] = players[c];
		}
	}	
	fclose(fp);
	return 1;
}
