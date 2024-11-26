froggerAllegro: 
	make -f makeAllegro.mak

froggerRaspi:
	make -f makeRaspi.mak

clean:
	rm -f *.o rm -r froggerAllegro -r froggerRaspi