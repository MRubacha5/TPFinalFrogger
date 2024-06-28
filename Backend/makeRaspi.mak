test: main.o Rana.o WorldCreate.o WorldInteract.o
	gcc -o test mainRaspi.o Rana.o WorldCreate.o WorldInteract.o joydrv.o disdrv.o
main.o: main.c Rana.h Objetos.h
	gcc -c main.c -Wall
Rana.o: Rana.c Rana.h Objetos.h
	gcc -c Rana.c -Wall
WorldCreate.o: WorldCreate.c Rana.h Objetos.h
	gcc -c WorldCreate.c -Wall
WorldInteract.o: WorldInteract.c Rana.h Objetos.h
	gcc -c WorldInteract.c -Wall
