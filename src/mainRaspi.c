/*
testlibraries es un ejemplo de uso de las librerías disdrv y joydrv
Permite mover con el joystick un LED encendido en la matriz de LEDs
*/
//Como compilar: gcc testLibraries.c disdrv.o joydrv.o -Wall -o testLibs
#include <stdio.h>
#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

#include "disdrv.h"
#include "joydrv.h"
#include "worldData.h"
#include "score.h"
#include "rana.h"
#include "movement.h"
#include "platformConfig.h"

#define FPS 60
#define THRESHOLD 40	//Límite a partir del cual se mueve el LED encendido
#define MENU 0
#define GAME 1
#define PAUSE 2
#define LIVES_ANIMATION 3 * FPS
#define LEVEL_ANIMATION 3 * FPS

int mainMenu[16][16] = {{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                        {0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                        {0,1,0,0,0,1,0,1,0,1,1,0,1,0,1,0},
                        {0,1,1,1,0,1,0,1,1,1,1,1,1,0,1,0},
                        {0,0,0,1,0,1,0,1,0,1,1,1,0,0,1,0},
                        {0,1,1,1,0,1,0,1,0,1,1,0,1,0,1,0},
                        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                        {0,1,1,1,0,1,0,1,0,1,1,1,0,1,1,1},
                        {0,1,0,1,0,1,0,1,0,0,1,0,0,0,1,0},
                        {0,1,1,1,0,1,0,1,0,0,1,0,0,0,1,0},
                        {0,0,0,1,0,1,0,1,0,0,1,0,0,0,1,0},
                        {0,0,0,1,0,1,1,1,0,1,1,1,0,0,1,0},
                        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}};

int pauseMenu[16][16]= {{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                        {0,1,1,1,0,1,0,0,0,1,1,1,0,1,0,1},
                        {0,1,0,1,0,1,0,0,0,1,0,1,0,1,0,1},
                        {0,1,1,1,0,1,0,0,0,1,1,1,0,0,1,0},
                        {0,1,0,0,0,1,0,0,0,1,0,1,0,0,1,0},
                        {0,1,0,0,0,1,1,1,0,1,0,1,0,0,1,0},
                        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                        {0,1,0,1,0,1,1,1,0,1,1,1,0,1,0,1},
                        {0,1,1,1,0,1,0,0,0,1,0,1,0,1,0,1},
                        {0,1,0,1,0,1,1,0,0,1,0,1,0,1,0,1},
                        {0,1,0,1,0,1,0,0,0,1,0,1,0,1,0,1},
                        {0,1,0,1,0,1,1,1,0,1,0,1,0,1,1,1},
                        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}};

int livesAnimation1[16][16] = {{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                {0,0,0,1,1,1,1,0,0,1,1,1,1,0,0,0},
                                {0,0,1,0,0,0,0,1,1,0,0,0,0,1,0,0},
                                {0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
                                {0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
                                {0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
                                {0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
                                {0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0},
                                {0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0},
                                {0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0},
                                {0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0},
                                {0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0},
                                {0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0},
                                {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}};
                                
                                    
int livesAnimation2[16][16] =  {{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                {0,0,1,1,0,1,1,0,0,0,0,0,0,0,0,0},
                                {0,1,0,0,1,0,0,1,0,0,0,0,0,0,0,0},
                                {0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0},
                                {0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0},
                                {0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0},
                                {0,0,0,0,1,0,0,1,1,1,0,0,1,1,1,0},
                                {0,0,0,0,0,0,1,0,0,0,1,1,0,0,0,1},
                                {0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1},
                                {0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1},
                                {0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0},
                                {0,0,0,0,0,0,0,0,1,0,0,0,0,1,0,0},
                                {0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0},
                                {0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0},
                                {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}};

int livesAnimation3[16][16] =  {{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                {0,0,1,1,0,1,1,0,0,1,1,0,1,1,0,0},
                                {0,1,0,0,1,0,0,1,1,0,0,1,0,0,1,0},
                                {0,1,0,0,0,0,0,1,1,0,0,0,0,0,1,0},
                                {0,0,1,0,0,0,1,0,0,1,0,0,0,1,0,0},
                                {0,0,0,1,0,1,0,0,0,0,1,0,1,0,0,0},
                                {0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0},
                                {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                {0,0,0,0,1,1,1,0,0,1,1,1,0,0,0,0},
                                {0,0,0,1,0,0,0,1,1,0,0,0,1,0,0,0},
                                {0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0},
                                {0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0},
                                {0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0},
                                {0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0},
                                {0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0},
                                {0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0}};

int levelAnimation[16][16] =   {{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                {0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0},
                                {0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0},
                                {0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0},
                                {0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0},
                                {0,0,1,1,1,1,0,0,0,0,1,1,1,1,0,0},
                                {0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
                                {0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
                                {0,0,1,1,1,0,0,0,0,0,0,0,1,1,0,0},
                                {0,0,0,0,0,1,0,0,0,0,1,1,0,0,0,0},
                                {0,0,0,0,1,1,0,1,1,0,1,0,0,0,0,0},
                                {0,0,0,1,1,0,1,0,1,0,0,1,0,0,0,0},
                                {0,0,1,1,0,0,1,0,1,0,0,0,1,0,0,0},
                                {0,0,1,0,0,1,0,0,0,1,1,0,1,0,0,0},
                                {0,0,0,1,1,0,0,0,0,0,0,1,0,0,0,0},
                                {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}};

unsigned int timeLeft = START_TIME; // valor en segundos 

int main(void)
{
    clock_t before = clock(); //agarro tiempo antes de arrancar
    clock_t difference = 0;
    clock_t ini = clock();
    clock_t lap_time;
    int msec = 0;
    rana_t rana;
    rana_t * pRana = &rana;
    linea_t map[HEIGHT];
	
	joy_init();										//inicializa el joystick
	disp_init();									//inicializa el display
	disp_clear();									//limpia todo el display
	dcoord_t pos = {DISP_MAX_X>>1 , DISP_MAX_Y>>1};	//pos es la posición actual, empieza en el centro de la matriz
	joyinfo_t coord = {0,0,J_NOPRESS};							//coordenadas medidas del joystick

    int fpsCounter = 0;
    int screen = MENU;

    int joyMoved = 0;
    int joyValue = -1;
    int joyPressed = 0;
    int isMoving = 0;

    int ranaColor = 0;
    int ranaColorTimer = 0;

    int optionSelected = 0;

    int do_exit = 0;

    dcoord_t timerCoord;

    extern int winPosStates[5];
    extern int vidas;
    extern int currentScore;

    unsigned int difficulty;

    int livesAnimationCounter = 0;
    int levelAnimationCounter = 0;

    SDL_Init(SDL_INIT_AUDIO);

    Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);

    Mix_Chunk *sound_drown = Mix_LoadWAV("../assets/Audio/sound-frogger-drown.wav");
    Mix_Chunk *sound_squash = Mix_LoadWAV("../assets/Audio/sound-frogger-squash.wav");
    Mix_Chunk *sound_hop = Mix_LoadWAV("../assets/Audio/sound-frogger-hop.wav");
    Mix_Chunk *sound_timer = Mix_LoadWAV("../assets/Audio/sound-frogger-time-running-out.wav");

    if(sound_drown == NULL){
        printf("%s\n", Mix_GetError());
    }
    if(sound_squash == NULL){
        printf("error loading squash\n");
    }
    if(sound_hop == NULL){
        printf("%s\n", Mix_GetError());
    }
    if(sound_timer == NULL){
        printf("%s\n", Mix_GetError());
    }

    do
	{
        lap_time = clock();
        difference = lap_time - before;
        msec = difference * 1000 / CLOCKS_PER_SEC;
        int i, c;

        if(msec > (1/FPS)*1000){ //falta el /FPS
            disp_update();	//Actualiza el display con el contenido del buffer
            coord = joy_read();	//Guarda las coordenadas medidas
            disp_clear();

            if(coord.y > THRESHOLD && !joyMoved){
                joyValue = UP;
                joyMoved = 1;
            }
            else if(coord.y < -THRESHOLD && !joyMoved) {
                joyValue = DOWN;
                joyMoved = 1;
            }
            else if(coord.x > THRESHOLD && !joyMoved){
                joyValue = RIGHT;
                joyMoved = 1;
            }
            else if (coord.x < -THRESHOLD && !joyMoved){
                joyValue = LEFT;
                joyMoved = 1;
            }

            if(coord.x < THRESHOLD && coord.x > -THRESHOLD && coord.y < THRESHOLD && coord.y > -THRESHOLD){
                joyMoved = 0;
            }

            if(coord.sw == J_NOPRESS){
                joyPressed = 0;
            }
            

            switch (screen)
            {
            case MENU:
                for(i = 0 ; i < 16 ; i++){
                    for (c = 0 ; c < 16 ; c++){
                        pos.x = c;
                        pos.y = i;
                        disp_write(pos, mainMenu[i][c]);
                    }
                }
                
                for(i=(optionSelected?8:0) ; i < (optionSelected?16:8) ; i++){
                    for(c = 0 ; c < 16 ; c++){
                        pos.x = c;
                        pos.y = i;
                        disp_write(pos, !mainMenu[i][c]);
                    }
                }

                if(joyMoved){
                    if(joyValue == UP){
                        optionSelected = 0;
                    }
                    if(joyValue == DOWN){
                        optionSelected = 1;
                    }
                }

                if(coord.sw == J_PRESS && joyPressed == 0){
                    joyPressed = 1;
                    if(optionSelected == 0){
                        screen = GAME;
                        difficulty = 0;
                        createMap(map,difficulty);
					    spawnRana(map, pRana);
                        vidas = 3;
                        ct_score (0,5,0,5,0);
                        timerCoord.x = 0;
                        timerCoord.y = DISP_MAX_Y;
                        
                    }
                    else if (optionSelected == 1){
                        do_exit = 1;
                    }
                }
                
                break;
            case PAUSE:
                for(i = 0 ; i < 16 ; i++){
                    for (c = 0 ; c < 16 ; c++){
                        pos.x = c;
                        pos.y = i;
                        disp_write(pos, pauseMenu[i][c]);
                    }
                }
                
                for(i=(optionSelected?8:0) ; i < (optionSelected?16:8) ; i++){
                    for(c = 0 ; c < 16 ; c++){
                        pos.x = c;
                        pos.y = i;
                        disp_write(pos, !pauseMenu[i][c]);
                    }
                }

                if(joyMoved){
                    if(joyValue == UP){
                        optionSelected = 0;
                    }
                    if(joyValue == DOWN){
                        optionSelected = 1;
                    }
                }

                if(coord.sw == J_PRESS && joyPressed == 0){
                    joyPressed = 1;
                    if(optionSelected == 0){
                        screen = GAME;
                    }
                    else if (optionSelected == 1){
                        screen = MENU;
                    }
                }
                break;
            case GAME:

                if(livesAnimationCounter){
                    livesAnimationCounter--;

                    if(((livesAnimationCounter < LIVES_ANIMATION*11/11 && livesAnimationCounter > LIVES_ANIMATION*9/11)
                        || (livesAnimationCounter < LIVES_ANIMATION*8/11 && livesAnimationCounter > LIVES_ANIMATION*6/11))
                        || (livesAnimationCounter < LIVES_ANIMATION*5/11 && livesAnimationCounter > LIVES_ANIMATION*3/11)
                        || (livesAnimationCounter < LIVES_ANIMATION*2/11)){
                        
                        if(livesAnimationCounter >= LIVES_ANIMATION*5.5/11){
                            for(i = 0 ; i < 16 ; i++){
                                for (c = 0 ; c < 16 ; c++){
                                    pos.x = c;
                                    pos.y = i;
                                    if(vidas == 2)
                                        disp_write(pos, livesAnimation3[i][c]);
                                    else if(vidas == 1)
                                        disp_write(pos, livesAnimation2[i][c]);
                                }
                            }
                        }
                        else{
                            for(i = 0 ; i < 16 ; i++){
                                for (c = 0 ; c < 16 ; c++){
                                    pos.x = c;
                                    pos.y = i;
                                    if(vidas == 2)
                                        disp_write(pos, livesAnimation2[i][c]);
                                    else if(vidas == 1)
                                        disp_write(pos, livesAnimation1[i][c]);
                                }
                            }
                        }
                        
                    }
                }
                else if(levelAnimationCounter){
                    levelAnimationCounter--;

                    if(((levelAnimationCounter < LEVEL_ANIMATION*11/11 && levelAnimationCounter > LEVEL_ANIMATION*9/11)
                        || (levelAnimationCounter < LEVEL_ANIMATION*8/11 && levelAnimationCounter > LEVEL_ANIMATION*6/11))
                        || (levelAnimationCounter < LEVEL_ANIMATION*5/11 && levelAnimationCounter > LEVEL_ANIMATION*3/11)
                        || (levelAnimationCounter < LEVEL_ANIMATION*2/11)){
                        
                        for(i = 0 ; i < 16 ; i++){
                            for (c = 0 ; c < 16 ; c++){
                                pos.x = c;
                                pos.y = i;
                                
                                disp_write(pos, levelAnimation[i][c]);
                                
                            }
                        }
                        
                    }
                }
                else{
 
                    fpsCounter++;
                    if(fpsCounter >= FPS){
                        fpsCounter = 0;
                        timeLeft--;
                    }

                    disp_clear();

                    timerCoord.x = 0;
                    timerCoord.y = DISP_MAX_Y;
                    disp_write(timerCoord, 1);
                    for(i = 0 ; i < timeLeft ; i++){
                        if(timerCoord.x == 0 && timerCoord.y != 0){
                            timerCoord.y--;
                        }
                        else if(timerCoord.y == 0 && timerCoord.x != DISP_MAX_X){
                            timerCoord.x++;
                        }
                        else if(timerCoord.x == DISP_MAX_X && timerCoord.y != DISP_MAX_Y){
                            timerCoord.y++;
                        }
                        else if (timerCoord.y == DISP_MAX_Y && timerCoord.x != 0){
                            timerCoord.x--;
                        }
                        disp_write(timerCoord, 1);
                    }
                    if(timeLeft == START_TIME*0.25){
                        Mix_PlayChannel(-1, sound_timer, 0);
                    }

                    
                    for(i = 0 ; i < HEIGHT ; i++){
                        linea_t * linea = map+i;
                        pos.y = HEIGHT - i;

                        if(i == 0 || i == HEIGHT/2){
                            for(c = 0 ; c < WIDTH ; c++){
                                pos.x = c+1;
                                disp_write(pos, 0);
                            }
                        }
                        else if(i < HEIGHT/2){
                            for(c = 0 ; c < WIDTH ; c++){
                                pos.x = c+1;
                                disp_write(pos, 0);
                            }
                            for(c = 0 ; c < linea->cant_obj ; c++){
                                int sizePos = 0;
                                for(sizePos = 0 ; sizePos < linea->size ; sizePos++){
                                    pos.x = linea->po[c] + sizePos;
                                    if(pos.x >= 0 && pos.x <= WIDTH-1){
                                        pos.x++;
                                        disp_write(pos, 1);
                                    } 
                                } 
                            } 
                        } 
                        else if (i > HEIGHT/2 && i != HEIGHT-1){
                            for(c = 0 ; c < WIDTH ; c++){
                                pos.x = c+1;
                                disp_write(pos, 1);
                            }
                            
                            for(c = 0 ; c < linea->cant_obj ; c++){
                                int sizePos = 0;
                                for(sizePos = 0 ; sizePos < linea->size ; sizePos++){
                                    pos.x = linea->po[c] + sizePos;
                                    if(pos.x >= 0 && pos.x <= WIDTH-1){
                                        pos.x++;
                                        disp_write(pos, 0);
                                    }
                                }
                            }
                            
                        } 
                        else if(i == HEIGHT-1){
                            for(c = 0 ; c < WIDTH ; c++){
                                pos.x = c+1;
                                disp_write(pos, 1);
                            }
                            if(winPosStates[0] != WIN_OCC){
                                pos.x = WINPOS1 + 1;
                                disp_write(pos, 0);
                            }
                            if(winPosStates[1] != WIN_OCC){
                                pos.x = WINPOS2 + 1;
                                disp_write(pos, 0);
                            }
                            if(winPosStates[2] != WIN_OCC){
                                pos.x = WINPOS3 + 1;
                                disp_write(pos, 0);
                            }
                            if(winPosStates[3] != WIN_OCC){
                                pos.x = WINPOS4 + 1;
                                disp_write(pos, 0);
                            }
                            if(winPosStates[4] != WIN_OCC){
                                pos.x = WINPOS5 + 1;
                                disp_write(pos, 0);
                            }                   
                        }

                        pos.x = pRana->posx + 1;
                        pos.y = HEIGHT - pRana->posy;
                        ranaColorTimer++;
                        if(ranaColorTimer == 5){
                            ranaColorTimer = 0;
                            ranaColor = !(ranaColor);
                        }
                        
                        disp_write(pos, ranaColor); 

                        if(!joyMoved){
                            isMoving = 0;
                        }
                        
                        if(joyMoved && !isMoving){
                            isMoving = 1;
                            Mix_PlayChannel(-1, sound_hop, 0);
                            switch (joyValue)
                            {
                            case UP:
                                MoveRana(pRana, UP, map+rana.posy);
                                break;
                            case DOWN:
                                if(!(pRana->posy == 0))
                                    MoveRana(pRana, DOWN, map+rana.posy);
                                break;
                            case LEFT:
                                if(!(pRana->posx == 0))
                                    MoveRana(pRana, LEFT, map+rana.posy);
                                break;
                            case RIGHT:
                                if(!(pRana->posx == WIDTH))
                                    MoveRana(pRana, RIGHT, map+rana.posy);
                                break;
                            default:
                                break;
                            }
                        }

                        if(linea->cant_obj > 0){
                            switch (linea->v)
                            {
                            case 1:
                                if(fpsCounter == 0){
                                    moveLine(linea, i, pRana);
                                }
                                break;
                            case 2:
                                if(fpsCounter == FPS/2 || fpsCounter == 0){
                                    moveLine(linea, i, pRana);
                                }
                                break;
                            case 3:
                                if(fpsCounter == FPS/3 || fpsCounter == FPS*2/3 || fpsCounter == 0){
                                    moveLine(linea, i, pRana);
                                }
                            default:
                                if(fpsCounter == FPS/5 || fpsCounter == FPS*2/5 || fpsCounter == FPS*3/5 || fpsCounter == FPS*4/5 || fpsCounter == 0){
                                    moveLine(linea, i, pRana);
                                }
                            break;
                            }                        
                        }

                        int collisionValue = RanaCollisions(pRana, &map[pRana->posy]);

                        if(collisionValue == 1 || !timeLeft){
                            
                            if(pRana->posy > HEIGHT/2){
                                Mix_PlayChannel(-1, sound_drown, 0);
                            }
                            else if (pRana->posy <= HEIGHT/2){
                                Mix_PlayChannel(-1, sound_squash, 0);
                            }
                            
                            RestarVidas(pRana, 0, "score.txt");
                            if(vidas == 0){
                                screen = MENU;
                            }

                            
                            
                            timeLeft = START_TIME;
                            livesAnimationCounter = LIVES_ANIMATION;
                        }
                        else if(collisionValue == 2){
                            printf("GANE!!");
                            
                            difficulty++;
							createMap(map, difficulty);
                        }
                    }

                    

                    if(coord.sw == J_PRESS && joyPressed == 0){
                        joyPressed = 1;
                        screen = PAUSE;
                    }
                }
                disp_update();
                break;
            }      
            before = clock();
        }
		

		
	} while(!do_exit);	//termina si se presiona el switch
	
	//Borro el display al salir
	disp_clear();
    disp_update();
    Mix_FreeChunk(sound_drown);
    Mix_FreeChunk(sound_hop);
    Mix_FreeChunk(sound_squash);
    Mix_FreeChunk(sound_timer);
    Mix_CloseAudio();
    SDL_Quit();
}
