
/************************************************************************************************************-
															Score Module
*************************************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "score.h"
#define TOP 10


/****************************************************************************************************/

static int compare_scores (uint16_t mscores[], uint16_t fscore)
{
	int i;
	for (i=10; i>0; i--)
	{
		//printf ("%d  %d\n", fscore, mscores[i-1]);
		if (fscore	<= mscores[i-1])
		{
			break;
		}
	}
	return i; // i = no elemento del array que debe ser fscore en orden decreciente
}


int max_scores (uint16_t fscore, char* filename, char* alias)
//formato del archivo por linea AAA	xxxxx(score)
//Abre el archivo con los maximos puntajes para comparar y agregar el puntaje si esta en el top 10
{ 
	int rank,c,i=0;
	uint16_t mscores [TOP] = {0,0,0,0,0,0,0,0,0,0};
	char plyr_list [TOP][4] = {"   ","   " ,"   ","   ","   ","   ","   " ,"   ","   ","   "};
	FILE * fp;
	fp = fopen(filename,"r+");
	if (fp == NULL)
	{
		return-1;
	} 
	//creo un buffer y voy leyendo los scores de los mejores jugadores
	unsigned int buf [TOP];
	char players [4];
    for (i=0;(fscanf(fp, "%*s %u ", buf) == 1) && (i<TOP); i++) //saltea 1er string (alias) y agarra el score
	{	
		//guardo los valores en el orden leido (mayor a menor) en mscores
		mscores [i] = *buf;
	}
	fseek ( fp,0,SEEK_SET); //vuelvo al comienzo del archivo
	for (i=0;(fscanf(fp, "%s %*s ", players) == 1) && (i<TOP); i++) //saltea 2do string (score) y agarra el alias
	{	
		//guardo los valores en el orden leido (mayor a menor) en plyr_list
		//strtok
		for (c=0; c<4; c++)
		{
			plyr_list[i][c] = players[c];
		}
	}
	rank = compare_scores (mscores, fscore );
	// Devuelve que lugar debe ocupar fscore en el array (0-9) 
	//(si rank =10 -> no entra en el top)

	int_swap_sc (mscores,TOP,rank, fscore);
	str_swap_al (plyr_list,TOP,rank, alias);

	fwr_sc (fp,mscores,TOP,plyr_list); //reimprimo la lista con las modificaciones ya hechas

	fclose(fp);
	return 1;
}





static void int_swap_sc (uint16_t* p2arr,  int nel, int rank, uint16_t fscore)
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
	}
	return;
}





static void str_swap_al (char plr [][4],  int nel, int rank, char* alias)
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





static void fwr_sc (FILE* fp ,uint16_t arr[], int l, char plr [][4])
{
	fseek ( fp,0,SEEK_SET);
	int i;
	for (i=0; i<l-1;i++)
	{
		fprintf(fp,"%s	%05u \n" ,plr [i], arr[i]);

	}
}






uint16_t ct_score (uint8_t y, uint8_t t_time, uint8_t time, uint8_t lines, uint8_t vidas, uint8_t lvlend)
{
	
	static uint16_t score, finalscore;
	
	if (vidas != 0)
	{
		score += in_game_score(y);
		if (lvlend)
		{
			//score += time_bonus(t_time,time, lines);
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





static uint16_t in_game_score (uint8_t y)
{
	
	static uint8_t yMax;
	uint16_t sc;
	
	if (y>yMax) //si la posicion de la rana es mayor a una alcanzada previamente, el puntaje se incrementa
	{
		sc = 10;
		yMax = y;
		//printf ("%u   %u \n", y, yMax);

	}
	else if (y == 0) //solo al principio de cada nivel/vida
	{
		yMax = 0;
	} 
	else sc = 0;

	return sc;
}





static uint16_t time_bonus (uint8_t t_time,uint8_t time, uint8_t lines) //Bonus al ganar un nivel segun cuanto tiempo sobra
{
	uint16_t tb;
			if (time >= t_time / 2)
			{
				tb = lines * 5;
			}
			else if (time >= t_time / 4)
			{
				tb = lines * 3;
			}
			else 
			{
				tb = 0;	
			}
	return tb;
}





int IsMax (uint16_t fscore, char* filename)
{
	int rank,c,i=0;
	uint16_t mscores [TOP] = {0,0,0,0,0,0,0,0,0,0};
	FILE * fp;
	fp = fopen(filename,"r+");
	if (fp == NULL)
	{
		return-1;
	} 
	//creo un buffer y voy leyendo los scores de los mejores jugadores
	unsigned int buf [TOP];
	char players [4];
    for (i=0;(fscanf(fp, "%*s %u ", buf) == 1) && (i<TOP); i++) //saltea 1er string (alias) y agarra el score
	{	
		//guardo los valores en el orden leido (mayor a menor) en mscores
		mscores [i] = *buf;
	}
	fseek ( fp,0,SEEK_SET); //vuelvo al comienzo del archivo
	rank = compare_scores (mscores, fscore );
	if (rank < TOP)
	{
		return 1;
	}
	else 
	{
		return 0;
	}
}

int gameOver (uint16_t fscore, char* filename)
{
	uint16_t score;
	fscore = score;
	int n = IsMax(score, filename);
	return n;
}

