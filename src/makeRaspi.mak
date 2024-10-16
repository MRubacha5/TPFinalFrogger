# MAKE DESACTUALIZADO. ACTUALIZAR CUANDO LO VAYAMOS A USAR

froggerRaspi: mainRaspi.o rana.o WorldCreate.o WorldInteract.o
	gcc -o froggerRaspi mainRaspi.o rana.o WorldCreate.o WorldInteract.o joydrv.o disdrv.o -D RASPI

mainRaspi.o: mainRaspi.c rana.h Objetos.h raspi.h
	gcc -c mainRaspi.c -Wall

rana.o: rana.c rana.h Objetos.h
	gcc -c rana.c -Wall

WorldCreate.o: WorldCreate.c rana.h Objetos.h
	gcc -c WorldCreate.c -Wall

WorldInteract.o: WorldInteract.c rana.h Objetos.h
	gcc -c WorldInteract.c -Wall
