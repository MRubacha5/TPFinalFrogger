# Flags
CC = gcc
CFLAGS = -c -Wall -Wextra -g -D RASPI

LIB = src/Frontend/RasPi/joydrv.o src/Frontend/RasPi/disdrv.o

RASPI_DIR = src/Frontend/RasPi
BACKEND_DIR = src/Backend


froggerRaspi: mainRaspi.o rana.o world.o score.o RasPiScreens.o RaspiInit.o RaspiMainMenu.o RaspiPause.o RaspiInGame.o RaspiGameover.o RaspiHiscore.o $(LIB)
	$(CC) -o froggerRaspi mainRaspi.o rana.o world.o score.o RasPiScreens.o RaspiInit.o RaspiMainMenu.o RaspiPause.o RaspiInGame.o RaspiGameover.o RaspiHiscore.o $(LIB) -lSDL2 -lSDL2_mixer


mainRaspi.o: $(RASPI_DIR)/mainRaspi.c $(RASPI_DIR)/RaspiData.h | 
	$(CC) $(CFLAGS) $(RASPI_DIR)/mainRaspi.c -o mainRaspi.o


rana.o: $(BACKEND_DIR)/rana.c $(BACKEND_DIR)/rana.h $(BACKEND_DIR)/movement.h $(BACKEND_DIR)/platformConfig.h $(BACKEND_DIR)/score.h $(BACKEND_DIR)/worldData.h | 
	$(CC) $(CFLAGS) $(BACKEND_DIR)/rana.c -o rana.o


world.o: $(BACKEND_DIR)/world.c $(BACKEND_DIR)/rana.h $(BACKEND_DIR)/movement.h $(BACKEND_DIR)/platformConfig.h $(BACKEND_DIR)/score.h $(BACKEND_DIR)/worldData.h | 
	$(CC) $(CFLAGS) $(BACKEND_DIR)/world.c -o world.o


score.o: $(BACKEND_DIR)/score.c $(BACKEND_DIR)/score.h | 
	$(CC) $(CFLAGS) $(BACKEND_DIR)/score.c -o score.o


RasPiScreens.o: $(RASPI_DIR)/RasPiScreens.c $(RASPI_DIR)/RaspiData.h | 
	$(CC) $(CFLAGS) $(RASPI_DIR)/RasPiScreens.c -o RasPiScreens.o


RaspiInit.o: $(RASPI_DIR)/RaspiInit.c $(RASPI_DIR)/RaspiData.h | 
	$(CC) $(CFLAGS) $(RASPI_DIR)/RaspiInit.c -o RaspiInit.o


RaspiMainMenu.o: $(RASPI_DIR)/RaspiMainMenu.c $(RASPI_DIR)/RaspiData.h | 
	$(CC) $(CFLAGS) $(RASPI_DIR)/RaspiMainMenu.c -o RaspiMainMenu.o


RaspiPause.o: $(RASPI_DIR)/RaspiPause.c $(RASPI_DIR)/RaspiData.h | 
	$(CC) $(CFLAGS) $(RASPI_DIR)/RaspiPause.c -o RaspiPause.o


RaspiInGame.o: $(RASPI_DIR)/RaspiInGame.c $(RASPI_DIR)/RaspiData.h | 
	$(CC) $(CFLAGS) $(RASPI_DIR)/RaspiInGame.c -o RaspiInGame.o


RaspiGameover.o: $(RASPI_DIR)/RaspiGameover.c $(RASPI_DIR)/RaspiData.h | 
	$(CC) $(CFLAGS) $(RASPI_DIR)/RaspiGameover.c -o RaspiGameover.o


RaspiHiscore.o: $(RASPI_DIR)/RaspiHiscore.c $(RASPI_DIR)/RaspiData.h | 
	$(CC) $(CFLAGS) $(RASPI_DIR)/RaspiHiscore.c -o RaspiHiscore.o

clean:
	rm -f *.o froggerRaspi
