test: main.o  score.o world.o Rana.o
	gcc -o test main.o world.o score.o Rana.o -lallegro -lallegro_primitives -lallegro_font -lallegro_color -lpthread -lallegro_image -g

main.o: main.c worldData.h score.h
	gcc -c main.c -Wall

world.o: world.c worldData.h
	gcc -c world.c -Wall
	
score.o: score.c score.h
	gcc -c score.c -Wall

Rana.o: Rana.c Rana.h
	gcc -c Rana.c -Wall -g
