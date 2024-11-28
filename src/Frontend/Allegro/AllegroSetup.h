#ifndef ALLEGRO_SETUP_H
#define ALLEGRO_SETUP_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include<allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

#include "../../Backend/platformConfig.h"
#include "../../Backend/worldData.h"
#include "../../Backend/rana.h"

/*************
* CONSTANTES *
**************/
// Pantallas utilizadas en la FSM
enum {MENU, GAME, PAUSE, HISCORE, GAMEOVER};

#define DISPLAY_X (WIDTH)
#define DISPLAY_Y ((HEIGHT+4)*GSIZEY)

/*******************************************************************************
 * ESTRUCTURAS Y TIPOS DE DATOS
 ******************************************************************************/


typedef struct assets
{
    /*************** | BITMAPS | ******************************************/
    //Cars
    ALLEGRO_BITMAP * car1_bitmap;
    ALLEGRO_BITMAP * car2_bitmap;
    ALLEGRO_BITMAP * car3_bitmap;
    ALLEGRO_BITMAP * car4_bitmap;
    ALLEGRO_BITMAP * truck_bitmap;

    //Death animations
    ALLEGRO_BITMAP * crash1_bitmap;
    ALLEGRO_BITMAP * crash2_bitmap;
    ALLEGRO_BITMAP * crash3_bitmap;
    ALLEGRO_BITMAP * death_bitmap;
    ALLEGRO_BITMAP * drown1_bitmap;
    ALLEGRO_BITMAP * drown2_bitmap;
    ALLEGRO_BITMAP * drown3_bitmap;

    //Frog animations
    ALLEGRO_BITMAP * frogIdleBack_bitmap;
    ALLEGRO_BITMAP * frogIdleFwd_bitmap;
    ALLEGRO_BITMAP * frogIdleLeft_bitmap;
    ALLEGRO_BITMAP * frogIdleRight_bitmap;
    ALLEGRO_BITMAP * frogLeapBack_bitmap;
    ALLEGRO_BITMAP * frogLeapFwd_bitmap;
    ALLEGRO_BITMAP * frogLeapLeft_bitmap;
    ALLEGRO_BITMAP * frogLeapRight_bitmap;
    ALLEGRO_BITMAP * frogWin_bitmap;

    //Grass
    ALLEGRO_BITMAP * grassWinFrame_bitmap;
    ALLEGRO_BITMAP * grassWinSeparator_bitmap;
    ALLEGRO_BITMAP * purpleGrass_bitmap;

    //Logs
    ALLEGRO_BITMAP * logLeft_bitmap;
    ALLEGRO_BITMAP * logMiddle_bitmap;
    ALLEGRO_BITMAP * logRight_bitmap;

    //Title Text
    ALLEGRO_BITMAP * titleE_bitmap;
    ALLEGRO_BITMAP * titleF_bitmap;
    ALLEGRO_BITMAP * titleG_bitmap;
    ALLEGRO_BITMAP * titleO_bitmap;
    ALLEGRO_BITMAP * titleR_bitmap;

    // Variable que se va a utilizar para guardar el estado de la rana (direccion y animacion)
    ALLEGRO_BITMAP * frog_bitmap;

    /*************** | AUDIO | ******************************************/

    ALLEGRO_SAMPLE * leap;
    ALLEGRO_SAMPLE * crash;
    ALLEGRO_SAMPLE * drown;
    ALLEGRO_SAMPLE * homed;
    ALLEGRO_SAMPLE * extra_life;
    ALLEGRO_SAMPLE * time_running_out;
    ALLEGRO_SAMPLE * game_start;
    ALLEGRO_SAMPLE_INSTANCE * game_startInstance;
    ALLEGRO_SAMPLE * stage_clear;
    ALLEGRO_SAMPLE_INSTANCE * stage_clearInstance;
    ALLEGRO_SAMPLE * music;
    ALLEGRO_SAMPLE_INSTANCE * musicInstance;

}assets_t;

typedef struct allegroComponents
{
    ALLEGRO_FONT * font, * fontL;
	ALLEGRO_DISPLAY * display;
	ALLEGRO_EVENT_QUEUE * event_queue;
	ALLEGRO_TIMER * timer;
    ALLEGRO_EVENT ev;

    int mouse_x;
	int mouse_y;
	int leftClick;
	int fpsCounter;
	int screen;
    int do_exit;

    int keycode; //Allegro Constant keycode value
    unsigned int flagValue; //Easter Egg

} allegroComponents_t;

/*******************************************************************************
 * PROTOTIPOS DE FUNCIONES
 ******************************************************************************/

/**
* @brief Inicializa todos los componentes de Allegro necesarios
* @return Estructura que contiene todas las variables necesarias para operar con Allegro
*/
allegroComponents_t initialize_allegro (void);

/**
* @brief Libera de forma segura toda la memoria reservada por initialize_allegro. Tambien desinstala los modulos
* @param Components Puntero a los componentes que se utilizaron durante la ejecucion
*/
void destroy_allegro (allegroComponents_t* Components);

/**
* @brief Carga todos los bitmaps, la fuente de texto y los samples de audio que se utilizaran
* @return Estructura que contiene todos los assets que se utilizan
*/
assets_t load_assets (void);

/**
* @brief Procesa todos los inputs y actualiza sus valores para que el resto de las funciones tengan acceso.
* @param Components Los componentes que se utilicen durante la ejecucion
* @param
*/
void inputHandler(allegroComponents_t * Components);

/**
* @brief Libera de forma segura toda la memoria utilizada por los assets
* @param assets Puntero a los assets que se utilizaron
*/
void destroy_assets (assets_t* assets);

// PANTALLAS DEL JUEGO
void menuScreen (assets_t assets, allegroComponents_t * Components, linea_t * map, rana_t * pRana, worldData_t * pWorldData);
void pauseScreen (allegroComponents_t * Components);
void inGame (allegroComponents_t * Comp, assets_t * assets, linea_t * map, rana_t * pRana, worldData_t * pWD);
void hiScoreScreen (allegroComponents_t * Components);
void gameOverScreen (allegroComponents_t * Components);

#endif //ALLEGRO_SETUP_H
