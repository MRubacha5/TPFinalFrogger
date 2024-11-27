/*******************************************************************************
 * HEADERS
 ******************************************************************************/

#include "../../Backend/score.h"
#include "AllegroSetup.h"

/*******************************************************************************
 * PROTOTIPOS DE FUNCIONES
 ******************************************************************************/

static void drawTopScores (ALLEGRO_FONT * font, const char* name, const char* score, double nameX, double scoreX, double y);

static void drawTopScores (ALLEGRO_FONT * font, const char* name, const char* score, double nameX, double scoreX, double y)
{
	al_draw_text(font, al_color_name("white"), nameX, y, ALLEGRO_ALIGN_CENTER, name);
	al_draw_text(font, al_color_name("white"), scoreX, y, ALLEGRO_ALIGN_CENTER, score);
}


void hiScoreScreen (allegroComponents_t * Components)
{	
    // Fondo
    al_clear_to_color(al_color_name("black"));
    
    //Botones
    //al_draw_filled_rectangle(DISPLAY_X/8, DISPLAY_Y*6/8, DISPLAY_X*7/8, DISPLAY_Y, al_color_name("black"));
    al_draw_text(Components->font, al_color_name("white"), DISPLAY_X/2, DISPLAY_Y*7/8, ALLEGRO_ALIGN_CENTER, "MAIN MENU");

    if((Components->mouse_x > DISPLAY_X/8 && Components->mouse_x < DISPLAY_X*7/8) && (Components->mouse_y > DISPLAY_Y*6/8 && Components->mouse_y < DISPLAY_Y)){
        al_draw_text(Components->font, al_color_name("yellow"), DISPLAY_X/2, DISPLAY_Y*7/8, ALLEGRO_ALIGN_CENTER, "MAIN MENU");
        if(Components->leftClick){
            Components->leftClick = 0;
            Components->screen = MENU;
        
        }
    }

    al_draw_text(Components->fontL, al_color_name("white"), DISPLAY_X/2, DISPLAY_Y*0.5/8, ALLEGRO_ALIGN_CENTER, "HIGH SCORES");

    // Fetch top scores
    getTopScores("score.txt");

    // Imprimo los 10 scores
    for (int s = 0; s < 10; s++)
    {
        // Convierto el score a string
        char buffer[6]; 
        intToChar(6, buffer ,topScores[s]);
        
        drawTopScores(Components->font, topNames[s], buffer, DISPLAY_X*9/24, DISPLAY_X*7/12, DISPLAY_Y*(s+2.5)/15);
    }
    
    if(Components->key_pressed == ALLEGRO_KEY_ESCAPE)
    {
		Components->screen = MENU;
	}
}
