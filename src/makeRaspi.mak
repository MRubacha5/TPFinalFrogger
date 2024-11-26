froggerRaspi:  mainRaspi.o rana.o world.o score.o RasPiScreens.o
	gcc -o froggerRaspi mainRaspi.o rana.o world.o joydrv.o disdrv.o score.o RasPiScreens.o -D RASPI -g -lSDL2 -lSDL2_mixer

mainRaspi.o: mainRaspi.c rana.h movement.h platformConfig.h score.h worldData.h
	gcc -c mainRaspi.c -Wall -D RASPI

rana.o: rana.c rana.h movement.h platformConfig.h score.h worldData.h
	gcc -c rana.c -Wall -D RASPI

world.o: world.c rana.h movement.h platformConfig.h worldData.h
	gcc -c world.c -Wall -D RASPI

score.o: score.c score.h
	gcc -c score.c -Wall -D RASPI

RasPiScreens.o: Frontend/RasPi/RasPiScreens.c
	gcc -c Frontend/RasPi/RasPiScreens.c -Wall -D RASPI