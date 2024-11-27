#ifndef RASPI_DATA_H
#define RASPI_DATA_H

#include <stdio.h>
#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

#include "disdrv.h"
#include "joydrv.h"
#include "../src/Backend/worldData.h"
#include "../src/Backend/score.h"
#include "../src/Backend/rana.h"
#include "../src/Backend/movement.h"
#include "../src/Backend/platformConfig.h"

#define THRESHOLD 40

enum {MENU, GAME, PAUSE, GAMEOVER, HISCORE};

#define LIVES_ANIMATION 3 * FPS
#define LEVEL_ANIMATION 3 * FPS

/***************************JOYSTICK HANDLER*********************************** */
typedef struct joystick{
    dcoord_t pos;	
	joyinfo_t coord;					
    int joyMoved;
    int joyValue;
    int joyPressed;
    int isMoving;
}   joystick_t;

/*******************************JOYSTICK INIT******************************** */

/**
 * @brief Returns and initializes the joystick variables and settings
 */
joystick_t joystickInit(void);

/**
 * @brief updates the joystick variables with the inputs
 * @param handler ptr to the struct with variables
 */
void joystickUpdate(joystick_t * handler)
/**************************************************************************** */

/********************************TIMER HANDLER******************************* */
typedef struct time{
    clock_t before; 
    clock_t difference;
    clock_t lap_time;
    int msec ;
    int fpsCounter;
} timer_t;
/********************************TIMER INIT*********************************** */

/**
 * @brief Returns and initializes the timer variables and settings
 */
timer_t timeInit(void);

/**
 * @brief updates the timer variables
 * @param handler ptr to the struct with variables
 */
void timerUpdate(timer_t * handler);
/***************************************************************************** */

/**********************************SCREEN MANAGER**************************** */
typedef struct screenHandler{
    int screen;
    int do_exit;
    int optionSelected;
} screenHandler_t;

typedef struct gameOverHandler{
    int charSelection[3];
} gameOverHandler_t;

typedef struct hiscoreHandler{
    int charToWrite;
    int intToWrite;
} hiscoreHandler_t;
/*****************************SCREENS INIT AND RESETS**************************** */

/**
 * @brief Initializes the screen variables
 * @param screenHandler ptr to the general screen variable struct
 * @param gameOverHandler ptr to the gameover screen varaible struct
 * @param hiscoreHandler ptr to the hiscore screen variable struct
 */
void screensInit(screenHandler_t * screenHandler, gameOverHandler_t * gameOverHandler, hiscoreHandler_t * hiscoreHandler);

/**
 * @brief Initializes the Menu screen variables
 * @param screenHandler ptr to the general screen variable struct
 */
void mainMenuInit(screenHandler_t * screenHandler);

/**
 * @brief Initializes the game over screen variables
 * @param screenHandler ptr to the general screen variable struct
 * @param gameOverHandler ptr to the gameover screen varaible struct
 */
void gameOverInit(screenHandler_t * screenHandler, gameOverHandler_t * gameOverHandler);

/**
 * @brief Initializes the hiscore screen variables
 * @param screenHandler ptr to the general screen variable struct
 * @param hiscoreHandler ptr to the hiscore screen variable struct
 */
void hiscoreInit(screenHandler_t * screenHandler, hiscoreHandler_t * hiscoreHandler);
/********************************************************************************** */

/******************************************SOUND*************************************** */
typedef struct soundHandler{
    Mix_Chunk *sound_drown;
    Mix_Chunk *sound_squash;
    Mix_Chunk *sound_hop;
    Mix_Chunk *sound_timer;
} soundHandler_t;
/*******************************************INIT************************************ */
soundHandler_t soundInit(void);
/*********************************************************************************** */

/******************************************SCREENS*********************************** */
extern int mainMenu[16][16];
extern int pauseMenu[16][16];
extern int livesAnimation1[16][16];
extern int livesAnimation2[16][16];
extern int livesAnimation3[16][16];
extern int levelAnimation[16][16];
extern int letters[26][5][3];
extern int numbers[10][5][3];
/************************************************************************************ */

/*************************************ANIMATIONS************************************* */
typedef struct animationHandler{
    int ranaColor;
    int ranaColorTimer;
    dcoord_t timerCoord;
    int livesAnimationCounter;
    int levelAnimationCounter;
} animationsHandler_t;
/**************************************ANIMATION INIT********************************* */

/**
 * @brief Returns and initializes the animation variables and settings
 */
animationHandler_t animationInit(void);
/************************************************************************************ */


/***************************************MAIN MENU************************************* */
void mainMenu(screenHandler_t * screenHandler, joystick_t * joystickHandler, rana_t * prana, worldData_t * worldData, linea_t * map);
/***************************************PAUSE***************************************** */
void pause(screenHandler_t * screenHandler, joystick_t * joystickHandler);
/*****************************************GAME******************************************** */
void inGame(linea_t * map, rana_t * pRana, worldData_t * worldData, screenHandler_t * screenHandler, joystick_t * joystickHandler, animationsHandler_t * animationHandler, timer_t * timeHandler, soundHandler_t * soundHandler, gameOverHandler_t * gameOverHandler);
/*******************************************GAMEOVER************************************** */
void gameover(joystick_t * joystickHandler, gameOverHandler_t * gameOverHandler, screenHandler_t * screenHandler, hiscoreHandler_t * hiscoreHandler);
/*******************************************HISCORE**************************************** */
void hiscoreScreen(joystick_t * joystickHandler, screenHandler_t * screenHandler, hiscoreHandler_t * hiscoreHandler);
/******************************************************************************************* */


/********************************************DESTRUCTOR************************************ */
void destroyEverything(soundHandler_t * soundHandler);

#endif //RASPI_DATA_H