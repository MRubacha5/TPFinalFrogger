#include "RaspiData.h"

joystick_t joystickInit(void){
    joystick_t holder;
    
    joy_init();										
	disp_init();									
	disp_clear();									
    holder->pos = {DISP_MAX_X>>1 , DISP_MAX_Y>>1};	
	holder->coord = {0,0,J_NOPRESS};					
    holder->joyMoved = 0;
    holder->joyValue = -1;
    holder->joyPressed = 0;
    holder->isMoving = 0;

    return holder;
}

timer_t timeInit(void){
    timer_t holder;
    holder->before = clock(); 
    holder->difference = 0;
    holder->lap_time;
    holder->msec = 0;
    holder->fpsCounter = 0;
    return holder;
}

void screensInit(screenHandler_t * screenHandler, gameOverHandler_t * gameOverHandler, hiscoreHandler_t * highscoreHandler){
    screenHandler->screen = MENU;
    screenHandler->optionSelected = 0;
    screenHandler->do_exit = 0;

    gameOverHandler->charSelection[3] = {0, 0, 0};

    hiscoreHandler->charToWrite = 0;
    hiscoreHandler->intToWrite = 0;
    return;
}

void mainMenuInit(screenHandler_t * screenHandler){
    screenHandler->screen = MENU;
    screenHandler->optionSelected = 0;
    return;
}

void gameStart(screenHandler_t * screenHandler){
    return;
}

void gameOverInit(screenHandler_t * screenHandler, gameOverHandler_t * gameOverHandler){
    screenHandler->screen = GAMEOVER;
    screenHandler->optionSelected = 0;
    gameOverHandler->charSelection[3] = {0, 0, 0};
    return;
}

void hiscoreInit(screenHandler_t * screenHandler, hiscoreHandler_t * hiscoreHandler){
    screenHandler->screen = HISCORE;
    screenHandler->optionSelected = 0;
    hiscoreHandler->charToWrite = 0;
    hiscoreHandler->intToWrite = 0;
    return;
}

soundHandler_t soundInit(void){
    SDL_Init(SDL_INIT_AUDIO);

    Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);

    soundHandler_t handler = {
        .sound_drown = ("../assets/Audio/sound-frogger-drown.wav"),
        .sound_squash = ("../assets/Audio/sound-frogger-squash.wav"),
        .sound_hop = ("../assets/Audio/sound-frogger-hop.wav"),
        .sound_timer = ("../assets/Audio/sound-frogger-time-running-out.wav")
    };

    if(handler.sound_drown == NULL){
        printf("%s\n", Mix_GetError());
    }
    if(handler.sound_squash == NULL){
        printf("error loading squash\n");
    }
    if(handler.sound_hop == NULL){
        printf("%s\n", Mix_GetError());
    }
    if(handler.sound_timer == NULL){
        printf("%s\n", Mix_GetError());
    }

    return handler;

}

animationHandler_t animationInit(void){
    timer_t holder;
    holder->ranaColor = 0;
    holder->ranaColorTimer = 0;
    holder->timerCoord;
    holder->livesAnimationCounter = 0;
    holder->levelAnimationCounter = 0;
    return holder;
}