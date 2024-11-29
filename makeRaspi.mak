# flags
CC = gcc
CFLAGS = -c -Wall -Wextra -D RASPI

#libraries
LIB = build/joydrv.o build/disdrv.o

#Directories
RASPI_DIR = src/Frontend/RasPi/
BACKEND_DIR = src/Backend/
BUILD_DIR = build/

$(BUILD_DIR)froggerRaspi: $(BUILD_DIR)mainRaspi.o $(BUILD_DIR)rana.o $(BUILD_DIR)world.o $(BUILD_DIR)score.o $(BUILD_DIR)RasPiScreens.o $(BUILD_DIR)RaspiInit.o $(BUILD_DIR)RaspiMainMenu $(BUILD_DIR)RaspiPause.o $(BUILD_DIR)RaspiPause.o $(BUILD_DIR)RaspiInGame.o $(BUILD_DIR)RaspiGameover.o $(BUILD_DIR)RaspiHiscore.o | $(BUILD_DIR)
	gcc -o $(CFLAGS) $(BUILD_DIR)mainRaspi.o $(BUILD_DIR)rana.o $(BUILD_DIR)world.o $(BUILD_DIR)score.o $(BUILD_DIR)RasPiScreens.o $(BUILD_DIR)RaspiInit.o $(BUILD_DIR)RaspiMainMenu $(BUILD_DIR)RaspiPause.o $(BUILD_DIR)RaspiPause.o $(BUILD_DIR)RaspiInGame.o $(BUILD_DIR)RaspiGameover.o $(BUILD_DIR)RaspiHiscore.o -lSDL2 -lSDL2_mixer

$(BUILD_DIR)mainRaspi.o: $(RASPI_DIR)mainRaspi.c $(RASPI_DIR)RaspiData.h | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(RASPI_DIR)mainRaspi.c

$(BUILD_DIR)rana.o: $(BACKEND_DIR)rana.c $(BACKEND_DIR)rana.h $(BACKEND_DIR)movement.h $(BACKEND_DIR)platformConfig.h $(BACKEND_DIR)score.h $(BACKEND_DIR)worldData.h | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(BACKEND_DIR)rana.c

$(BUILD_DIR)world.o: $(BACKEND_DIR)world.c $(BACKEND_DIR)rana.h $(BACKEND_DIR)movement.h $(BACKEND_DIR)platformConfig.h $(BACKEND_DIR)score.h $(BACKEND_DIR)worldData.h | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(BACKEND_DIR)world.c

$(BUILD_DIR)score.o: $(BACKEND_DIR)score.c $(BACKEND_DIR)score.h
	$(CC) $(CFLAGS) $(BACKEND_DIR)score.c

$(BUILD_DIR)RasPiScreens.o: $(RASPI_DIR)RasPiScreens.c $(RASPI_DIR)RaspiData.h | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(RASPI_DIR)RasPiScreens.c

$(BUILD_DIR)RaspiInit.o: $(RASPI_DIR)RaspiInit.c $(RASPI_DIR)RaspiData.h | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(RASPI_DIR)RaspiInit.c

$(BUILD_DIR)RaspiMainMenu.o: $(RASPI_DIR)RaspiMainMenu.c $(RASPI_DIR)RaspiData.h | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(RASPI_DIR)RaspiMainMenu.c

$(BUILD_DIR)RaspiPause.o: $(RASPI_DIR)RaspiPause.c $(RASPI_DIR)RaspiData.h | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(RASPI_DIR)RaspiPause.c

$(BUILD_DIR)RaspiInGame.o: $(RASPI_DIR)RaspiInGame.c $(RASPI_DIR)RaspiData.h | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(RASPI_DIR)RaspiInGame.c

$(BUILD_DIR)RaspiGameover.o: $(RASPI_DIR)RaspiGameover.c $(RASPI_DIR)RaspiData.h | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(RASPI_DIR)RaspiGameover.c

$(BUILD_DIR)RaspiHiscore.o: $(RASPI_DIR)RaspiHiscore.c $(RASPI_DIR)RaspiData.h | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(RASPI_DIR)RaspiHiscore.c

