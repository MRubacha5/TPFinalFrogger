# MAKE DESACTUALIZADO. ACTUALIZAR CUANDO LO VAYAMOS A USAR

test: mainRaspi.o rana.o WorldCreate.o WorldInteract.o
	gcc -o test mainRaspi.o rana.o WorldCreate.o WorldInteract.o joydrv.o disdrv.o

mainRaspi.o: mainRaspi.c rana.h Objetos.h
	gcc -c mainRaspi.c -Wall

rana.o: rana.c rana.h Objetos.h
	gcc -c rana.c -Wall

WorldCreate.o: WorldCreate.c rana.h Objetos.h
	gcc -c WorldCreate.c -Wall

WorldInteract.o: WorldInteract.c rana.h Objetos.h
	gcc -c WorldInteract.c -Wall
