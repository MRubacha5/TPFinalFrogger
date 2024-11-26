#include "RaspiData.h"

void timerUpdate(timer_t * handler){
    
    handler->lap_time = clock();
    handler->difference = handler->lap_time - handler->before;
    handler->msec = handler->difference * 1000 / CLOCKS_PER_SEC;

}