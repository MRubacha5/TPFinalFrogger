/*******************************************************************************
 * HEADERS
 ******************************************************************************/

#include "AllegroSetup.h"


void pauseScreen (allegroComponents_t * Components)
{
    //PAUSE
    al_draw_filled_rectangle(DISPLAY_X/8, DISPLAY_Y*7/16, DISPLAY_X*7/8, DISPLAY_Y*9/16, al_color_name("black"));
    al_draw_text(Components->fontL, al_color_name("red"), DISPLAY_X/2, (DISPLAY_Y-GSIZEY)/2, ALLEGRO_ALIGN_CENTER, "PAUSE");

    //Botones
    al_draw_filled_rectangle(DISPLAY_X/8, DISPLAY_Y/8, DISPLAY_X*7/8, DISPLAY_Y*3/8, al_color_name("black"));
    al_draw_filled_rectangle(DISPLAY_X/8, DISPLAY_Y*5/8, DISPLAY_X*7/8, DISPLAY_Y*7/8, al_color_name("black"));
    al_draw_text(Components->font, al_color_name("white"), DISPLAY_X/2, DISPLAY_Y/4, ALLEGRO_ALIGN_CENTER, "CONTINUE");
    al_draw_text(Components->font, al_color_name("white"), DISPLAY_X/2, DISPLAY_Y*3/4, ALLEGRO_ALIGN_CENTER, "MAIN MENU");

    if(Components->mouse_x > DISPLAY_X/8 && Components->mouse_x < DISPLAY_X*7/8){
        if(Components->mouse_y > DISPLAY_Y/8 && Components->mouse_y < DISPLAY_Y*3/8){
            al_draw_text(Components->font, al_color_name("yellow"), DISPLAY_X/2, DISPLAY_Y/4, ALLEGRO_ALIGN_CENTER, "CONTINUE");
            if(Components->leftClick){
                Components->leftClick = 0;
                Components->screen = GAME;
            }
        }
        else if(Components->mouse_y > DISPLAY_Y*5/8 && Components->mouse_y < DISPLAY_Y*7/8){
            al_draw_text(Components->font, al_color_name("yellow"), DISPLAY_X/2, DISPLAY_Y*3/4, ALLEGRO_ALIGN_CENTER, "MAIN MENU");
            if(Components->leftClick){
                Components->leftClick = false;
                Components->screen = MENU;
                Components->flagValue = false;
            }
        }
    }

}