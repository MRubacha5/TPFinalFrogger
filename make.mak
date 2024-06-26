test: main.o Rana.o WorldCreate.o
	gcc -o test main.o Rana.o WorldCreate.o -lallegro -lallegro_primitives -lallegro_font -lallegro_color -lpthread -g

main.o: main.c Rana.h Objetos.h
	gcc -c main.c -Wall
Rana.o: Rana.c Rana.h Objetos.h
	gcc -c Rana.c -Wall
WorldCreate.o: WorldCreate.c Rana.h Objetos.h
	gcc -c WorldCreate.c -Wall
