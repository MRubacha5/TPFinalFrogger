
#include "RaspiData.h"

int main(void)
{
    /**************************************LEVELGEN/VAR*********************************** */
    rana_t rana;
    rana_t * pRana = &rana;
    linea_t map[HEIGHT];

    worldData_t worldData;

    joystick_t joystickHandler = joystickInit();
    timer_t timerHandler = timerInit();

    screenHandler_t screenHandler;
    gameOverHandler_t gameOverHandler;
    hiscoreHandler_t hiscoreHandler;
    
    screensInit(&screenHandler, &gameOverHandler, &hiscoreHandler);

    soundHandler_t soundHandler = soundInit();

    animationHandler_t animationHandler = animationInit();

    int i, c, j;

    do
	{

        timerUpdate(&timerHandler);

        if(timerHandler.msec > (1/FPS)*1000){ 
            
            joystickUpdate(&joystickHandler);

            switch (screenHandler.screen)
            {
            case MENU:
                mainMenu(&screenHandler, &joystickHandler, pRana, &worldData, map);
                break;
            case PAUSE:
                pause(&screenHandler, &joystickHandler);
                break;
            case GAME:
                inGame(map, pRana, &worldData, &screenHandler, &joystickHandler, &animationHandler, &timerHandler, &soundHandler);
                break;
            case GAMEOVER:
                
                if(IsMax(currentScore, "score.txt")){

                    for(i = 0 ; i < 3 ; i++){
                        for(c = 0 ; c < 5 ; c++){
                            for(j = 0 ; j < 3 ; j++){
                                pos.x = 3 + i*4 + j;
                                pos.y = 5 + c;
                                if(i == charSelected){
                                    disp_write(pos, !letters[charSelection[i]][c][j]);
                                }
                                else{
                                    disp_write(pos, letters[charSelection[i]][c][j]);
                                }
                                
                            }
                        }
                    }

                    for(c = 0 ; c < 7 ; c++){
                            for(j = 0 ; j < 5 ; j++){
                                pos.x = 2 + charSelected*4 + j;
                                pos.y = 4 + c;
                                if(c == 0 || c == 6 || j == 0 || j == 4)
                                    disp_write(pos, 1);
                            }
                        }

                    if(!joyMoved){
                        isMoving = 0;
                    }

                    if(joyMoved && !isMoving){
                        isMoving = 1;

                        switch (joyValue)
                        {
                        case DOWN:
                            charSelection[charSelected] = (charSelection[charSelected] < 25)?(charSelection[charSelected]+1):0;
                            break;
                        case UP:
                            charSelection[charSelected] = (charSelection[charSelected] > 0)?(charSelection[charSelected]-1):25;
                            break;
                        case RIGHT:
                            charSelected = (charSelected < 2)?(charSelected+1):(charSelected);
                            break;
                        case LEFT:
                            charSelected = (charSelected > 0)?(charSelected-1):(charSelected);
                            break;
                        }
                    }

                    if(coord.sw == J_PRESS && joyPressed == 0){
                        joyPressed = 1;

                        for(i = 0 ; i < 3 ; i++){
                            name[i] = charSelection[i] + 'A';
                        }

                        max_scores(currentScore,"score.txt", name);

                        charSelection[0] = 0;
                        charSelection[1] = 0;
                        charSelection[2] = 0;
                        charSelected = 0;

                        getTopScores("score.txt");
                        screen = HIGHSCORE;
                        highSelected = 0;
                        disp_clear();
                    }
                }
                else{
                    screen = HIGHSCORE;
                    highSelected = 0;
                }

                disp_update();
                break;
            case HIGHSCORE:
                
                disp_clear();

                for(j = 0 ; j < 3 ; j++){
                    for(i = 0 ; i < 5 ; i++){
                        for(c = 0 ; c < 3 ; c++){
                            pos.x = 3 + j*4 + c;
                            pos.y = 1 + i;
                            
                            charToWrite = topNames[highSelected][j] - 'A';

                            disp_write(pos, letters[charToWrite][i][c]);
                        }
                    }
                }

                char buffer[6]; 
				intToChar(6, buffer ,topScores[highSelected]);

                for(j = 0 ; j < 5 ; j++){
                    for(i = 0 ; i < 5 ; i++){
                        for(c = 0 ; c < 3 ; c++){
                            pos.x = 1 + j*3 + c;
                            pos.y = 7 + i;

                            intToWrite = buffer[j] - '0';

                            disp_write(pos, numbers[intToWrite][i][c]);
                        }
                    }
                }

                if(!joyMoved){
                    isMoving = 0;
                }

                if(joyMoved && !isMoving){
                    isMoving = 1;

                    switch (joyValue)
                    {
                    case DOWN:
                        highSelected = (highSelected < 9)?(highSelected+1):(highSelected);
                        break;
                    case UP:
                        highSelected = (highSelected > 0)?(highSelected-1):(highSelected);
                        break;
                    }
                }

                if(coord.sw == J_PRESS && joyPressed == 0){
                    joyPressed = 1;
                    screen = MENU;
                }

                break;
            } 
                 
            timerHandler.before = clock();
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
