#include "RaspiData.h"

void pause(screenHandler_t * screenHandler, joystick_t * joystickHandler, mainMenuHandler_t * mainMenuHandler){
    
    int i, c;
    
    for(i = 0 ; i < DISP_CANT_Y_DOTS ; i++){
        for (c = 0 ; c < DISP_CANT_X_DOTS ; c++){
            joystickHandler->pos.x = c;
            joystickHandler->pos.y = i;
            disp_write(joystickHandler->pos, pauseMenu[i][c]);
        }
    }

    for(i = (screenHandler->optionSelected?8:0) ; i < (screenHandler->optionSelected?16:8) ; i++){
        for(c = 0 ; c < DISP_CANT_X_DOTS ; c++){
            joystickHandler->pos.x = c;
            joystickHandler->pos.y = i;
            disp_write(joystickHandler->pos, !pauseMenu[i][c]);
        }
    }

    if(joystickHandler->joyMoved){
        if(joystickHandler->joyValue == UP){
            screenHandler->optionSelected = 0;
        }
        if(joystickHandler->joyValue == DOWN){
            screenHandler->optionSelected = 1;
        }
    }

    if(joystickHandler->coord.sw == J_PRESS && joystickHandler->joyPressed == 0){
        joystickHandler->joyPressed = 1;
        if(screenHandler->optionSelected == 0){
            screenHandler->screen = GAME;
        }
        else if (screenHandler->optionSelected == 1){
            mainMenuInit(screenHandler, mainMenuHandler);
        }
    }
}
