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

#define GSIZE 85

#define DISPLAY_X (GSIZE*WIDTH)
#define DISPLAY_Y (GSIZE*HEIGHT)

void * line1();

int do_exit = 0;
int keyPressed = 0;

linea_t * pl;
rana_t rana = {.posx=WIDTH/2, .posy=0, .vidas=3};

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

		pthread_create(&tid1, NULL, line1, NULL);

		//pthread_join(tid1, NULL);
        pl = CreateWorld(HEIGHT, WIDTH);

        for (int i = 0; i < HEIGHT; i++)
        {
            for (int c = 0; c < WIDTH; c++)
            {
                if(*(((pl+i)->p_linea)+c)){
                    al_draw_filled_rectangle(c*GSIZE, i*GSIZE, (c+1)*GSIZE, (i+1)*GSIZE , al_color_name("green"));
                }
                else{
                    al_draw_filled_rectangle(c*GSIZE, i*GSIZE, (c+1)*GSIZE, (i+1)*GSIZE , al_color_name("blue"));
                }
                
            }
            
        }
        al_draw_filled_ellipse(rana.posx*GSIZE + GSIZE/2, DISPLAY_Y-(rana.posy*GSIZE) - GSIZE/2, GSIZE/2, GSIZE/2, al_color_name("pink"));
        al_flip_display();
		while(!do_exit){

			ALLEGRO_EVENT ev;

			if(al_get_next_event(event_queue, &ev)){

				if(ev.type == ALLEGRO_EVENT_TIMER){
					if(keyPressed){
                        printf("%d", rana.posy);
                    }
                    keyPressed = 0;
                    for (int i = 0; i < HEIGHT; i++)
                    {
                        for (int c = 0; c < WIDTH; c++)
                        {
                            if(*(((pl+i)->p_linea)+c)){
                                al_draw_filled_rectangle(c*GSIZE, i*GSIZE, (c+1)*GSIZE, (i+1)*GSIZE , al_color_name("green"));
                            }
                            else{
                                al_draw_filled_rectangle(c*GSIZE, i*GSIZE, (c+1)*GSIZE, (i+1)*GSIZE , al_color_name("blue"));
                            }
                            
                        }
                        
                    }
                    al_draw_filled_ellipse(rana.posx*GSIZE + GSIZE/2, DISPLAY_Y-(rana.posy*GSIZE) - GSIZE/2, GSIZE/2, GSIZE/2, al_color_name("pink"));

                    for(int i = 0 ; i < HEIGHT ; i++){
                        for(int c = 0 ; c < (pl+i)->cant_obj ; c++){
                            al_draw_filled_rectangle(((((pl+i)->po)+c)->x) *GSIZE, i*GSIZE, (((((pl+i)->po)+c)->x) + ((((pl+i)->po)+c)->size)) * GSIZE, (i+1)*GSIZE,al_color_name("brown"));
                        }
                    }
                    al_flip_display();
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
                            MoveRana(rana, DOWN);
                            keyPressed = 1;
                            break;
                        case ALLEGRO_KEY_UP:
                            MoveRana(rana, UP);
                            keyPressed = 1;
                            break;
                        case ALLEGRO_KEY_LEFT:
                            MoveRana(rana, LEFT);
                            keyPressed = 1;
                            break;
                        case ALLEGRO_KEY_RIGHT:
                            MoveRana(rana, RIGHT);
                            keyPressed = 1;
                            break;

                    }
			    }
		    }
		}
        FreeWorldData(pl, HEIGHT);
		al_destroy_display(display);

	return 0;
}

void * line1(){
	//detecta botones y cambia la direccion
    int dir = (pl+3)->dir;
    int v = (pl+3)->v;
    int time_buffer = 0;
    int spawned = 0;
	ALLEGRO_EVENT_QUEUE * queue;
    ALLEGRO_TIMER * timer = al_create_timer(1.0/v);
	queue = al_create_event_queue();
	al_register_event_source(queue, al_get_timer_event_source(timer));
    al_start_timer(timer);
    CreateObject(pl+3);
    
	while(1){
		ALLEGRO_EVENT ev;
		if(al_get_next_event(queue, &ev)){
            if(ev.type == ALLEGRO_EVENT_TIMER){
                
                MoveObject(pl+3);
            
                switch (dir)
                {
                case DER:
                    if((pl+3)->po->x > WIDTH){
                        DestroyObject(pl+3);
                        printf("destory");
                    }
                    break;
                case IZQ:
                    if((pl+3)->po->x + (pl+3)->po->size < 0){
                        DestroyObject(pl+3);
                        printf("destory");
                    }
                }
            }
		}
	}
}


//que pasa cuando no hay objetos con el realloc. Hacer la logica de crear y borrar
