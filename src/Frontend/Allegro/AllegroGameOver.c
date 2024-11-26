
/*******************************************************************************
 * HEADERS
 ******************************************************************************/

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include<allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_image.h>

#include "../../Backend/platformConfig.h"
#include "AllegroSetup.h"
#include "../../Backend/score.h"

void gameOverScreen (allegroComponents_t * Components)
{
    al_clear_to_color(al_color_name("black"));

    al_draw_text(Components->fontL, al_color_name("white"), DISPLAY_X/2.0, DISPLAY_Y/16, ALLEGRO_ALIGN_CENTER, "GAME OVER");
    al_draw_text(Components->font,al_color_name("white"),(DISPLAY_X/2), (HEIGHT/4)*GSIZEY,ALLEGRO_ALIGN_CENTRE,"FINAL SCORE:");
    al_draw_textf(Components->fontL, al_color_name("white"), DISPLAY_X/2.0,(HEIGHT/3)*GSIZEY, ALLEGRO_ALIGN_CENTRE, scorestr);
    
    // If the game resulted in a Top 10 score
    if (IsMax(currentScore,"score.txt"))
    {
        al_draw_text(Components->font,al_color_name("white"),(DISPLAY_X/2), (HEIGHT*3/5)*GSIZEY,ALLEGRO_ALIGN_CENTRE,"PLEASE ENTER YOUR NAME:");
        al_draw_text(Components->fontL,al_color_name("white"),(DISPLAY_X/2), (HEIGHT*5/6)*GSIZEY,ALLEGRO_ALIGN_CENTRE,name);
        al_draw_text(Components->font, al_color_name("white"), DISPLAY_X/2, DISPLAY_Y*7/8, ALLEGRO_ALIGN_CENTER, "SUBMIT");

        if((Components->mouse_x > DISPLAY_X/8 && Components->mouse_x < DISPLAY_X*7/8) && (Components->mouse_y > DISPLAY_Y*6/8 && Components->mouse_y < DISPLAY_Y)){
            al_draw_text(Components->font, al_color_name("yellow"), DISPLAY_X/2, DISPLAY_Y*7/8, ALLEGRO_ALIGN_CENTER, "SUBMIT");
            if(Components->leftClick){
                Components->leftClick = 0;
                max_scores(currentScore,"score.txt",name);
                Components->screen = HISCORE;

                //Reset input default for next time
                for(int n = 0; n < 3; n++){
                    name[n] = 'A';
                }
            }
        }
        for (int f = -1; f < 2; f++)
        {
            al_draw_text(Components->fontL,al_color_name("white"),(DISPLAY_X/2)+f*GSIZEX, DISPLAY_Y*6/11,ALLEGRO_ALIGN_CENTRE,"^");
            al_draw_text(Components->fontL,al_color_name("white"),(DISPLAY_X/2)+f*GSIZEX, DISPLAY_Y*7/11,ALLEGRO_ALIGN_CENTRE,"v");
            if((Components->mouse_x > (DISPLAY_X/2)+(f-0.5)*GSIZEX && Components->mouse_x < (DISPLAY_X/2)+(f+0.5)*GSIZEX))
            {
                if(Components->mouse_y > DISPLAY_Y*6/11 && Components->mouse_y < DISPLAY_Y*6/11+GSIZEY)
                {
                    
                    al_draw_text(Components->fontL,al_color_name("yellow"),(DISPLAY_X/2)+f*GSIZEX, DISPLAY_Y*6/11,ALLEGRO_ALIGN_CENTRE,"^");
                    if(Components->leftClick){
                        Components->leftClick = 0;
                        name[f+1] = (name[f+1] == 'Z')? 'A':name[f+1]+1;
                    }
                }

                if(Components->mouse_y > DISPLAY_Y*7/11 && Components->mouse_y < DISPLAY_Y*7/11+GSIZEY)
                {
                    al_draw_text(Components->fontL,al_color_name("yellow"),(DISPLAY_X/2)+f*GSIZEX, DISPLAY_Y*7/11,ALLEGRO_ALIGN_CENTRE,"v");
                    if(Components->leftClick){
                        Components->leftClick = 0;
                        name[f+1] = (name[f+1] == 'A')? 'Z':name[f+1]-1;
                    }
                }
            }
        }
        
    }
    else // Not top score
    {
        al_draw_text(Components->font, al_color_name("white"), DISPLAY_X/2, DISPLAY_Y*7/8, ALLEGRO_ALIGN_CENTER, "MAIN MENU");

        if((Components->mouse_x > DISPLAY_X/8 && Components->mouse_x < DISPLAY_X*7/8) && (Components->mouse_y > DISPLAY_Y*6/8 && Components->mouse_y < DISPLAY_Y)){
            al_draw_text(Components->font, al_color_name("yellow"), DISPLAY_X/2, DISPLAY_Y*7/8, ALLEGRO_ALIGN_CENTER, "MAIN MENU");
            if(Components->leftClick){
                Components->leftClick = 0;
                Components->screen = MENU;
            }
        }
    }
	
}