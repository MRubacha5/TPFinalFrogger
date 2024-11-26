
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
                        currentScore = 0;
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

                printf("vidas: %d", vidas);

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
                                break;
                            default:
                                if(fpsCounter == FPS/5 || fpsCounter == FPS*2/5 || fpsCounter == FPS*3/5 || fpsCounter == FPS*4/5 || fpsCounter == 0){
                                    moveLine(linea, i, pRana);
                                }
                                break;
                            }                        
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
                    
                    //lo hago aca o lo hacemos afuera????

                    if(joyMoved && !isMoving){
                        isMoving = 1;
                        Mix_PlayChannel(-1, sound_hop, 0);
                        switch (joyValue)
                        {
                        case UP:
                            MoveRana(pRana, UP, map+rana.posy); 
                            currentScore = ct_score(pRana->posy, timeLeft, HEIGHT, vidas, (pRana->posy == HEIGHT-1)?(1):(0));
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

                    int collisionValue = RanaCollisions(pRana, map+pRana->posy);

                    if(collisionValue == 1 || !timeLeft){

                        if(pRana->posy > HEIGHT/2){
                            Mix_PlayChannel(-1, sound_drown, 0);
                        }
                        else if (pRana->posy <= HEIGHT/2){
                            Mix_PlayChannel(-1, sound_squash, 0);
                        }
                        
                        RestarVidas(pRana, 0, "score.txt");
                        if(vidas == 0){
                            disp_clear();
                            screen = GAMEOVER;
                        }
                        else{
                            timeLeft = START_TIME;
                            livesAnimationCounter = LIVES_ANIMATION;
                        }

                    }
                    else if(collisionValue == 2){
                        levelAnimationCounter = LEVEL_ANIMATION;
                        
                        difficulty++;
                        createMap(map, difficulty);
                    }

                    if(coord.sw == J_PRESS && joyPressed == 0){
                        joyPressed = 1;
                        screen = PAUSE;
                    }
                }
                disp_update();
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
