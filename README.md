# 25.02 Programación I - Trabajo Práctico Final - Frogger
Otamendi, Nicanor - Rodríguez Arias, Juan Martín - Rubacha, Manuel

Este repo cuenta con el código para ejecutar el juego tanto en una PC con Linux y Allegro 5 como en una Raspberry Pi con un display de 16x16 LEDs y un joystick.

## Instalación

### 1. Clonar el repo

### 2. Instalar allegro 5 (No es necesario en Raspberry Pi)
    En terminal, utilizar el comando:
    sudo apt-get install liballegro5-dev 

### 3. Compilar con Makefile
    En terminal, utilizar el comando:
    make froggerAllegro
    ó
    make froggerRaspi
    
    Para borrar los archivos .o generados, utilizar el comando:
    make clean 

    Para desinstalar el juego,  utilizar el comando:
    make uninstall_froggerAllegro
    ó
    make uninstall_froggerRaspi
    NOTA: Este comando SOLAMENTE desinstala el ejecutable; es decir, NO borra los archivos .o

## Bibliografía
> Todos los sprites al igual que el audio fueron tomados del juego Frogger (Konami Group Corporation & Sega Corporation, 1981)

