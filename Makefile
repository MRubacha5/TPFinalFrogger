froggerAllegro: 
	make -f makeAllegro.mak

froggerRaspi:
	make -f makeRaspi.mak

clean:
	rm -f *.o

uninstall_froggerAllegro:
	rm -r froggerAllegro

uninstall_froggerRaspi:
	rm -r froggerRaspi