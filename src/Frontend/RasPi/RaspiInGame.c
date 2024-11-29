#include "RaspiData.h"

void inGame(linea_t * map, rana_t * pRana, worldData_t * worldData, screenHandler_t * screenHandler, joystick_t * joystickHandler, animationHandler_t * animationHandler, timerStruct_t * timeHandler, soundHandler_t * soundHandler, gameOverHandler_t * gameOverHandler){

    int i, c;

    if(animationHandler->livesAnimationCounter){
        animationHandler->livesAnimationCounter--;

        if(((animationHandler->livesAnimationCounter < LIVES_ANIMATION*11/11 && animationHandler->livesAnimationCounter > LIVES_ANIMATION*9/11)
            || (animationHandler->livesAnimationCounter < LIVES_ANIMATION*8/11 && animationHandler->livesAnimationCounter > LIVES_ANIMATION*6/11))
            || (animationHandler->livesAnimationCounter < LIVES_ANIMATION*5/11 && animationHandler->livesAnimationCounter > LIVES_ANIMATION*3/11)
            || (animationHandler->livesAnimationCounter < LIVES_ANIMATION*2/11)){
            
            if(animationHandler->livesAnimationCounter >= LIVES_ANIMATION*5.5/11){
                for(i = 0 ; i < DISP_CANT_Y_DOTS ; i++){
                    for (c = 0 ; c < DISP_CANT_X_DOTS ; c++){
                        joystickHandler->pos.x = c;
                        joystickHandler->pos.y = i;
                        if(pRana->vidas == 2)
                            disp_write(joystickHandler->pos, livesAnimation3[i][c]);
                        else if(pRana->vidas == 1)
                            disp_write(joystickHandler->pos, livesAnimation2[i][c]);
                    }
                }
            }
            else{
                for(i = 0 ; i < DISP_CANT_Y_DOTS ; i++){
                    for (c = 0 ; c < DISP_CANT_X_DOTS ; c++){
                        joystickHandler->pos.x = c;
                        joystickHandler->pos.y = i;
                        if(pRana->vidas == 2)
                            disp_write(joystickHandler->pos, livesAnimation2[i][c]);
                        else if(pRana->vidas == 1)
                            disp_write(joystickHandler->pos, livesAnimation1[i][c]);
                    }
                }
            }
            
        }
    }
    else if(animationHandler->levelAnimationCounter){
        animationHandler->levelAnimationCounter--;

        if(((animationHandler->levelAnimationCounter < LEVEL_ANIMATION*11/11 && animationHandler->levelAnimationCounter > LEVEL_ANIMATION*9/11)
            || (animationHandler->levelAnimationCounter < LEVEL_ANIMATION*8/11 && animationHandler->levelAnimationCounter > LEVEL_ANIMATION*6/11))
            || (animationHandler->levelAnimationCounter < LEVEL_ANIMATION*5/11 && animationHandler->levelAnimationCounter > LEVEL_ANIMATION*3/11)
            || (animationHandler->levelAnimationCounter < LEVEL_ANIMATION*2/11)){
            
            for(i = 0 ; i < DISP_CANT_Y_DOTS ; i++){
                for (c = 0 ; c < DISP_CANT_X_DOTS ; c++){
                    joystickHandler->pos.x = c;
                    joystickHandler->pos.y = i;
                    
                    disp_write(joystickHandler->pos, levelAnimation[i][c]);
                    
                }
            }
            
        }

        if(animationHandler->levelAnimationCounter == 1){
            Mix_PlayMusic(soundHandler->sound_main_theme, -1);
        }
    }
    else{
        timeHandler->fpsCounter++;
        if(timeHandler->fpsCounter >= FPS){
            timeHandler->fpsCounter = 0;
            worldData->timeLeft--;
        }

        disp_clear();
    
        animationHandler->timerCoord.x = 0;
        animationHandler->timerCoord.y = DISP_MAX_Y;
        disp_write(animationHandler->timerCoord, 1);
        for(i = 0 ; i < worldData->timeLeft ; i++){
            if(animationHandler->timerCoord.x == 0 && animationHandler->timerCoord.y != 0){
                animationHandler->timerCoord.y--;
            }
            else if(animationHandler->timerCoord.y == 0 && animationHandler->timerCoord.x != DISP_MAX_X){
                animationHandler->timerCoord.x++;
            }
            else if(animationHandler->timerCoord.x == DISP_MAX_X && animationHandler->timerCoord.y != DISP_MAX_Y){
                animationHandler->timerCoord.y++;
            }
            else if (animationHandler->timerCoord.y == DISP_MAX_Y && animationHandler->timerCoord.x != 0){
                animationHandler->timerCoord.x--;
            }
            disp_write(animationHandler->timerCoord, 1);
        }
        if(worldData->timeLeft == START_TIME*0.25){
            Mix_PlayChannel(-1, soundHandler->sound_timer, 0);
        }


        for(i = 0 ; i < HEIGHT ; i++){
            linea_t * linea = map+i;
            joystickHandler->pos.y = HEIGHT - i;

            if(i == 0 || i == HEIGHT/2){
                for(c = 0 ; c < WIDTH ; c++){
                    joystickHandler->pos.x = c+1;
                    disp_write(joystickHandler->pos, 0);
                }
            }
            else if(i < HEIGHT/2){
                for(c = 0 ; c < WIDTH ; c++){
                    joystickHandler->pos.x = c+1;
                    disp_write(joystickHandler->pos, 0);
                }
                for(c = 0 ; c < linea->cant_obj ; c++){
                    int sizePos = 0;
                    for(sizePos = 0 ; sizePos < linea->size ; sizePos++){
                        joystickHandler->pos.x = linea->po[c] + sizePos;
                        if(joystickHandler->pos.x >= 0 && joystickHandler->pos.x <= WIDTH-1){
                            joystickHandler->pos.x++;
                            disp_write(joystickHandler->pos, 1);
                        } 
                    } 
                } 
            } 
            else if (i > HEIGHT/2 && i != HEIGHT-1){
                for(c = 0 ; c < WIDTH ; c++){
                    joystickHandler->pos.x = c+1;
                    disp_write(joystickHandler->pos, 1);
                }
                
                for(c = 0 ; c < linea->cant_obj ; c++){
                    int sizePos = 0;
                    for(sizePos = 0 ; sizePos < linea->size ; sizePos++){
                        joystickHandler->pos.x = linea->po[c] + sizePos;
                        if(joystickHandler->pos.x >= 0 && joystickHandler->pos.x <= WIDTH-1){
                            joystickHandler->pos.x++;
                            disp_write(joystickHandler->pos, 0);
                        }
                    }
                }
                
            } 
            else if(i == HEIGHT-1){
                for(c = 0 ; c < WIDTH ; c++){
                    joystickHandler->pos.x = c+1;
                    disp_write(joystickHandler->pos, 1);
                }
                if(worldData->winPosStates[0] != WIN_OCC){
                    joystickHandler->pos.x = WINPOS1 + 1;
                    disp_write(joystickHandler->pos, 0);
                }
                if(worldData->winPosStates[1] != WIN_OCC){
                    joystickHandler->pos.x = WINPOS2 + 1;
                    disp_write(joystickHandler->pos, 0);
                }
                if(worldData->winPosStates[2] != WIN_OCC){
                    joystickHandler->pos.x = WINPOS3 + 1;
                    disp_write(joystickHandler->pos, 0);
                }
                if(worldData->winPosStates[3] != WIN_OCC){
                    joystickHandler->pos.x = WINPOS4 + 1;
                    disp_write(joystickHandler->pos, 0);
                }
                if(worldData->winPosStates[4] != WIN_OCC){
                    joystickHandler->pos.x = WINPOS5 + 1;
                    disp_write(joystickHandler->pos, 0);
                }                   
            }

            if(linea->cant_obj > 0){
                switch (linea->v)
                {
                case 1:
                    if(timeHandler->fpsCounter == 0){
                        moveLine(linea, i, pRana);
                    }
                    break;
                case 2:
                    if(timeHandler->fpsCounter == FPS/2 || timeHandler->fpsCounter == 0){
                        moveLine(linea, i, pRana);
                    }
                    break;
                case 3:
                    if(timeHandler->fpsCounter == FPS/3 || timeHandler->fpsCounter == FPS*2/3 || timeHandler->fpsCounter == 0){
                        moveLine(linea, i, pRana);
                    }
                    break;
                default:
                    if(timeHandler->fpsCounter == FPS/5 || timeHandler->fpsCounter == FPS*2/5 || timeHandler->fpsCounter == FPS*3/5 || timeHandler->fpsCounter == FPS*4/5 || timeHandler->fpsCounter == 0){
                        moveLine(linea, i, pRana);
                    }
                    break;
                }                        
            }
        }

        joystickHandler->pos.x = pRana->posx + 1;
        joystickHandler->pos.y = HEIGHT - pRana->posy;
        animationHandler->ranaColorTimer++;
        if(animationHandler->ranaColorTimer == 5){
            animationHandler->ranaColorTimer = 0;
            animationHandler->ranaColor = !(animationHandler->ranaColor);
        }
        
        disp_write(joystickHandler->pos, animationHandler->ranaColor); 

        if(!(joystickHandler->joyMoved)){
            joystickHandler->isMoving = 0;
        }
        
        if(joystickHandler->joyMoved && !(joystickHandler->isMoving)){
            joystickHandler->isMoving = 1;
            Mix_PlayChannel(-1, soundHandler->sound_hop, 0);
            switch (joystickHandler->joyValue)
            {
            case UP:
                MoveRana(pRana, UP, map+(pRana->posy)); 
                currentScore = ct_score(pRana->posy, worldData->timeLeft, pRana->vidas, (pRana->posy == HEIGHT-1)?(1):(0));
                break;
            case DOWN:
                if(!(pRana->posy == 0))
                    MoveRana(pRana, DOWN, map+(pRana->posy));
                break;
            case LEFT:
                if(!(pRana->posx == 0))
                    MoveRana(pRana, LEFT, map+(pRana->posy));
                break;
            case RIGHT:
                if(!(pRana->posx == WIDTH))
                    MoveRana(pRana, RIGHT, map+(pRana->posy));
                break;
            default:
                break;
            }
        }

        int collisionValue = RanaCollisions(pRana, map+(pRana->posy), worldData);

        if(collisionValue == 1 || !(worldData->timeLeft)){

            if(pRana->posy > HEIGHT/2){
                Mix_PlayChannel(-1, soundHandler->sound_drown, 0);
            }
            else if (pRana->posy <= HEIGHT/2){
                Mix_PlayChannel(-1, soundHandler->sound_squash, 0);
            }
            
            RestarVidas(pRana, worldData);
            if(pRana->vidas == 0){
                disp_clear();
                gameOverInit(screenHandler, gameOverHandler);
            }
            else {
                animationHandler->livesAnimationCounter = LIVES_ANIMATION;
            }

        }
        else if(collisionValue == NEXTLEVELFALSE){
            Mix_PlayChannel(-1, soundHandler->sound_homed, 0);
        }
        else if(collisionValue == NEXTLEVELTRUE){
            animationHandler->levelAnimationCounter = LEVEL_ANIMATION;
            Mix_HaltMusic();
            Mix_PlayChannel(-1, soundHandler->sound_level_clear, 0);
            worldData->difficulty++;
            createMap(map, worldData);
        }

        if(joystickHandler->coord.sw == J_PRESS && joystickHandler->joyPressed == 0){
            joystickHandler->joyPressed = 1;
            screenHandler->screen = PAUSE;
        }

    }

    disp_update();

}
