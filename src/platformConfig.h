#ifndef PLATFORMCONFIG_H
#define PLATFORMCONFIG_H

//CONFIGURACIONES DE ALLEGRO
#if defined(ALLEGRO)
    /*******************************************************************************
     * CONSTANTES
     ******************************************************************************/
    #define RANAWIDTH 16

    //Coordenadas x de las posiciones de victoria
    #define WINPOS1 1
    #define WINPOS2 2
    #define WINPOS3 3
    #define WINPOS4 4
    #define WINPOS5 5

//CONFIGURACIONES DE RASPI
#else
    /*******************************************************************************
     * CONSTANTES
     ******************************************************************************/
    #define RANAWIDTH 0

    //Coordenadas x de las posiciones de victoria
    #define WINPOS1 1
    #define WINPOS2 2
    #define WINPOS3 3
    #define WINPOS4 4
    #define WINPOS5 5

#endif 

#endif PLATFORMCONFIG_H