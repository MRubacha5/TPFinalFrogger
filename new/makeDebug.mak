test: mainDebug.o Rana.o WorldCreate.o WorldInteract.o
	gcc -o test mainDebug.o Rana.o WorldCreate.o WorldInteract.o -g
mainDebug.o: mainDebug.c Rana.h Objetos.h
	gcc -c mainDebug.c -Wall -g
Rana.o: Rana.c Rana.h Objetos.h
	gcc -c Rana.c -Wall -g
WorldCreate.o: WorldCreate.c Rana.h Objetos.h
	gcc -c WorldCreate.c -Wall -g
WorldInteract.o: WorldInteract.c Rana.h Objetos.h
	gcc -c WorldInteract.c -Wall -g
