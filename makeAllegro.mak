# flags
CFLAGS = -Wall -Wextra -g
AL_LIBS = -lallegro -lallegro_primitives -lallegro_ttf -lallegro_font -lallegro_color -lallegro_image -lallegro_acodec -lallegro_audio

#Directories
AL = src/Frontend/Allegro/
BC = src/Backend/
BLD = build/

froggerAllegro: AllegroSetup.o mainAllegro.o AllegroPause.o AllegroMainMenu.o AllegroIngame.o AllegroHiScore.o score.o world.o rana.o
	gcc -o froggerAllegro AllegroSetup.o mainAllegro.o AllegroPause.o AllegroMainMenu.o AllegroHiScore.o score.o world.o rana.o AllegroIngame.o $(AL_LIBS)mak 
	mv *.o /build

AllegroSetup.o: $(AL)AllegroSetup.c $(BC)platformConfig.h $(AL)AllegroSetup.h
	gcc -c $(AL)AllegroSetup.c $(CFLAGS) -D ALLEGRO

mainAllegro.o: $(AL)mainAllegro.c $(BC)worldData.h $(BC)rana.h $(BC)platformConfig.h $(AL)AllegroSetup.h
	gcc -c $(AL)mainAllegro.c $(CFLAGS) -D ALLEGRO

AllegroMainMenu.o: $(AL)AllegroMainMenu.c $(BC)platformConfig.h $(AL)AllegroSetup.h $(BC)worldData.h $(BC)rana.h
	gcc -c $(AL)AllegroMainMenu.c $(CFLAGS) -D ALLEGRO

AllegroPause.o: $(AL)AllegroPause.c $(AL)AllegroSetup.h
	gcc -c $(AL)AllegroPause.c $(CFLAGS) -D ALLEGRO

AllegroIngame.o: $(AL)AllegroIngame.c $(AL)AllegroSetup.h $(BC)worldData.h $(BC)movement.h $(BC)platformConfig.h $(BC)rana.h $(BC)score.h
	gcc -c $(AL)AllegroIngame.c $(CFLAGS) -D ALLEGRO

AllegroHiScore.o: $(AL)AllegroHiScore.c $(BC)score.h $(AL)AllegroSetup.h
	gcc -c $(AL)AllegroHiScore.c $(CFLAGS) -D ALLEGRO

AllegroGameOver.o: $(AL)AllegroGameOver.c $(BC)platformConfig.h $(BC)score.h $(AL)AllegroSetup.h
	gcc -c $(AL)AllegroSetup.c $(CFLAGS) -D ALLEGRO

world.o: $(BC)world.c $(BC)worldData.h $(BC)movement.h $(BC)platformConfig.h $(BC)rana.h $(BC)score.h
	gcc -c $(BC)world.c -D ALLEGRO $(CFLAGS)
	
score.o: $(BC)score.c $(BC)score.h
	gcc -c $(BC)score.c $(CFLAGS) -D ALLEGRO

rana.o: $(BC)rana.c $(BC)rana.h $(BC)movement.h $(BC)platformConfig.h $(BC)worldData.h $(BC)score.h
	gcc -c $(BC)rana.c $(CFLAGS) -D ALLEGRO
