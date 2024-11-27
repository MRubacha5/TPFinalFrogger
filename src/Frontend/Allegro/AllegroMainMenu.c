/*******************************************************************************
 * HEADERS
 ******************************************************************************/

#include "../../Backend/platformConfig.h"
#include "../../Backend/worldData.h"
#include "../../Backend/rana.h"
#include "AllegroSetup.h"

void menuScreen (assets_t assets, allegroComponents_t * Components, linea_t * map, rana_t * pRana, worldData_t * pWorldData)
{
    // Fondo
    al_clear_to_color(al_color_name("darkblue"));
    
    // Letras de FROGGER
    al_draw_scaled_bitmap(assets.titleF_bitmap,0,0,32,32,
                GSIZEX*1.7, 2*GSIZEY, GSIZEX*3.0,GSIZEY*3.0,0);
    al_draw_scaled_bitmap(assets.titleR_bitmap,0,0,32,32,
                GSIZEX*3.2, 2*GSIZEY, GSIZEX*3.0,GSIZEY*3.0,0);
    al_draw_scaled_bitmap(assets.titleO_bitmap,0,0,32,32,
                GSIZEX*4.7, 2*GSIZEY, GSIZEX*3.0,GSIZEY*3.0,0);
    al_draw_scaled_bitmap(assets.titleG_bitmap,0,0,32,32,
                GSIZEX*6.2, 2*GSIZEY, GSIZEX*3.0,GSIZEY*3.0,0);
    al_draw_scaled_bitmap(assets.titleG_bitmap,0,0,32,32,
                GSIZEX*7.7, 2*GSIZEY, GSIZEX*3.0,GSIZEY*3.0,0);
    al_draw_scaled_bitmap(assets.titleE_bitmap,0,0,32,32,
                GSIZEX*9.2, 2*GSIZEY, GSIZEX*3.0,GSIZEY*3.0,0);
    al_draw_scaled_bitmap(assets.titleR_bitmap,0,0,32,32,
                GSIZEX*10.7, 2*GSIZEY, GSIZEX*3.0,GSIZEY*3.0,0);

    //Easter Egg
    if (Components->flagValue == 2)
    {
        al_play_sample(assets.extra_life,1,0,1,ALLEGRO_PLAYMODE_ONCE,0);
        Components->flagValue--;
    }
    
    // Botones
    al_draw_text(Components->fontL, al_color_name("white"), DISPLAY_X/2, DISPLAY_Y*4.0/8, ALLEGRO_ALIGN_CENTER, "START");
    al_draw_text(Components->fontL, al_color_name("white"), DISPLAY_X/2, DISPLAY_Y*5.0/8, ALLEGRO_ALIGN_CENTER, "HIGH SCORES");
    al_draw_text(Components->fontL, al_color_name("white"), DISPLAY_X/2, DISPLAY_Y*6.0/8, ALLEGRO_ALIGN_CENTER, "QUIT");

    // Los Botones cambian de color cuando el mouse esta por encima
    if(Components->mouse_x > DISPLAY_X/8 && Components->mouse_x < DISPLAY_X*7/8)
    {
        if(Components->mouse_y > DISPLAY_Y*7.0/16 && Components->mouse_y < DISPLAY_Y*8.5/16+GSIZEY)
        {
            al_draw_text(Components->fontL, al_color_name("yellow"), DISPLAY_X/2, DISPLAY_Y*4.0/8, ALLEGRO_ALIGN_CENTER, "START");
            if(Components->leftClick)
            {
                Components->leftClick = false;
                Components->screen = GAME;
                gameStart(map, pWorldData);
                spawnRana(pRana);
                if (Components->flagValue) //Easter Egg
                {
                    pRana->vidas += 7;
                    Components->flagValue = false;
                }
            } 
        }
        else if(Components->mouse_y > DISPLAY_Y*8.5/16+GSIZEY && Components->mouse_y < DISPLAY_Y*9.5/16+2*GSIZEY)
        {
            al_draw_text(Components->fontL, al_color_name("yellow"), DISPLAY_X/2, DISPLAY_Y*5.0/8, ALLEGRO_ALIGN_CENTER, "HIGH SCORES");
            if(Components->leftClick)
            {
                Components->leftClick = false;
                Components->screen = HISCORE;
                Components->flagValue = false;
            }
        }
        else if(Components->mouse_y > DISPLAY_Y*9.5/16+2*GSIZEY && Components->mouse_y < DISPLAY_Y*10.5/16+3*GSIZEY)
        {
            al_draw_text(Components->fontL, al_color_name("yellow"), DISPLAY_X/2, DISPLAY_Y*6.0/8, ALLEGRO_ALIGN_CENTER, "QUIT");
            if(Components->leftClick)
            {
                Components->leftClick = false;
                Components->do_exit = true;
                Components->flagValue = false;
            }
        }
    }
}



