#include "RaspiData.h"


void menu(mainMenuHandler_t * mainMenuHandler, animationHandler_t * animationHandler, hiscoreHandler_t * hiscoreHandler, screenHandler_t * screenHandler, joystick_t * joystickHandler, rana_t * prana, worldData_t * worldData, linea_t * map){
    int i, c;

    if(mainMenuHandler->screenSelected == 0){
        for(i = 0 ; i < DISP_CANT_Y_DOTS ; i++){
            for (c = 0 ; c < DISP_CANT_X_DOTS ; c++){
                joystickHandler->pos.x = c;
                joystickHandler->pos.y = i;
                disp_write(joystickHandler->pos, mainMenu[i][c]);
            }
        }

        for(i = (screenHandler->optionSelected?8:0) ; i < (screenHandler->optionSelected?16:8) ; i++){
            for(c = 0 ; c < DISP_CANT_X_DOTS ; c++){
                joystickHandler->pos.x = c;
                joystickHandler->pos.y = i;
                disp_write(joystickHandler->pos, !mainMenu[i][c]);
            }
        }
    }
    else{
        for(i = 0 ; i < DISP_CANT_Y_DOTS ; i++){
            for (c = 0 ; c < DISP_CANT_X_DOTS ; c++){
                joystickHandler->pos.x = c;
                joystickHandler->pos.y = i;
                disp_write(joystickHandler->pos, mainMenu2[i][c]);
            }
        }

        for(i = ((screenHandler->optionSelected-1)?8:0) ; i < ((screenHandler->optionSelected-1)?16:8) ; i++){
            for(c = 0 ; c < DISP_CANT_X_DOTS ; c++){
                joystickHandler->pos.x = c;
                joystickHandler->pos.y = i;
                disp_write(joystickHandler->pos, !mainMenu2[i][c]);
            }
        }
    }

    


    if(!(joystickHandler->joyMoved)){
        joystickHandler->isMoving = 0;
    }

    if(joystickHandler->joyMoved && !(joystickHandler->isMoving)){
        joystickHandler->isMoving = 1;

        switch (joystickHandler->joyValue)
        {
        case DOWN:
            if(screenHandler->optionSelected == 1){
                mainMenuHandler->screenSelected = 1;
            }
            if(screenHandler->optionSelected == 0 || screenHandler->optionSelected == 1){
                screenHandler->optionSelected++;
            }
            break;
        case UP:
            if(screenHandler->optionSelected == 1){
                mainMenuHandler->screenSelected = 0;
            }
            if(screenHandler->optionSelected == 1 || screenHandler->optionSelected == 2){
                screenHandler->optionSelected--;
            }
            break;
        }
    }

    if(joystickHandler->coord.sw == J_PRESS && joystickHandler->joyPressed == 0){
        joystickHandler->joyPressed = 1;
        if(screenHandler->optionSelected == 0){
            screenHandler->screen = GAME;
            gameStart(map, worldData);
            spawnRana(prana);
            animationHandler->timerCoord.x = 0;
            animationHandler->timerCoord.y = DISP_MAX_Y;
        }
        else if (screenHandler->optionSelected == 1){
            hiscoreInit(screenHandler, hiscoreHandler);
        }
        else if (screenHandler->optionSelected == 2){
            screenHandler->do_exit = 1;
        }
    }

}
