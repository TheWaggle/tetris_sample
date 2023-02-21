#include "view.h"
#include "tetris.h"

#define true 1
#define false 0

int main(void){
        int flag = true;
        int score;

        if(flag == true){ flag = startView(); }
        if(flag == true){ score = tetris(); }
        
        if(flag == true){ flag = gameOverView(score); }
        if(flag == true){ rankingView(score); }
}
