test: mainDebug.o world.o rana.o
	gcc -o test mainDebug.o world.o rana.o -g
mainDebug.o: mainDebug.c worldData.h 
	gcc -c mainDebug.c -Wall -g
world.o: world.c worldData.h
	gcc -c world.c -Wall -g
rana.o: rana.c rana.h
	gcc -c rana.c -Wall -g