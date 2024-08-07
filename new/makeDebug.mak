test: mainDebug.o world.o
	gcc -o test mainDebug.o world.o -g
mainDebug.o: mainDebug.c worldData.h
	gcc -c mainDebug.c -Wall -g
world.o: world.c worldData.h
	gcc -c world.c -Wall -g
