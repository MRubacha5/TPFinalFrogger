/*******************************************************************************
 * HEADERS
 ******************************************************************************/

#include "AllegroSetup.h"
#include <stdio.h>


// Easter egg
static const int konami[10] =
{
    ALLEGRO_KEY_UP, ALLEGRO_KEY_UP, ALLEGRO_KEY_DOWN, ALLEGRO_KEY_DOWN, ALLEGRO_KEY_LEFT, 
    ALLEGRO_KEY_RIGHT, ALLEGRO_KEY_LEFT, ALLEGRO_KEY_RIGHT, ALLEGRO_KEY_B, ALLEGRO_KEY_A
};

static int i = 0; 

void inputHandler (allegroComponents_t * Components)
{
    if(Components->ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
    {
        Components->do_exit = true;
    }
    else if(Components->ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
    {
        Components->leftClick = true;
    }
    else if(Components->ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
    {
        Components->leftClick = false;
    }
    else if(Components->ev.type == ALLEGRO_EVENT_MOUSE_AXES)
    {
        Components->mouse_x = Components->ev.mouse.x;
        Components->mouse_y = Components->ev.mouse.y;
    }
    else if(Components->ev.type == ALLEGRO_EVENT_KEY_DOWN)
    {
        switch (Components->screen)
        {
            case MENU: 
            //Easter Egg
            if(Components->ev.keyboard.keycode == konami[i])
            {
                i++;
            }
            else
            {
                i = 0;
            }

            if(i == 10)
            {
                Components->flagValue = 2; //will be lowered to one in a future use
                
                i = 0;
            }
          
            break; 
            

            case PAUSE:
            case HISCORE:
            //Tecla de escape reanuda el juego/ lleva a menu principal
            if(Components->ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE){
                Components->screen = (Components->screen == PAUSE)? GAME : MENU;
            }
            break;

            case GAME:
            switch (Components->ev.keyboard.keycode)
            {
                case ALLEGRO_KEY_ESCAPE:
                Components->screen = PAUSE;
                break;

                case ALLEGRO_KEY_UP:
                case ALLEGRO_KEY_W:
                Components->keycode = ALLEGRO_KEY_UP;
                Components->flagValue = GSIZEY;
                break;

                case ALLEGRO_KEY_DOWN:
                case ALLEGRO_KEY_S:
                Components->keycode = ALLEGRO_KEY_DOWN;
                Components->flagValue = GSIZEY;
                break;

                case ALLEGRO_KEY_LEFT:
                case ALLEGRO_KEY_A:
                Components->keycode = ALLEGRO_KEY_LEFT;
                Components->flagValue = GSIZEX;
                break;

                case ALLEGRO_KEY_RIGHT:
                case ALLEGRO_KEY_D:
                Components->keycode = ALLEGRO_KEY_RIGHT;
                Components->flagValue = GSIZEX;
                break;

            }                
            break;
            
        }
    }
}