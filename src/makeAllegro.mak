test: main.o  score.o world.o rana.o
	gcc -o test main.o world.o score.o rana.o -lallegro -lallegro_primitives -lallegro_font -lallegro_color -lpthread -lallegro_image -g

main.o: main.c worldData.h score.h movement.h
	gcc -c main.c -Wall

world.o: world.c worldData.h movement.h
	gcc -c world.c -Wall
	
score.o: score.c score.h
	gcc -c score.c -Wall

rana.o: rana.c rana.h movement.h
	gcc -c rana.c -Wall -g
