test: mainDebug.o world.o rana.o
	gcc -o test mainDebug.o world.o rana.o -g

mainDebug.o: mainDebug.c worldData.h movement.h
	gcc -c mainDebug.c -Wall -g

world.o: world.c worldData.h movement.h
	gcc -c world.c -Wall -g

rana.o: rana.c rana.h movement.h
	gcc -c rana.c -Wall -g