#ifndef PLATFORMCONFIG_H
#define PLATFORMCONFIG_H

//CONFIGURACIONES DE ALLEGRO
#if defined(ALLEGRO)
    /*******************************************************************************
     * CONSTANTES
     ******************************************************************************/
    #define RANAWIDTH 16

    //Valor de ancho para Allegro. El alto es constante entre plataformas
    #define WIDTH GSIZEX *14

    //Constantes graficas
    #define GSIZEX 50
    #define GSIZEY 50

    //Coordenadas x de las posiciones de victoria
    #define WINPOS1 0
    #define WINPOS2 GSIZEX * 3
    #define WINPOS3 GSIZEX * 6
    #define WINPOS4 GSIZEX * 9
    #define WINPOS5 GSIZEX * 12


//CONFIGURACIONES DE RASPI
#elif defined(RASPI)
    /*******************************************************************************
     * CONSTANTES
     ******************************************************************************/
    #define RANAWIDTH 0

    //constantes graficas
    #define GSIZEX 1
    #define GSIZEY 1

    //valor de ancho del juego para raspi
    #define WIDTH GSIZEX * 14

    //Coordenadas x de las posiciones de victoria
    #define WINPOS1 0
    #define WINPOS2 3
    #define WINPOS3 6
    #define WINPOS4 9
    #define WINPOS5 12

#else 
    #error("No platform defined")
#endif 

#endif // PLATFORMCONFIG_H