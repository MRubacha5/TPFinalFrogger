/*codigo para allegro*/
#include "Objetos.h"
#include "Rana.h"
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_image.h>
#include <stdio.h>
#include <pthread.h>

#define GSIZE 50
#define FPS 60

#define DISPLAY_X (GSIZE*WIDTH)
#define DISPLAY_Y (GSIZE*HEIGHT)

void * line();

int do_exit = 0;
int keyPressed = 0;

linea_t * pl;
rana_t rana = {.posx=WIDTH/2, .posy=0, .vidas=3};

int tnum[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22};

int flag = 0;

int main (void) {

		ALLEGRO_DISPLAY * display = NULL;
		ALLEGRO_FONT * font;
		ALLEGRO_EVENT_QUEUE * event_queue;
		ALLEGRO_TIMER * timer;
		ALLEGRO_BITMAP * background;

		pthread_t tid[HEIGHT];


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

	    timer = al_create_timer(1.0/FPS);
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

		if(!al_init_image_addon()){
			printf("falied to inicialize image\n");
			return -1;
		}

		background = al_load_bitmap("background.jpg");

		al_register_event_source(event_queue, al_get_display_event_source(display));
		al_register_event_source(event_queue, al_get_timer_event_source(timer));
		al_register_event_source(event_queue, al_get_keyboard_event_source());
		al_register_event_source(event_queue, al_get_mouse_event_source());

		al_start_timer(timer);

		al_clear_to_color(al_color_name("black"));

		pl = CreateWorld(HEIGHT, WIDTH);

		//creo instancias de objetos
		//int i;
		/*
		for(i = 1 ; i < 19 ; i++){
			pthread_create(&(tid[i]), NULL, line, &(tnum[i]));
		}
		*/
		
		

		//pthread_join(tid1, NULL);

		/*
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
		*/
        al_draw_filled_ellipse(rana.posx*GSIZE + GSIZE/2, DISPLAY_Y-(rana.posy*GSIZE) - GSIZE/2, GSIZE/2, GSIZE/2, al_color_name("pink"));
        al_flip_display();
		while(!do_exit){

			ALLEGRO_EVENT ev;

			if(al_get_next_event(event_queue, &ev)){

				if(ev.type == ALLEGRO_EVENT_TIMER){
					al_draw_bitmap(background, 0, 0, 0);
					if(keyPressed){
                        printf("%d", rana.posy);
                    }
                    keyPressed = 0;
					/*
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
					*/
                    al_draw_filled_ellipse(rana.posx*GSIZE + GSIZE/2, DISPLAY_Y-(rana.posy*GSIZE) - GSIZE/2, GSIZE/2, GSIZE/2, al_color_name("pink"));

					
					for(int i = 0 ; i < HEIGHT ; i++){
						for(int c = 0 ; c < (pl+i)->cant_obj ; c++){
							int xvalue = ((((pl+i)->po)+c)->x) < 0 ? 0 : (((pl+i)->po)+c)->x ;
							int maxvalue = (((((pl+i)->po)+c)->x) + (pl+i)->size) > WIDTH ? WIDTH : (((((pl+i)->po)+c)->x) + (pl+i)->size);
							//printf("size: %d, x: %d, xval: %d, maxval: %d\n", (pl+i)->size, ((((pl+i)->po)+c)->x), xvalue, maxvalue);
							al_draw_filled_rectangle(xvalue * GSIZE, i*GSIZE, maxvalue * GSIZE, (i+1)*GSIZE,al_color_name("white"));
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

void * line(void*arg){
	//detecta botones y cambia la direccion
	linea_t * linea = pl+(*((int *)arg));
    int dir = (linea)->dir;
    int v = (linea)->v;
	int size = linea->size; 

	ALLEGRO_EVENT_QUEUE * queue;
    ALLEGRO_TIMER * timer = al_create_timer(1.0);
	queue = al_create_event_queue();
	al_register_event_source(queue, al_get_timer_event_source(timer));
    al_start_timer(timer);
    
	//printf("dir: %d, v: %d, size: %d, x: %d\n", dir, v, size, linea->po->x);

	while(1){
		ALLEGRO_EVENT ev;
		if(al_get_next_event(queue, &ev)){
            if(ev.type == ALLEGRO_EVENT_TIMER){
				ObjectSpawner(v*2, size, linea->cant_obj, linea);
                
				MoveObject(linea);	
            }
		}
	}
}


//que pasa cuando no hay objetos con el realloc. Hacer la logica de crear y borrar
//hacer que apenas arranque cree los obstaculos, como para que esten inicializados
