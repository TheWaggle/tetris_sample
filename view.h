#include <stdio.h>
#include "scoreIO.h"
#define true 1
#define false 0


int startView(void){
char y;
printf("テトリス\n");
    printf("Please Start key push -> y \n");
    scanf("%[y]",&y);

    switch (y){
        case 'y':
            return true;
        default:
            printf("開始する場合はyを入力してください。ゲームを終了します。");
            return false;
    };

}

void rankingView(int score){

    char* score_list = NULL;
    char* pt_score_list[11];
    size_t result_size;

    printf("あなたのスコア=>%d", score);
    score_list = get_score();
    if(score_list != NULL){
        char* p = score_list;
        char* score = p;
        while(p){
            if(*p == ','){
                *p = 0;
                printf("zu: %s\n",score);
                score = p+1;
            }
            p++;
        }
        free(score_list);
    }
}

int gameOverView(int score){
    char buf[40];
    char y;
    printf("Game Over\n");
    printf("あなたのスコア=>%d\n", score);
    printf("Please Ranking View key push -> y \n");
    scanf("%[y]",&y);

        switch (y){
            case 'y':
                // scoreをキャラ型に変換し、postする
                post_score(sprintf(buf,"score=%d",score));
                return true;
            default:
                printf("ランキングを見る場合はyを入力してください。ゲームを終了します。");
                return false;
        };
}