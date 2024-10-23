froggerRaspi:  mainRaspi.o rana.o world.o
	gcc -o froggerRaspi mainRaspi.o rana.o world.o joydrv.o disdrv.o -D RASPI

mainRaspi.o: mainRaspi.c rana.h movement.h platformConfig.h score.h worldData.h
	gcc -c mainRaspi.c -Wall -D RASPI

rana.o: rana.c rana.h movement.h platformConfig.h score.h worldData.h
	gcc -c rana.c -Wall -D RASPI

world.o: world.c rana.h movement.h platformConfig.h worldData.h
	gcc -c world.c -Wall -D RASPI
