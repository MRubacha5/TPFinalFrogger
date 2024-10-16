#ifndef PLATFORMCONFIG_H
#define PLATFORMCONFIG_H

//CONFIGURACIONES DE ALLEGRO
#if defined(ALLEGRO)
    /*******************************************************************************
     * CONSTANTES
     ******************************************************************************/
    #define RANAWIDTH 16


    //Constantes graficas
    #define GSIZEX 50
    #define GSIZEY 50

    //Coordenadas x de las posiciones de victoria
    #define WINPOS1 25
    #define WINPOS2 125
    #define WINPOS3 225
    #define WINPOS4 325
    #define WINPOS5 425


//CONFIGURACIONES DE RASPI
#elif defined(RASPI)
    /*******************************************************************************
     * CONSTANTES
     ******************************************************************************/
    #define RANAWIDTH 0

    //Coordenadas x de las posiciones de victoria
    #define WINPOS1 0
    #define WINPOS2 0
    #define WINPOS3 0
    #define WINPOS4 0
    #define WINPOS5 0

#else 
    #error("No platform defined")
#endif 

#endif // PLATFORMCONFIG_H