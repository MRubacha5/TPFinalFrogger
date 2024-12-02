
#include "RaspiData.h"

int main(void)
{
    /**************************************LEVELGEN/VAR*********************************** */
    rana_t rana;
    rana_t * pRana = &rana;
    linea_t map[HEIGHT];

    worldData_t worldData;
    screenHandler_t screenHandler;
    mainMenuHandler_t mainMenuHandler;
    gameOverHandler_t gameOverHandler;
    hiscoreHandler_t hiscoreHandler;
    
    joystick_t joystickHandler = joystickInit();
    timerStruct_t timerHandler = timeInit();
    soundHandler_t soundHandler = soundInit();
    animationHandler_t animationHandler = animationInit();

    screensInit(&screenHandler, &mainMenuHandler, &gameOverHandler, &hiscoreHandler);

    Mix_PlayMusic(soundHandler.sound_main_theme, -1);

    do
	{

        timerUpdate(&timerHandler);

        if(timerHandler.msec > (1/FPS)*1000){ 
            
            joystickUpdate(&joystickHandler);

            /***********************
            * FINITE STATE MACHINE * 
            ************************/

            switch (screenHandler.screen)
            {
            case MENU:
                menu(&mainMenuHandler, &animationHandler, &hiscoreHandler, &screenHandler, &joystickHandler, pRana, &worldData, map);
                break;
            case PAUSE:
                pause(&screenHandler, &joystickHandler, &mainMenuHandler);
                break;
            case GAME:
                inGame(map, pRana, &worldData, &screenHandler, &joystickHandler, &animationHandler, &timerHandler, &soundHandler, &gameOverHandler);
                break;
            case GAMEOVER:
                gameover(&joystickHandler, &gameOverHandler, &screenHandler, &hiscoreHandler);
                break;
            case HISCORE:
                
                hiscoreScreen(&joystickHandler, &screenHandler, &hiscoreHandler, &mainMenuHandler);
                break;
            } 
                 
            timerHandler.before = clock();
        }
		
	} while(!(screenHandler.do_exit));	//termina si se presiona el switch
	
	//Borro el display al salir

    destroyEverything(&soundHandler);
	
}
