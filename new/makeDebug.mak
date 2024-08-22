test: mainDebug.o world.o Rana.o
	gcc -o test mainDebug.o world.o Rana.o -g
mainDebug.o: mainDebug.c worldData.h 
	gcc -c mainDebug.c -Wall -g
world.o: world.c worldData.h
	gcc -c world.c -Wall -g
Rana.o: Rana.c Rana.h
	gcc -c Rana.c -Wall -g