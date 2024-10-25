#ifndef PLATFORMCONFIG_H
#define PLATFORMCONFIG_H

//CONFIGRACIONES GLOBALES
#define FPS 60
#define START_TIME 60 // (en segundos)

//HABILITAR DEBUG 
//#define DEBUG

//CONFIGURACIONES DE ALLEGRO
#if defined(ALLEGRO)
    /*******************************************************************************
     * CONSTANTES
     *******************************************************************************/
    //Constantes graficas
    #define GSIZEX 50
    #define GSIZEY 50

    #define HITBOXWIDTH 13.0/16 * GSIZEX

   //Valor de ancho para Allegro. El alto es constante entre plataformas
    #define WIDTH GSIZEX *14

    //Coordenadas x de las posiciones de victoria
    #define WINPOS1 GSIZEX * 1
    #define WINPOS2 GSIZEX * 4
    #define WINPOS3 GSIZEX * 7
    #define WINPOS4 GSIZEX * 10
    #define WINPOS5 GSIZEX * 13


//CONFIGURACIONES DE RASPI
#elif defined(RASPI)
    /*******************************************************************************
     * CONSTANTES
     ******************************************************************************/
    #define RANAWIDTH 0

    //constantes graficas
    #define GSIZEX 1
    #define GSIZEY 1

    #define HITBOXWIDTH 0

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