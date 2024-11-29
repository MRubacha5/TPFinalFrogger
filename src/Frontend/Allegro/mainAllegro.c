/*******************************************************************************
 * HEADERS
 ******************************************************************************/

#include "../../Backend/worldData.h"
#include "../../Backend/platformConfig.h"
#include "../../Backend/rana.h"
#include "AllegroSetup.h"

int main (void) 
{

	/***************
	 * GAME SETUP  *
	 ***************/
	linea_t map[HEIGHT];
	rana_t rana;
	rana_t * pRana = &rana;
 	allegroComponents_t Comps = initialize_allegro();
	assets_t assets = load_assets();
	worldData_t worldData;

	al_play_sample_instance(assets.game_startInstance);

	while(!Comps.do_exit){

		/***********************
		* FINITE STATE MACHINE *
		************************/
		if(al_get_next_event(Comps.event_queue, &Comps.ev)) 
		{
			if(Comps.ev.type == ALLEGRO_EVENT_TIMER)//only update game ever timer tick
			{
				switch (Comps.screen)
				{
				case MENU:
					menuScreen(assets, &Comps, map, pRana, &worldData);
					break;

				case HISCORE:
					hiScoreScreen(&Comps);
					break;

				case PAUSE:
					pauseScreen(&Comps, assets);
					break;

				case GAME:
					inGame(&Comps, &assets, map, pRana, &worldData);
					break;
					
				case GAMEOVER:
					gameOverScreen(&Comps);
					break;
				}

				al_flip_display();
			}
			else
			{
				inputHandler(&Comps);
			}	
		}
	}
	
	destroy_assets(&assets);
	destroy_allegro(&Comps);

	return 0;
}