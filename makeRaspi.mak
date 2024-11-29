# Flags
CC = gcc
CFLAGS = -c -Wall -Wextra -g -D RASPI

# Libraries
LIB = build/joydrv.o build/disdrv.o

# Directories
RASPI_DIR = src/Frontend/RasPi
BACKEND_DIR = src/Backend
BUILD_DIR = build

# Target executable
$(BUILD_DIR)/froggerRaspi: $(BUILD_DIR)/mainRaspi.o $(BUILD_DIR)/rana.o $(BUILD_DIR)/world.o $(BUILD_DIR)/score.o $(BUILD_DIR)/RasPiScreens.o $(BUILD_DIR)/RaspiInit.o $(BUILD_DIR)/RaspiMainMenu.o $(BUILD_DIR)/RaspiPause.o $(BUILD_DIR)/RaspiInGame.o $(BUILD_DIR)/RaspiGameover.o $(BUILD_DIR)/RaspiHiscore.o $(LIB)
	$(CC) -o $(BUILD_DIR)/froggerRaspi $(BUILD_DIR)/mainRaspi.o $(BUILD_DIR)/rana.o $(BUILD_DIR)/world.o $(BUILD_DIR)/score.o $(BUILD_DIR)/RasPiScreens.o $(BUILD_DIR)/RaspiInit.o $(BUILD_DIR)/RaspiMainMenu.o $(BUILD_DIR)/RaspiPause.o $(BUILD_DIR)/RaspiInGame.o $(BUILD_DIR)/RaspiGameover.o $(BUILD_DIR)/RaspiHiscore.o $(LIB) -lSDL2 -lSDL2_mixer

# Rule to compile mainRaspi.c
$(BUILD_DIR)/mainRaspi.o: $(RASPI_DIR)/mainRaspi.c $(RASPI_DIR)/RaspiData.h | $(BUILD_DIR)/
	$(CC) $(CFLAGS) $(RASPI_DIR)/mainRaspi.c -o $(BUILD_DIR)/mainRaspi.o

# Rule to compile rana.c
$(BUILD_DIR)/rana.o: $(BACKEND_DIR)/rana.c $(BACKEND_DIR)/rana.h $(BACKEND_DIR)/movement.h $(BACKEND_DIR)/platformConfig.h $(BACKEND_DIR)/score.h $(BACKEND_DIR)/worldData.h | $(BUILD_DIR)/
	$(CC) $(CFLAGS) $(BACKEND_DIR)/rana.c -o $(BUILD_DIR)/rana.o

# Rule to compile world.c
$(BUILD_DIR)/world.o: $(BACKEND_DIR)/world.c $(BACKEND_DIR)/rana.h $(BACKEND_DIR)/movement.h $(BACKEND_DIR)/platformConfig.h $(BACKEND_DIR)/score.h $(BACKEND_DIR)/worldData.h | $(BUILD_DIR)/
	$(CC) $(CFLAGS) $(BACKEND_DIR)/world.c -o $(BUILD_DIR)/world.o

# Rule to compile score.c
$(BUILD_DIR)/score.o: $(BACKEND_DIR)/score.c $(BACKEND_DIR)/score.h | $(BUILD_DIR)/
	$(CC) $(CFLAGS) $(BACKEND_DIR)/score.c -o $(BUILD_DIR)/score.o

# Rule to compile RasPiScreens.c
$(BUILD_DIR)/RasPiScreens.o: $(RASPI_DIR)/RasPiScreens.c $(RASPI_DIR)/RaspiData.h | $(BUILD_DIR)/
	$(CC) $(CFLAGS) $(RASPI_DIR)/RasPiScreens.c -o $(BUILD_DIR)/RasPiScreens.o

# Rule to compile RaspiInit.c
$(BUILD_DIR)/RaspiInit.o: $(RASPI_DIR)/RaspiInit.c $(RASPI_DIR)/RaspiData.h | $(BUILD_DIR)/
	$(CC) $(CFLAGS) $(RASPI_DIR)/RaspiInit.c -o $(BUILD_DIR)/RaspiInit.o

# Rule to compile RaspiMainMenu.c
$(BUILD_DIR)/RaspiMainMenu.o: $(RASPI_DIR)/RaspiMainMenu.c $(RASPI_DIR)/RaspiData.h | $(BUILD_DIR)/
	$(CC) $(CFLAGS) $(RASPI_DIR)/RaspiMainMenu.c -o $(BUILD_DIR)/RaspiMainMenu.o

# Rule to compile RaspiPause.c
$(BUILD_DIR)/RaspiPause.o: $(RASPI_DIR)/RaspiPause.c $(RASPI_DIR)/RaspiData.h | $(BUILD_DIR)/
	$(CC) $(CFLAGS) $(RASPI_DIR)/RaspiPause.c -o $(BUILD_DIR)/RaspiPause.o

# Rule to compile RaspiInGame.c
$(BUILD_DIR)/RaspiInGame.o: $(RASPI_DIR)/RaspiInGame.c $(RASPI_DIR)/RaspiData.h | $(BUILD_DIR)/
	$(CC) $(CFLAGS) $(RASPI_DIR)/RaspiInGame.c -o $(BUILD_DIR)/RaspiInGame.o

# Rule to compile RaspiGameover.c
$(BUILD_DIR)/RaspiGameover.o: $(RASPI_DIR)/RaspiGameover.c $(RASPI_DIR)/RaspiData.h | $(BUILD_DIR)/
	$(CC) $(CFLAGS) $(RASPI_DIR)/RaspiGameover.c -o $(BUILD_DIR)/RaspiGameover.o

# Rule to compile RaspiHiscore.c
$(BUILD_DIR)/RaspiHiscore.o: $(RASPI_DIR)/RaspiHiscore.c $(RASPI_DIR)/RaspiData.h | $(BUILD_DIR)/
	$(CC) $(CFLAGS) $(RASPI_DIR)/RaspiHiscore.c -o $(BUILD_DIR)/RaspiHiscore.o

# Create build directory if it doesn't exist
$(BUILD_DIR)/:
	mkdir -p $(BUILD_DIR)

# Clean up build files
clean:
	rm -f $(BUILD_DIR)/*.o $(BUILD_DIR)/froggerRaspi
