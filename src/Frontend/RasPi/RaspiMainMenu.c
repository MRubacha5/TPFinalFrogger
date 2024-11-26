#include "RaspiData.h"


void mainMenu(screenHandler_t * screenHandler, joystick_t * joystickHandler, rana_t * prana, worldData_t * worldData, linea_t * map){
    int i, c;
    
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

    if(joyMoved){
        if(joyValue == UP){
            optionSelected = 0;
        }
        if(joyValue == DOWN){
            optionSelected = 1;
        }
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
                        currentScore = 0;
                        ct_score (0,5,0,5,0);
                        timerCoord.x = 0;
                        timerCoord.y = DISP_MAX_Y;
                        
                    }
                    else if (optionSelected == 1){
                        do_exit = 1;
                    }
                }