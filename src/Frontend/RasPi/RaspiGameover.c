#include "RaspiData.h"

void gameover(){

}

if(IsMax(currentScore, "score.txt")){

    for(i = 0 ; i < 3 ; i++){
        for(c = 0 ; c < 5 ; c++){
            for(j = 0 ; j < 3 ; j++){
                pos.x = 3 + i*4 + j;
                pos.y = 5 + c;
                if(i == charSelected){
                    disp_write(pos, !letters[charSelection[i]][c][j]);
                }
                else{
                    disp_write(pos, letters[charSelection[i]][c][j]);
                }
                
            }
        }
    }

    for(c = 0 ; c < 7 ; c++){
            for(j = 0 ; j < 5 ; j++){
                pos.x = 2 + charSelected*4 + j;
                pos.y = 4 + c;
                if(c == 0 || c == 6 || j == 0 || j == 4)
                    disp_write(pos, 1);
            }
        }

    if(!joyMoved){
        isMoving = 0;
    }

    if(joyMoved && !isMoving){
        isMoving = 1;

        switch (joyValue)
        {
        case DOWN:
            charSelection[charSelected] = (charSelection[charSelected] < 25)?(charSelection[charSelected]+1):0;
            break;
        case UP:
            charSelection[charSelected] = (charSelection[charSelected] > 0)?(charSelection[charSelected]-1):25;
            break;
        case RIGHT:
            charSelected = (charSelected < 2)?(charSelected+1):(charSelected);
            break;
        case LEFT:
            charSelected = (charSelected > 0)?(charSelected-1):(charSelected);
            break;
        }
    }

    if(coord.sw == J_PRESS && joyPressed == 0){
        joyPressed = 1;

        for(i = 0 ; i < 3 ; i++){
            name[i] = charSelection[i] + 'A';
        }

        max_scores(currentScore,"score.txt", name);

        charSelection[0] = 0;
        charSelection[1] = 0;
        charSelection[2] = 0;
        charSelected = 0;

        getTopScores("score.txt");
        screen = HIGHSCORE;
        highSelected = 0;
        disp_clear();
    }
}
else{
    screen = HIGHSCORE;
    highSelected = 0;
}

disp_update();