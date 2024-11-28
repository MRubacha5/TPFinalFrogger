/*******************************************************************************
 * HEADERS
 ******************************************************************************/

#include "../../Backend/platformConfig.h"
#include "AllegroSetup.h"
#include <stdio.h>
allegroComponents_t initialize_allegro (void)
{
    if(!al_init())
    {
        fprintf(stderr, "failed to initialize allegro!\n");
        
	}
    if (!al_install_keyboard()) 
    {
		fprintf(stderr, "failed to initialize the keyboard!\n");
		
	}
    if (!al_init_ttf_addon()) 
    {
		fprintf(stderr, "failed to initialize the ttf addon!\n");
		
	}
    if (!al_init_font_addon()) 
    {
		fprintf(stderr, "failed to initialize the font addon!\n");
		
	}
    if (!al_install_mouse()) 
    {
		fprintf(stderr, "failed to initialize the mouse!\n");
		
	}
    if (!al_init_primitives_addon()) 
    {
		fprintf(stderr, "failed to initialize the primitives addon!\n");
		
	}
     if (!al_init_image_addon()) 
    {
		fprintf(stderr, "failed to initialize the image addon!\n");
		
	}
    if(!al_install_audio())
    {
        fprintf(stderr, "failed to initialize audio module!\n");
        
	}
    if(!al_init_acodec_addon())
    {
        fprintf(stderr, "failed to initialize audio codec addon!\n");
        
    }

    allegroComponents_t Components =
    {
        .font = al_load_font("assets/Sprites/arcadeFont.ttf",GSIZEX*0.5,0),
        .fontL = al_load_font("assets/Sprites/arcadeFont.ttf",GSIZEX,0),
        .event_queue = al_create_event_queue(),
        .display = al_create_display(DISPLAY_X, DISPLAY_Y),
        .timer = al_create_timer(1.0/FPS),

        .mouse_x = 0,
	    .mouse_y = 0,
	    .leftClick = 0,
	    .fpsCounter = 0,
	    .screen = MENU,
        .do_exit = 0
    };

    al_start_timer(Components.timer);    

    al_register_event_source(Components.event_queue, al_get_display_event_source(Components.display));
    al_register_event_source(Components.event_queue, al_get_timer_event_source(Components.timer));
    al_register_event_source(Components.event_queue, al_get_keyboard_event_source());
    al_register_event_source(Components.event_queue, al_get_mouse_event_source());


    return Components;
}

void destroy_allegro (allegroComponents_t* Components)
{
    al_destroy_display(Components->display);
    al_destroy_event_queue(Components->event_queue);
    al_destroy_font(Components->font);
    al_destroy_font(Components->fontL);
    al_destroy_timer(Components->timer);
    al_uninstall_audio();
    al_uninstall_keyboard();
    al_uninstall_mouse();
}

assets_t load_assets (void)
{
    al_reserve_samples(10);
    assets_t assets = 
    {
        //Cars
		.car1_bitmap = al_load_bitmap("assets/Sprites/car1.png"),
		.car2_bitmap = al_load_bitmap("assets/Sprites/car2.png"),
		.car3_bitmap = al_load_bitmap("assets/Sprites/car3.png"),
		.car4_bitmap = al_load_bitmap("assets/Sprites/car4.png"),
		.truck_bitmap = al_load_bitmap("assets/Sprites/truck.png"),

		//Death animations
		.crash1_bitmap = al_load_bitmap("assets/Sprites/crash1.png"),
		.crash2_bitmap = al_load_bitmap("assets/Sprites/crash2.png"),
		.crash3_bitmap = al_load_bitmap("assets/Sprites/crash3.png"),
		.death_bitmap = al_load_bitmap("assets/Sprites/death.png"),
		.drown1_bitmap = al_load_bitmap("assets/Sprites/drown1.png"),
		.drown2_bitmap = al_load_bitmap("assets/Sprites/drown2.png"),
		.drown3_bitmap = al_load_bitmap("assets/Sprites/drown3.png"),

		//Frog animations
		.frogIdleBack_bitmap = al_load_bitmap("assets/Sprites/frogIdleBack.png"),
		.frogIdleFwd_bitmap = al_load_bitmap("assets/Sprites/frogIdleFwd.png"),
		.frogIdleLeft_bitmap = al_load_bitmap("assets/Sprites/frogIdleLeft.png"),
		.frogIdleRight_bitmap = al_load_bitmap("assets/Sprites/frogIdleRight.png"),
		.frogLeapBack_bitmap = al_load_bitmap("assets/Sprites/frogLeapBack.png"),
		.frogLeapFwd_bitmap = al_load_bitmap("assets/Sprites/frogLeapFwd.png"),
		.frogLeapLeft_bitmap = al_load_bitmap("assets/Sprites/frogLeapLeft.png"),
		.frogLeapRight_bitmap = al_load_bitmap("assets/Sprites/frogLeapRight.png"),
		.frogWin_bitmap = al_load_bitmap("assets/Sprites/frogWin.png"),

		//Grass
		.grassWinFrame_bitmap = al_load_bitmap("assets/Sprites/grassWinFrame.png"),
		.grassWinSeparator_bitmap = al_load_bitmap("assets/Sprites/grassWinSeparator.png"),
		.purpleGrass_bitmap = al_load_bitmap("assets/Sprites/purpleGrass.png"),

		//Logs
		.logLeft_bitmap = al_load_bitmap("assets/Sprites/logLeft.png"),
		.logMiddle_bitmap = al_load_bitmap("assets/Sprites/logMiddle.png"),
		.logRight_bitmap = al_load_bitmap("assets/Sprites/logRight.png"),

		//Title Text
		.titleE_bitmap = al_load_bitmap("assets/Sprites/titleE.png"),
		.titleF_bitmap = al_load_bitmap("assets/Sprites/titleF.png"),
		.titleG_bitmap = al_load_bitmap("assets/Sprites/titleG.png"),
		.titleO_bitmap = al_load_bitmap("assets/Sprites/titleO.png"),
		.titleR_bitmap = al_load_bitmap("assets/Sprites/titleR.png"),

		.frog_bitmap = assets.frogIdleFwd_bitmap,

        //SFX
		.leap = al_load_sample("assets/Audio/sound-frogger-hop.wav"),
		.crash = al_load_sample("assets/Audio/sound-frogger-squash.wav"),
		.drown = al_load_sample("assets/Audio/sound-frogger-drown.wav"),
		.homed = al_load_sample("assets/Audio/sound-frogger-homed.wav"),
        .extra_life = al_load_sample("assets/Audio/sound-frogger-extra-life.wav"),
        .time_running_out = al_load_sample("assets/Audio/sound-frogger-time-running-out.wav"),
        .stage_clear = al_load_sample("assets/Audio/Stage-Clear.wav"),
        .stage_clearInstance = al_create_sample_instance(assets.stage_clear),
        .game_start = al_load_sample("assets/Audio/game_start.wav"),
        .game_startInstance = al_create_sample_instance(assets.game_start),

        //Music
		.music = al_load_sample("assets/Audio/Main-Theme-Fixed.wav"),
		.musicInstance = al_create_sample_instance(assets.music)
    };

    al_set_sample_instance_playmode(assets.musicInstance, ALLEGRO_PLAYMODE_LOOP);
    
    return assets;
}

void destroy_assets (assets_t* assets)
{
    al_destroy_bitmap(assets->car1_bitmap);
    al_destroy_bitmap(assets->car2_bitmap);
    al_destroy_bitmap(assets->car3_bitmap);
    al_destroy_bitmap(assets->car4_bitmap);
    al_destroy_bitmap(assets->truck_bitmap);
    al_destroy_bitmap(assets->crash1_bitmap);
    al_destroy_bitmap(assets->crash2_bitmap);
    al_destroy_bitmap(assets->crash3_bitmap);
    al_destroy_bitmap(assets->death_bitmap);
    al_destroy_bitmap(assets->drown1_bitmap);
    al_destroy_bitmap(assets->drown2_bitmap);
    al_destroy_bitmap(assets->drown3_bitmap);
    al_destroy_bitmap(assets->frogIdleFwd_bitmap);
    al_destroy_bitmap(assets->frogLeapFwd_bitmap);
    al_destroy_bitmap(assets->frogIdleBack_bitmap);
    al_destroy_bitmap(assets->frogLeapBack_bitmap);
    al_destroy_bitmap(assets->frogIdleLeft_bitmap);
    al_destroy_bitmap(assets->frogLeapLeft_bitmap);
    al_destroy_bitmap(assets->frogIdleRight_bitmap);
    al_destroy_bitmap(assets->frogLeapRight_bitmap);
    al_destroy_bitmap(assets->frogWin_bitmap);
    al_destroy_bitmap(assets->grassWinFrame_bitmap);
    al_destroy_bitmap(assets->grassWinSeparator_bitmap);
    al_destroy_bitmap(assets->purpleGrass_bitmap);
    al_destroy_bitmap(assets->logRight_bitmap);
    al_destroy_bitmap(assets->logLeft_bitmap);
    al_destroy_bitmap(assets->logMiddle_bitmap);
    al_destroy_bitmap(assets->titleE_bitmap);
    al_destroy_bitmap(assets->titleF_bitmap);
    al_destroy_bitmap(assets->titleG_bitmap);
    al_destroy_bitmap(assets->titleO_bitmap);
    al_destroy_bitmap(assets->titleR_bitmap);

    al_destroy_sample(assets->crash);
    al_destroy_sample(assets->drown);
    al_destroy_sample(assets->homed);
    al_destroy_sample(assets->leap);
    al_destroy_sample(assets->time_running_out);
    al_destroy_sample(assets->stage_clear);
    al_destroy_sample_instance(assets->stage_clearInstance);
    al_destroy_sample(assets->game_start);
    al_destroy_sample_instance(assets->game_startInstance);
    al_destroy_sample(assets->music);
    al_destroy_sample_instance(assets->musicInstance);

}