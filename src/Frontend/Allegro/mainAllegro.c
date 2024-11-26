/*******************************************************************************
 * HEADERS
 ******************************************************************************/

#include "../../Backend/worldData.h"
#include "../../Backend/platformConfig.h"
#include "../../Backend/rana.h"
#include "AllegroSetup.h"

/*******************************************************************************
 * PROTOTIPOS DE FUNCIONES
 ******************************************************************************/
static void mouseHandler (allegroComponents_t * Components);

static void mouseHandler (allegroComponents_t * Components)
{
		if(Components->ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
			Components->do_exit = true;
		}
		else if(Components->ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
			Components->leftClick = true;
		}
		else if(Components->ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP){
			Components->leftClick = false;
		}
		else if(Components->ev.type == ALLEGRO_EVENT_MOUSE_AXES){
			Components->mouse_x = Components->ev.mouse.x;
			Components->mouse_y = Components->ev.mouse.y;
		}
}

int main (void) 
{

	/***************
	 * GAME SETUP  *
	 ***************/
	linea_t map[HEIGHT];
	rana_t rana;
	rana_t * pRana = &rana;
	assets_t assets = load_assets();
	allegroComponents_t Comps = initialize_allegro();
	worldData_t worldData;


	while(!Comps.do_exit){

		al_get_next_event(Comps.event_queue, &(Comps.ev));

		/***********************
		* FINITE STATE MACHINE *
		************************/
		switch (Comps.screen)
		{
		case MENU:
			menuScreen(assets, &Comps, map, pRana, &worldData);
			break;

		case HISCORE:
			hiScoreScreen(&Comps);
			break;

		case PAUSE:
			pauseScreen(&Comps);
			break;

		case GAME:
			inGame(&Comps, &assets, map, pRana, &worldData);
			break;
			
		case GAMEOVER:
			gameOverScreen(&Comps);
			break;
		}

		al_flip_display();

		mouseHandler(&Comps);
		
	}

	destroy_allegro(&Comps);
	destroy_assets(&assets);

	return 0;
}