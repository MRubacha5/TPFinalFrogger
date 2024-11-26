# flags
CFLAGS = -Wall -Wextra -g
AL_LIBS = -lallegro -lallegro_primitives -lallegro_ttf -lallegro_font -lallegro_color -lallegro_image -lallegro_acodec -lallegro_audio

#Directories
AL = src/Frontend/Allegro/
BC = src/Backend/
BLD = build/

$(BLD)froggerAllegro: $(BLD)mainAllegro.o $(BLD)AllegroSetup.o $(BLD)AllegroPause.o $(BLD)AllegroMainMenu.o $(BLD)AllegroIngame.o $(BLD)AllegroHiScore.o $(BLD)score.o $(BLD)world.o $(BLD)rana.o
	gcc -o froggerAllegro $(BLD)mainAllegro.o $(BLD)AllegroSetup.o $(BLD)AllegroPause.o $(BLD)AllegroMainMenu.o $(BLD)AllegroHiScore.o $(BLD)score.o $(BLD)world.o $(BLD)rana.o $(BLD)AllegroIngame.o $(AL_LIBS) 

$(BLD)mainAllegro.o: $(AL)mainAllegro.c $(BC)worldData.h $(BC)rana.h $(BC)platformConfig.h $(AL)AllegroSetup.h
	gcc -c $(AL)mainAllegro.c $(CFLAGS) -D ALLEGRO

$(BLD)AllegroSetup.o: $(AL)AllegroSetup.c $(BC)platformConfig.h $(AL)AllegroSetup.h
	gcc -c $(AL)AllegroSetup.c $(CFLAGS) -D ALLEGRO

$(BLD)AllegroMainMenu.o: $(AL)AllegroHiScore.c $(BC)platformConfig.h $(AL)AllegroSetup.h $(BC)worldData.h $(BC)rana.h
	gcc -c $(AL)AllegroHiScore.c $(CFLAGS) -D ALLEGRO

$(BLD)AllegroPause.o: $(AL)AllegroPause.c $(AL)AllegroSetup.h
	gcc -c $(AL)AllegroPause.c $(CFLAGS) -D ALLEGRO

$(BLD)AllegroIngame.o: $(AL)AllegroIngame.c $(AL)AllegroSetup.h $(BC)worldData.h $(BC)movement.h $(BC)platformConfig.h $(BC)rana.h $(BC)score.h
	gcc -c $(AL)AllegroIngame.c $(CFLAGS) -D ALLEGRO

$(BLD)AllegroHiScore.o: $(AL)AllegroHiScore.c $(BC)score.h $(AL)AllegroSetup.h
	gcc -c $(AL)AllegroHiScore.c $(CFLAGS) -D ALLEGRO

$(BLD)AllegroGameOver.o: $(AL)AllegroGameOver.c $(BC)platformConfig.h $(BC)score.h $(AL)AllegroSetup.h
	gcc -c $(AL)AllegroSetup.c $(CFLAGS) -D ALLEGRO

$(BLD)world.o: $(BC)world.c $(BC)worldData.h $(BC)movement.h $(BC)platformConfig.h $(BC)rana.h $(BC)score.h
	gcc -c $(BC)world.c -D ALLEGRO $(CFLAGS)
	
$(BLD)score.o: $(BC)score.c $(BC)score.h
	gcc -c $(BC)score.c $(CFLAGS) -D ALLEGRO

$(BLD)rana.o: $(BC)rana.c $(BC)rana.h $(BC)movement.h $(BC)platformConfig.h $(BC)worldData.h $(BC)score.h
	gcc -c $(BC)rana.c $(CFLAGS) -D ALLEGRO
