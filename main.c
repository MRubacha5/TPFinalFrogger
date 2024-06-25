/*codigo para allegro*/
#include "Objetos.h"
#include "Rana.h"
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_color.h>
#include <stdio.h>
#include <pthread.h>

#define GSIZE 20

#define DISPLAY_X (GSIZE*WIDTH)
#define DISPLAY_Y (GSIZE*HEIGHT)

void * buttonThread();

int do_exit = 0;

int main (void) {

		ALLEGRO_DISPLAY * display = NULL;
		ALLEGRO_FONT * font;
		ALLEGRO_EVENT_QUEUE * event_queue;
		ALLEGRO_TIMER * timer;

		pthread_t tid1;


		if(!al_init()){
		    	fprintf(stderr, "failed to initialize allegro!\n");
		    	return -1;
		}

	    display = al_create_display(DISPLAY_X, DISPLAY_Y);

	    if(!display){
	        	fprintf(stderr, "failed to create\n");
	        	return -1;
	    }

		if (!al_install_keyboard()) {
		    fprintf(stderr, "failed to initialize the keyboard!\n");
		    return -1;
		}

	    event_queue = al_create_event_queue();
	    if (!event_queue) {
	        printf("failed to create event_queue!\n");
	        al_destroy_display(display);
	        return -1;
	    }

	    timer = al_create_timer(1.0);
	    al_init_font_addon();
	    if(!timer){
	    	printf("failed to create timer!\n");
	    	al_destroy_display(display);
	    	return -1;
	    }

	    font = al_create_builtin_font();
	    if (!font) {
	    	printf("failed to create event_queue!\n");
	    	al_destroy_display(display);
	    	return -1;
	    }

	    if (!al_install_mouse()) {
	        printf("failed to initialize the mouse!\n");
	        return -1;
        }

	    if (!al_init_primitives_addon()) {
	    	printf("failed to initialize primitives!\n");
	        return -1;
        }

		al_register_event_source(event_queue, al_get_display_event_source(display));
		al_register_event_source(event_queue, al_get_timer_event_source(timer));
		al_register_event_source(event_queue, al_get_keyboard_event_source());
		al_register_event_source(event_queue, al_get_mouse_event_source());

		al_start_timer(timer);

		al_clear_to_color(al_color_name("black"));

		//pthread_create(&tid1, NULL, buttonThread, NULL);

		//pthread_join(tid1, NULL);

        linea_t * pl = CreateWorld(HEIGHT, WIDTH);
        rana_t rana = {.posx=HEIGHT/2, .posy=0, .vidas=3};

        for (int i = HEIGHT; i > 0; i--)
        {
            for (int c = 0; c < WIDTH; c++)
            {
                al_draw_filled_rectangle(snake.x, snake.y, snake.x + DISPLAY_X/B_SIZE - 2, snake.y + DISPLAY_Y/B_SIZE -2 , al_color_name("red"));
            }
            
        }
        al_flip_display();
		while(!do_exit){

			ALLEGRO_EVENT ev;

			if(al_get_next_event(event_queue, &ev)){

				if(ev.type == ALLEGRO_EVENT_TIMER){
					
		    	}
				else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
					do_exit = true;
		    	}
				else if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
					//leftClick = 1;
				}
				else if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP){
					//leftClick = 0;
				}
				else if(ev.type == ALLEGRO_EVENT_MOUSE_AXES){
					//x = (ev.mouse.x / (DISPLAY_X/COL)) + 1;
					//y = (ev.mouse.y / (DISPLAY_Y/ROW)) + 1;
		    	}
                else if(ev.type == ALLEGRO_EVENT_KEY_DOWN){

				switch(ev.keyboard.keycode){
				case ALLEGRO_KEY_DOWN:
					
					break;
				case ALLEGRO_KEY_UP:
					
					break;
				case ALLEGRO_KEY_LEFT:
					
					break;
				case ALLEGRO_KEY_RIGHT:
					
					break;

				}
			}
		    }
		}
        FreeWorldData(pl, HEIGHT);
		al_destroy_display(display);

	return 0;
}

void * buttonThread(){
	//detecta botones y cambia la direccion
	ALLEGRO_EVENT_QUEUE * button_queue;
	button_queue = al_create_event_queue();
	al_register_event_source(button_queue, al_get_keyboard_event_source());

	while(1){
		ALLEGRO_EVENT ev;
		if(al_get_next_event(button_queue, &ev)){
			
		}
	}

}


