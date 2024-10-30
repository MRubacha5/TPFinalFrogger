froggerAllegro: main.o  score.o world.o rana.o
	gcc -o froggerAllegro main.o world.o score.o rana.o -lallegro -lallegro_primitives -lallegro_ttf -lallegro_font -lallegro_color -lpthread -lallegro_image -lallegro_acodec -lallegro_audio -g

main.o: main.c worldData.h score.h movement.h platformConfig.h
	gcc -c main.c -Wall -D ALLEGRO

world.o: world.c worldData.h movement.h platformConfig.h
	gcc -c world.c -Wall -D ALLEGRO
	
score.o: score.c score.h
	gcc -c score.c -Wall -D ALLEGRO

rana.o: rana.c rana.h movement.h platformConfig.h
	gcc -c rana.c -Wall -g -D ALLEGRO
