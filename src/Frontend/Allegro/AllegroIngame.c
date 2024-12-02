/*******************************************************************************
 * HEADERS
 ******************************************************************************/

#include <stdlib.h>
#include <stdio.h>

#include "AllegroSetup.h"
#include "../../Backend/worldData.h"
#include "../../Backend/score.h"
#include "../../Backend/rana.h"
#include "../../Backend/movement.h"
#include "../../Backend/platformConfig.h"

/*******************************************************************************
 * VARIABLES DE ALCANCE LOCAL
 ******************************************************************************/
//Se setean como FPS cuando hay una muerte/cambio de nivel. Inhibe el movimiento y el contador hasta que termine el evento
static uint16_t deathTimer = false; 
static bool ranaEntregadaFlag = false;
static bool nextLevelFlag = false;

static long int deathX, deathY;

/*******************************************************************************
 * PROTOTIPOS DE FUNCIONES
 ******************************************************************************/
static void ranaAnimate (allegroComponents_t * C, assets_t * assets, linea_t * map, rana_t * pRana, worldData_t * pWD);

static void ranaAnimate (allegroComponents_t * C, assets_t * assets, linea_t * map, rana_t * pRana, worldData_t * pWD)
{
    unsigned int m = 8; //Velocidad de movimiento de la rana

    /****************************************************************
     * DIBUJO LA RANA Y LLAMO LAS FUNCIONES LOGICAS NECESARIAS      *
     * **************************************************************/
    // SI LA RANA ESTA MURIENDO, NO LA DIBUJO

    #ifdef DEBUG
    al_draw_filled_rectangle(pRana->posx-HITBOXWIDTH/2.0,(HEIGHT-pRana->posy)*GSIZEY, 
            pRana->posx+HITBOXWIDTH/2,(HEIGHT-pRana->posy)*GSIZEY+GSIZEY,al_color_name("red"));
    #endif //DEBUG (Hitbox display)

    if (deathTimer == FPS) 
    {
        
        //Inhibo el movimiento (NO INPUT ASI SI PERMITO PAUSA) de la rana y guardo su posicion de muerte
        C->flagValue = 1; //no cero asi input no lo vuelve a setear
        deathX = pRana->posx;
        deathY = pRana->posy;
        al_play_sample((deathY > HEIGHT/2 && pWD->timeLeft && deathY != HEIGHT-1)? assets->drown : assets->crash,
                        1,0,1,ALLEGRO_PLAYMODE_ONCE,0);
    }
    // Animacion de ahogado solo en las lineas con troncos. Si se muere en otro lugar (o por tiempo) la animacion es explosion
    if (deathTimer >= FPS * 0.75)
    {
        al_draw_scaled_bitmap((deathY > HEIGHT/2 && pWD->timeLeft && deathY != HEIGHT-1)? assets->drown1_bitmap : assets->crash1_bitmap,
                    0,0,16,16, deathX - GSIZEX/2.0, (HEIGHT - deathY) * GSIZEY, GSIZEX,GSIZEY,0);
        deathTimer--;
    }
    else if (deathTimer >= FPS / 2)
    {
        al_draw_scaled_bitmap((deathY > HEIGHT/2 && pWD->timeLeft && deathY != HEIGHT-1)? assets->drown2_bitmap : assets->crash2_bitmap,
                    0,0,16,16, deathX - GSIZEX/2.0, (HEIGHT - deathY) * GSIZEY, GSIZEX,GSIZEY,0);
        deathTimer--;
    }
    else if (deathTimer > FPS/4)
    {
        al_draw_scaled_bitmap((deathY > HEIGHT/2 && pWD->timeLeft && deathY != HEIGHT-1)? assets->drown3_bitmap : assets->crash3_bitmap,
                    0,0,16,16, deathX - GSIZEX/2.0, (HEIGHT - deathY) * GSIZEY, GSIZEX,GSIZEY,0);
        deathTimer--;
    }
    else if (deathTimer > 0)
    {
        al_draw_scaled_bitmap(assets->death_bitmap,0,0,16,16,
                    deathX - GSIZEX/2.0, (HEIGHT - deathY) * GSIZEY, GSIZEX,GSIZEY,0);
        deathTimer--;
        C->flagValue = deathTimer == 1 ? 0 : C->flagValue;
    }


    // SI LA RANA ESTA VIVA, SI LA DIBUJO
    else if (C->flagValue)
    {
        switch (C->keycode)
        {
            case ALLEGRO_KEY_UP:
            if (C->flagValue == GSIZEY)
            {
                al_play_sample(assets->leap,1,0,1,ALLEGRO_PLAYMODE_ONCE,0);
                C->flagValue = C->flagValue/m;
                al_draw_scaled_bitmap(assets->frogLeapFwd_bitmap,0,0,16,16,
                        pRana->posx - GSIZEX/2.0, (HEIGHT - pRana->posy - 1 + (C->flagValue*m/(double)GSIZEY)) * GSIZEY, GSIZEX,GSIZEY,0);
                C->flagValue--;
            }
            else if (C->flagValue > m/2)
            {
                al_draw_scaled_bitmap(assets->frogLeapFwd_bitmap,0,0,16,16,
                        pRana->posx - GSIZEX/2.0, (HEIGHT - pRana->posy - 1 + (C->flagValue*m/(double)GSIZEY)) * GSIZEY, GSIZEX,GSIZEY,0);
                C->flagValue--;
            }
            else if (C->flagValue == m/2 || (GSIZEY/m < m/2 && C->flagValue == GSIZEY/m - 1))//Backend move occurs halfway through animation; second condition accounts for small screen sizes
            {
                al_draw_scaled_bitmap(assets->frogLeapFwd_bitmap,0,0,16,16,
                        pRana->posx - GSIZEX/2.0, (HEIGHT - pRana->posy - 1 + (C->flagValue*m/(double)GSIZEY)) * GSIZEY, GSIZEX,GSIZEY,0);
                MoveRana(pRana, UP, map + (pRana->posy));

                C->flagValue--;

            }
            else if (C->flagValue > 0)
            {
                al_draw_scaled_bitmap(assets->frogLeapFwd_bitmap,0,0,16,16,
                        pRana->posx - GSIZEX/2.0, (HEIGHT - pRana->posy + (C->flagValue*m/(double)GSIZEY)) * GSIZEY, GSIZEX,GSIZEY,0);
                C->flagValue--;
            }
            break;

            case ALLEGRO_KEY_DOWN:
            if (C->flagValue == GSIZEY && pRana->posy == 0) //No permite que la rana baje del origen
            {
                C->flagValue = 0;
                al_draw_scaled_bitmap(assets->frog_bitmap,0,0,16,16,
                    pRana->posx - GSIZEX/2.0, (HEIGHT - pRana->posy) * GSIZEY, GSIZEX,GSIZEY,0);
            }
            else if (C->flagValue == GSIZEY)
            {
                al_play_sample(assets->leap,1,0,1,ALLEGRO_PLAYMODE_ONCE,0);
                C->flagValue = C->flagValue/m;
                al_draw_scaled_bitmap(assets->frogLeapBack_bitmap,0,0,16,16,
                        pRana->posx - GSIZEX/2.0, (HEIGHT - pRana->posy + 1 - (C->flagValue*m)/(double)GSIZEY) * GSIZEY, GSIZEX,GSIZEY,0);
                C->flagValue--;
            }
            else if (C->flagValue > GSIZEY/(2*m))
            {
                al_draw_scaled_bitmap(assets->frogLeapBack_bitmap,0,0,16,16,
                        pRana->posx - GSIZEX/2.0, (HEIGHT - pRana->posy + 1 - (C->flagValue*m)/(double)GSIZEY) * GSIZEY, GSIZEX,GSIZEY,0);
                C->flagValue--;
            }
            else if (C->flagValue == GSIZEY/(2*m) || (GSIZEY/m < m/2 && C->flagValue == GSIZEY/m - 1))
            {
                
                al_draw_scaled_bitmap(assets->frogLeapBack_bitmap,0,0,16,16,
                        pRana->posx - GSIZEX/2.0, (HEIGHT - pRana->posy + 1 - (C->flagValue*m)/(double)GSIZEY) * GSIZEY, GSIZEX,GSIZEY,0);
                MoveRana(pRana, DOWN, map + pRana->posy);
                C->flagValue--;
            }
            else if (C->flagValue > 0)
            {
                al_draw_scaled_bitmap(assets->frogLeapBack_bitmap,0,0,16,16,
                        pRana->posx - GSIZEX/2.0, (HEIGHT - pRana->posy - (C->flagValue*m)/(double)GSIZEY) * GSIZEY, GSIZEX,GSIZEY,0);
                C->flagValue--;
            }
            break;

            case ALLEGRO_KEY_LEFT:
            case ALLEGRO_KEY_RIGHT:
            if (C->flagValue == GSIZEX) al_play_sample(assets->leap,1,0,1,ALLEGRO_PLAYMODE_ONCE,0);
            al_draw_scaled_bitmap((C->keycode == ALLEGRO_KEY_LEFT)? assets->frogLeapLeft_bitmap : assets->frogLeapRight_bitmap,0,0,16,16,
                                    pRana->posx - GSIZEX/2.0, (HEIGHT - pRana->posy) * GSIZEY, GSIZEX,GSIZEY,0);
            for (unsigned n = 1; C->flagValue > 0 && n < m; n++)
            {
                C->flagValue = (C->flagValue-1 > 0)? C->flagValue-1 : 0;
                MoveRana(pRana, (C->keycode == ALLEGRO_KEY_LEFT)? LEFT : RIGHT, map + (pRana->posy));
            }
            break;
        }
    }
    else{ //Idle animation
        switch(pRana->dir)
        {
            case UP:
                assets->frog_bitmap = assets->frogIdleFwd_bitmap;
                break;
            case DOWN:
                assets->frog_bitmap = assets->frogIdleBack_bitmap;
                break;
            case LEFT:
                assets->frog_bitmap = assets->frogIdleLeft_bitmap;
                break;
            case RIGHT:
                assets->frog_bitmap = assets->frogIdleRight_bitmap;
                break;
            default:
                break;
        }
        al_draw_scaled_bitmap(assets->frog_bitmap,0,0,16,16,
            pRana->posx - GSIZEX/2.0, (HEIGHT - pRana->posy) * GSIZEY, GSIZEX,GSIZEY,0);
    }
}

void inGame (allegroComponents_t * Comp, assets_t * assets, linea_t * map, rana_t * pRana, worldData_t * pWD)
{
    if(!al_get_sample_instance_playing(assets->game_startInstance) && !nextLevelFlag)
    {
        al_set_sample_instance_playing(assets->musicInstance, true);
    }
    if(Comp->fpsCounter >= FPS){
        Comp->fpsCounter = 0;
        if(!deathTimer && !nextLevelFlag)
        {
            pWD->timeLeft--;
        }
        
    }
    
    al_clear_to_color(al_color_name("black"));

    /***************
    * DIBUJO EL UI *
    ****************/
    // dibujo las ranas que simbolizan vidas
    for (int a = 0; a < pRana->vidas; a++)
    {
        al_draw_scaled_bitmap(assets->frogIdleFwd_bitmap,0,0,16,16,
                GSIZEX*(a+1), (HEIGHT +1) * GSIZEY, GSIZEX,GSIZEY,0);
    }
    
    //dibujo el tiempo restante
    al_draw_text(Comp->font,al_color_name("yellow"),GSIZEX,GSIZEY*(HEIGHT+2),0,"TIME");

    if (pWD->timeLeft > 30)
    {
        al_draw_filled_rectangle(GSIZEX*3.5,(HEIGHT + 2)*GSIZEY,3.5*GSIZEX + ((pWD->timeLeft) * GSIZEX/6.333) , (HEIGHT+2.5)*GSIZEY, al_color_name("green"));
    }
    else if (pWD->timeLeft > 10)
    {
        al_draw_filled_rectangle(GSIZEX*3.5,(HEIGHT + 2)*GSIZEY,3.5*GSIZEX + ((pWD->timeLeft) * GSIZEX/6.333) , (HEIGHT+2.5)*GSIZEY, al_color_name("yellow"));
    }
    else if (pWD->timeLeft == 10)
    {
        al_draw_filled_rectangle(GSIZEX*3.5,(HEIGHT + 2)*GSIZEY,3.5*GSIZEX + ((pWD->timeLeft) * GSIZEX/6.333) , (HEIGHT+2.5)*GSIZEY, al_color_name("red"));
        al_play_sample(assets->time_running_out,1,0,1,ALLEGRO_PLAYMODE_ONCE,0);
    }
    else if (pWD->timeLeft > 0)
    {
        al_draw_filled_rectangle(GSIZEX*3.5,(HEIGHT + 2)*GSIZEY,3.5*GSIZEX + ((pWD->timeLeft) * GSIZEX/6.333) , (HEIGHT+2.5)*GSIZEY, al_color_name("red"));
    }
    else if (deathTimer == 0) //La rana muere si se queda sin tiempo
    {
        deathTimer = FPS;
    }

    //dibujo el score
    al_draw_text(Comp->font,al_color_name("white"),GSIZEX, (HEIGHT+2.75)*GSIZEY,0,"SCORE");
    al_draw_text(Comp->font, al_color_name("white"), GSIZEX*4,(HEIGHT+2.75)*GSIZEY, 0, scorestr);

    //high score
    al_draw_text(Comp->font,al_color_name("white"),GSIZEX*9, (HEIGHT+2.75)*GSIZEY,0,"HI");
    al_draw_text(Comp->font,al_color_name("white"),GSIZEX*10.5, (HEIGHT+2.75)*GSIZEY,0,highscorestr);

    /*****************************
    * DIBUJO LAS LINEAS DEL MAPA *
    ******************************/
    for (int i = 0; i < HEIGHT ; i++){

        linea_t * linea = map+i;
        
        /******************
        * LINEAS DE PASTO *
        *******************/
        if (i == 0 || i == HEIGHT/2)
        {

            if(i==HEIGHT/2){
                al_draw_filled_rectangle(0,(HEIGHT-i-1)*GSIZEY,
                    WIDTH, (HEIGHT-i)*GSIZEY + GSIZEY/2.0, al_color_name("darkblue"));
            }
            for(int j = 0; j < WIDTH/GSIZEX; j++){
                al_draw_scaled_bitmap(assets->purpleGrass_bitmap,0,0,16,16,
                    j*GSIZEX, (HEIGHT-i) * GSIZEY, GSIZEX,GSIZEY,0);
            }
        }
        
        /******************
        * LINEAS DE CALLE *
        *******************/
        else if(i > 0 && i < HEIGHT/2){ 
        
            for (int obj = 0; obj < linea->cant_obj; obj++)
            {
                float objx = linea->po[obj];

                // Autos y Camiones
                switch (linea->size)
                {
                case 1:
                    switch (linea->dir)
                    {
                    case IZQ:
                        if (i%3 == 1){
                            #ifdef DEBUG
                            al_draw_filled_rectangle(objx, (HEIGHT-i)*GSIZEY,objx+GSIZEX,(HEIGHT-i+1)*GSIZEY,(al_color_name("purple")));
                            #endif
                            al_draw_scaled_bitmap(assets->car2_bitmap,0,0,16,16,
                                objx, (HEIGHT-i) * GSIZEY, GSIZEX, GSIZEY, 0);
                        }
                        else{
                            #ifdef DEBUG
                            al_draw_filled_rectangle(objx, (HEIGHT-i)*GSIZEY,objx+GSIZEX,(HEIGHT-i+1)*GSIZEY,(al_color_name("purple")));
                            #endif
                            al_draw_scaled_bitmap(assets->car1_bitmap,0,0,16,16,
                                objx, (HEIGHT-i) * GSIZEY, GSIZEX, GSIZEY, 0);
                        }
                        break;
                    case DER:
                        if (i%3 == 1){
                            #ifdef DEBUG
                            al_draw_filled_rectangle(objx, (HEIGHT-i)*GSIZEY,objx+GSIZEX,(HEIGHT-i+1)*GSIZEY,(al_color_name("purple")));
                            #endif
                            al_draw_scaled_bitmap(assets->car3_bitmap,0,0,16,16,
                                objx, (HEIGHT-i) * GSIZEY, GSIZEX, GSIZEY, 0);

                        }
                        else{
                            #ifdef DEBUG
                            al_draw_filled_rectangle(objx, (HEIGHT-i)*GSIZEY,objx+GSIZEX,(HEIGHT-i+1)*GSIZEY,(al_color_name("purple")));
                            #endif
                            al_draw_scaled_bitmap(assets->car4_bitmap,0,0,16,16,
                                objx, (HEIGHT-i) * GSIZEY, GSIZEX, GSIZEY, 0);
                        }
                    }
                        break;
                case 2:
                    #ifdef DEBUG
                            al_draw_filled_rectangle(objx, (HEIGHT-i)*GSIZEY,objx+GSIZEX*2,(HEIGHT-i+1)*GSIZEY,(al_color_name("purple")));
                    #endif
                    al_draw_scaled_bitmap(assets->truck_bitmap,0,0,32,16,
                        objx, (HEIGHT-i) * GSIZEY, GSIZEX *2, GSIZEY, 0);
                    break;
                default:
                    break;
                }
            }
            
        }		

        /******************
        * LINEAS DE AGUA *
        *******************/			
        else if(i > HEIGHT/2 && i < HEIGHT-1){ 
            //imprimo el agua en si 
            al_draw_filled_rectangle(0,(HEIGHT-i-1)*GSIZEY,
            WIDTH, (HEIGHT-i)*GSIZEY, al_color_name("darkblue"));

            //imprimo troncos
            for (int obj = 0; obj < linea->cant_obj; obj++)
            {
                float objx = linea->po[obj];
                for (int size = 0; size < linea->size; size++)
                {
                    if(size == 0){
                        #ifdef DEBUG
                            al_draw_filled_rectangle(objx, (HEIGHT-i)*GSIZEY,objx+GSIZEX,(HEIGHT-i+1)*GSIZEY,(al_color_name("purple")));
                        #endif
                        al_draw_scaled_bitmap(assets->logLeft_bitmap,0,0,16,16,
                            objx, (HEIGHT-i) * GSIZEY, GSIZEX, GSIZEY, 0);
                    }
                    else if (size == linea->size - 1){
                        #ifdef DEBUG
                            al_draw_filled_rectangle((objx+GSIZEX*size), (HEIGHT-i)*GSIZEY,objx+GSIZEX*(size+1),(HEIGHT-i+1)*GSIZEY,(al_color_name("purple")));
                        #endif
                        al_draw_scaled_bitmap(assets->logRight_bitmap,0,0,16,16,
                            (objx+GSIZEX*size), (HEIGHT-i) * GSIZEY, GSIZEX,GSIZEY,0);
                    }
                    else{
                        al_draw_scaled_bitmap(assets->logMiddle_bitmap,0,0,16,16,
                            (objx+GSIZEX*size), (HEIGHT-i) * GSIZEY, GSIZEX,GSIZEY,0);
                    }
                }
            }
        }

        /****************************************************************************
        * ULTIMA LINEA DEL MAPA: LOS OBJETIVOS, SEPARADORES Y RANAS QUE YA LLEGARON *
        *****************************************************************************/
        else if(i == HEIGHT - 1){
            al_draw_filled_rectangle(0, (HEIGHT-i)*GSIZEY,
                WIDTH, (HEIGHT-i-1)*GSIZEY, al_color_name("darkblue"));

            //Espacios libres
            #ifdef DEBUG
                    #define HITBOX_WINPOS(x) (al_draw_filled_rectangle((x)-HITBOXWIDTH/3.0, GSIZEY *0.75, (x)+HITBOXWIDTH/3.0, GSIZEY *1.75,al_color_name("red")))
                    //al_draw_filled_rectangle(WINPOS1-0.25*HITBOXWIDTH, GSIZEY *0.75, 
                    //	WINPOS1+0.25*HITBOXWIDTH, GSIZEY *1.75,al_color_name("red"));
                    HITBOX_WINPOS(WINPOS1);
                    HITBOX_WINPOS(WINPOS2);
                    HITBOX_WINPOS(WINPOS3);
                    HITBOX_WINPOS(WINPOS4);
                    HITBOX_WINPOS(WINPOS5);
            #endif //DEBUG (Hitbox display)

            //Casillas donde van las ranas (macro para simplificar codigo)
            #define DRAW_GRASSWINFRAME(x) (al_draw_scaled_bitmap(assets->grassWinFrame_bitmap,0,0,32,24,(x)-GSIZEX, (HEIGHT-i-1) * GSIZEY, GSIZEX *2,GSIZEY*2,0))
            DRAW_GRASSWINFRAME(WINPOS1);
            DRAW_GRASSWINFRAME(WINPOS2);
            DRAW_GRASSWINFRAME(WINPOS3);
            DRAW_GRASSWINFRAME(WINPOS4);
            DRAW_GRASSWINFRAME(WINPOS5);

            //Separadores (macro para simplificar codigo)
            #define DRAW_GRASSWINSEPARATORS(winpos) al_draw_scaled_bitmap(assets->grassWinSeparator_bitmap,0,0,16,24,  \
                                                        (winpos)+GSIZEX,(HEIGHT-i-1) * GSIZEY, GSIZEX, GSIZEY*2,0);    \
                                                    al_draw_scaled_bitmap(assets->grassWinSeparator_bitmap,0,0,16,24,  \
                                                        (winpos)+GSIZEX*1.5,(HEIGHT-i-1) * GSIZEY, GSIZEX, GSIZEY*2,0) 
            DRAW_GRASSWINSEPARATORS(WINPOS1);
            DRAW_GRASSWINSEPARATORS(WINPOS2);
            DRAW_GRASSWINSEPARATORS(WINPOS3);
            DRAW_GRASSWINSEPARATORS(WINPOS4);
            DRAW_GRASSWINSEPARATORS(WINPOS5);

            /// Dibujo ranas que ya llegaron (macro para simplificar codigo)
            #define DRAW_FROGWIN(x) (al_draw_scaled_bitmap(assets->frogWin_bitmap,0,0,16,16,(x)-0.5*GSIZEX, GSIZEY *0.75, GSIZEX,GSIZEY,0))
            if(pWD->winPosStates[0] == WIN_OCC){
                DRAW_FROGWIN(WINPOS1);
            }
            if(pWD->winPosStates[1] == WIN_OCC){
                DRAW_FROGWIN(WINPOS2);
            }
            if(pWD->winPosStates[2] == WIN_OCC){
                DRAW_FROGWIN(WINPOS3);
            }
            if(pWD->winPosStates[3] == WIN_OCC){
                DRAW_FROGWIN(WINPOS4);
            }
            if(pWD->winPosStates[4] == WIN_OCC){
                DRAW_FROGWIN(WINPOS5);
            }
            
        }	

        /**********************************************************************************************************************
         * MOVIMIENTO DE LOS OBJETOS SEGUN SU VELOCIDAD. VELOCIDAD V = V PIXELES POR FOTOGRAMA (ESCENCIALMENTE UNA FRECUENCIA)*
         * ********************************************************************************************************************/
        if(linea->cant_obj > 0)
        {
            for(int f = 1; f <= linea->v; f++)
            {
                moveLine(linea, i, pRana);
            }
            
        }
        
    }

    // Calculo colisiones
    int status = RanaCollisions(pRana, &map[pRana->posy], pWD);
    
    //Me fijo si se entrego la rana o no
    if (status == NEXTLEVELTRUE || status == NEXTLEVELFALSE)
    {
        ranaEntregadaFlag = 1;
        al_play_sample(assets->homed,1,0,1,ALLEGRO_PLAYMODE_ONCE,0);

    }
    else 
    {
        ranaEntregadaFlag = 0;
    }

    
    if (deathTimer != 0 || status == 1) // Death check
    {
        if(deathTimer == 0) // Kill rana (acaba de colisionar)
        {
            deathTimer = FPS;
        } 
        if (deathTimer == 1) // Respawn rana (finishing respawn animation)
        {
            RestarVidas(pRana, pWD);
            assets->frog_bitmap = assets->frogIdleFwd_bitmap;
        }
    
    }
    else if (status == NEXTLEVELTRUE) // Win
    {
        nextLevelFlag = true;
        InhibitInput(true);
        al_set_sample_instance_playing(assets->musicInstance,false);
        al_set_sample_instance_playing(assets->stage_clearInstance, true);
    }
    if (nextLevelFlag)
    {
        al_draw_filled_rectangle(DISPLAY_X/8, DISPLAY_Y*7/16, DISPLAY_X*7/8, DISPLAY_Y*9/16, al_color_name("black"));
        al_draw_text(Comp->fontL, al_color_name("red"), DISPLAY_X/2, (DISPLAY_Y-GSIZEY)/2, ALLEGRO_ALIGN_CENTER, "LEVEL UP");
        if(!al_get_sample_instance_playing(assets->stage_clearInstance))
        {
            pWD->difficulty++;
            createMap(map, pWD);
            al_rest(0.5);
            InhibitInput(false);
            al_set_sample_instance_playing(assets->musicInstance,true);
            nextLevelFlag = false;
        }
    }

    ranaAnimate (Comp, assets, map, pRana, pWD);
    
    if (!pRana->vidas)
    {
        Comp->screen = GAMEOVER;
        Comp->flagValue = 0;
        al_stop_sample_instance(assets->musicInstance);
    }
    currentScore = ct_score(pRana->posy,pWD->timeLeft, pRana->vidas,ranaEntregadaFlag, 0);
    intToChar (6, scorestr, currentScore);
    // Game tick update
    Comp->fpsCounter++;
}
