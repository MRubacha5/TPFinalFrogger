#include "RaspiData.h"

void hiscoreScreen(joystick_t * joystickHandler, screenHandler_t * screenHandler, hiscoreHandler_t * hiscoreHandler){
    
    int i, c, j;
    
    disp_clear();
    for(j = 0 ; j < 3 ; j++){
        for(i = 0 ; i < 5 ; i++){
            for(c = 0 ; c < 3 ; c++){
                joystickHandler->pos.x = 3 + j*4 + c;
                joystickHandler->pos.y = 1 + i;
                
                hiscoreHandler->charToWrite = topNames[screenHandler->optionSelected][j] - 'A';
                disp_write(joystickHandler->pos, letters[hiscoreHandler->charToWrite][i][c]);
            }
        }
    }
    char buffer[6]; 
    intToChar(6, buffer ,topScores[screenHandler->optionSelected]);

    for(j = 0 ; j < 5 ; j++){
        for(i = 0 ; i < 5 ; i++){
            for(c = 0 ; c < 3 ; c++){
                joystickHandler->pos.x = 1 + j*3 + c;
                joystickHandler->pos.y = 7 + i;

                hiscoreHandler->intToWrite = buffer[j] - '0';

                disp_write(joystickHandler->pos, numbers[hiscoreHandler->intToWrite][i][c]);
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
            screenHandler->optionSelected = (screenHandler->optionSelected < 9)?(screenHandler->optionSelected+1):(screenHandler->optionSelected);
            break;
        case UP:
            screenHandler->optionSelected = (screenHandler->optionSelected > 0)?(screenHandler->optionSelected-1):(screenHandler->optionSelected);
            break;
        }
    }

    if(joystickHandler->coord.sw == J_PRESS && joystickHandler->joyPressed == 0){
        joystickHandler->joyPressed = 1;
        mainMenuInit(screenHandler);
    }

}

