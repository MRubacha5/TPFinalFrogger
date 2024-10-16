#ifndef PLATFORMCONFIG_H
#define PLATFORMCONFIG_H

//CONFIGURACIONES DE ALLEGRO
#if defined(ALLEGRO)
    /*******************************************************************************
     * CONSTANTES
     ******************************************************************************/
    #define RANAWIDTH 16


    //Coordenadas x de las posiciones de victoria
    #define WINPOS1 50
    #define WINPOS2 150
    #define WINPOS3 250
    #define WINPOS4 350
    #define WINPOS5 450


//CONFIGURACIONES DE RASPI
#else
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

//#else 
    //#error("No platform defined")
#endif 

#endif // PLATFORMCONFIG_H