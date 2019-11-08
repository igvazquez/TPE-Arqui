#include <stdLib.h>

//Defines
    #define BRICKS_PER_COLUMN 3
    #define BRICKS_PER_ROW SCREEN_WIDTH / BRICKS_WIDTH

    #define SCREEN_WIDTH 1024
    #define SCREEN_HEIGHT 768

    #define BRICKS_HEIGHT 2
    #define BRICKS_WIDTH 5

    #define INVERT -1
//End Defines
static void drawBricks();
static void drawBall(unsigned int x, unsigned int y);

void startArkanoid(){
    drawBall(500,500);
}

static void drawBricks(){
    for (int i = 500; i < 516; i++)
        for (int j = 500; j < 516; j++)
            drawPixelSys(i,j,0xffffff);
}

static void drawBall(unsigned int x, unsigned int y){
    int color;
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++){
            // UPPER LEFT
            if(i >= 8 - 2 - j)
                color = 0xFFFFFF;
            else
                color = 0x000000;
            drawPixelSys(x + i, y + j, color);
            // UPPER RIGHT
            if(i < j + 2)
                color = 0xFFFFFF;
            else
                color = 0x000000;
            drawPixelSys(x + i + 8, y + j, color);
            // BOTTOM LEFT
             if(i > j - 2)
                color = 0xFFFFFF;
            else
                color = 0x000000;
            drawPixelSys(x + i, y + j + 8, color);
            // BOTTOM RIGHT
             if(i < 7 + 2 - j)
                color = 0xFFFFFF;
            else
                color = 0x000000;
            drawPixelSys(x + i + 8, y + j + 8, color);
        }
}

// (x,y): Upper left corner of brick
// static void drawBrick(unsigned int x, unsigned int y, int color){
//     for (int i = 0; i < ; i++)
//     {
//         /* code */
//     }
    
// }