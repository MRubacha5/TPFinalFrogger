#include "RaspiData.h"

void gameover(joystick_t * joystickHandler, gameOverHandler_t * gameOverHandler, screenHandler_t * screenHandler, hiscoreHandler_t * hiscoreHandler){
    
    int i, c, j;

    if(IsMax(currentScore, "score.txt")){
        
        for(i = 0 ; i < 3 ; i++){
            for(c = 0 ; c < 5 ; c++){
                for(j = 0 ; j < 3 ; j++){
                    joystickHandler->pos.x = 3 + i*4 + j;
                    joystickHandler->pos.y = 5 + c;
                    if(i == screenHandler->optionSelected){
                        disp_write(joystickHandler->pos, !letters[gameOverHandler->charSelection[i]][c][j]);
                    }
                    else{
                        disp_write(joystickHandler->pos, letters[gameOverHandler->charSelection[i]][c][j]);
                    }
                    
                }
            }
        }

        for(c = 0 ; c < 7 ; c++){
            for(j = 0 ; j < 5 ; j++){
                joystickHandler->pos.x = 2 + screenHandler->optionSelected*4 + j;
                joystickHandler->pos.y = 4 + c;
                if(c == 0 || c == 6 || j == 0 || j == 4)
                    disp_write(joystickHandler->pos, 1);
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
                gameOverHandler->charSelection[screenHandler->optionSelected] = (gameOverHandler->charSelection[screenHandler->optionSelected] < 25)?(gameOverHandler->charSelection[screenHandler->optionSelected]+1):0;
                break;
            case UP:
                gameOverHandler->charSelection[screenHandler->optionSelected] = (gameOverHandler->charSelection[screenHandler->optionSelected] > 0)?(gameOverHandler->charSelection[screenHandler->optionSelected]-1):25;
                break;
            case RIGHT:
                screenHandler->optionSelected = (screenHandler->optionSelected < 2)?(screenHandler->optionSelected+1):(screenHandler->optionSelected);
                break;
            case LEFT:
                screenHandler->optionSelected = (screenHandler->optionSelected > 0)?(screenHandler->optionSelected-1):(screenHandler->optionSelected);
                break;
            }
        }

        if(joystickHandler->coord.sw == J_PRESS && joystickHandler->joyPressed == 0){
            joystickHandler->joyPressed = 1;

            for(i = 0 ; i < 3 ; i++){
                name[i] = gameOverHandler->charSelection[i] + 'A';
            }

            max_scores(currentScore,"score.txt", name);

            gameOverHandler->charSelection[0] = 0;
            gameOverHandler->charSelection[1] = 0;
            gameOverHandler->charSelection[2] = 0;
            screenHandler->optionSelected = 0;

            getTopScores("score.txt");
            hiscoreInit(screenHandler, hiscoreHandler);
            disp_clear();
        }
    }
    else{
        hiscoreInit(screenHandler, hiscoreHandler);
    }
    disp_update();
}