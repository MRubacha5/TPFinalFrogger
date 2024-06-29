test: mainDebug.o Rana.o WorldCreate.o WorldInteract.o
	gcc -o test mainDebug.o Rana.o WorldCreate.o WorldInteract.o
mainDebug.o: mainDebug.c Rana.h Objetos.h
	gcc -c mainDebug.c -Wall
Rana.o: Rana.c Rana.h Objetos.h
	gcc -c Rana.c -Wall
WorldCreate.o: WorldCreate.c Rana.h Objetos.h
	gcc -c WorldCreate.c -Wall
WorldInteract.o: WorldInteract.c Rana.h Objetos.h
	gcc -c WorldInteract.c -Wall
