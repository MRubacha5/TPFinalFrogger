
#include "RaspiData.h"

int main(void)
{
    /**************************************LEVELGEN/VAR*********************************** */
    rana_t rana;
    rana_t * pRana = &rana;
    linea_t map[HEIGHT];

    worldData_t worldData;
    screenHandler_t screenHandler;
    gameOverHandler_t gameOverHandler;
    hiscoreHandler_t hiscoreHandler;
    
    joystick_t joystickHandler = joystickInit();
    timer_t timerHandler = timerInit();
    soundHandler_t soundHandler = soundInit();
    animationHandler_t animationHandler = animationInit();

    screensInit(&screenHandler, &gameOverHandler, &hiscoreHandler);

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
                inGame(map, pRana, &worldData, &screenHandler, &joystickHandler, &animationHandler, &timerHandler, &soundHandler, &gameOverHandler);
                break;
            case GAMEOVER:
                gameover(&joystickHandler, &gameOverHandler, &screenHandler, &hiscoreHandler);
                break;
            case HIGHSCORE:
                
                hiscoreScreen(&joystickHandler, &screenHandler, &hiscoreHandler);
                break;
            } 
                 
            timerHandler.before = clock();
        }
		
	} while(!(screenHandler.do_exit));	//termina si se presiona el switch
	
	//Borro el display al salir
	
}
