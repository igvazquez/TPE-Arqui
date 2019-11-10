#include <stdLib.h>

//Defines
    #define BRICKS_PER_COLUMN 3
    #define BRICKS_PER_ROW SCREEN_WIDTH / BRICKS_WIDTH

    #define SCREEN_WIDTH 1024
    #define SCREEN_HEIGHT 768

    #define BRICKS_HEIGHT 32
    #define BRICKS_WIDTH 64

    #define INVERT -1
//End Defines
static void drawBricks();
static void drawBall(unsigned int x, unsigned int y);

void startArkanoid(){
    drawBricks();
    drawBall(500,500);
}

static void drawBricks(){
    for (int k = 0; k < BRICKS_PER_COLUMN; k++){
        for (int i = 0; i < SCREEN_WIDTH; i++)
            for (int j = 0; j < BRICKS_HEIGHT; j++){
                if (i%BRICKS_WIDTH == 0)
                    drawPixel(i,j+k*BRICKS_HEIGHT,0x000000);
                else if(i%BRICKS_WIDTH <=4 || j%BRICKS_HEIGHT<=4)
                    drawPixel(i,j+k*BRICKS_HEIGHT,0x4587f7+k*0xA555BB);
                else if(i%BRICKS_WIDTH >=60 || j%BRICKS_HEIGHT>=28)
                    drawPixel(i,j+k*BRICKS_HEIGHT,0x1c5cc9+k*0xA555BB);
                else
                    drawPixel(i,j+k*BRICKS_HEIGHT,0x2b66cc+k*0xA555BB);
            }
    }
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
            drawPixel(x + i, y + j, color);
            // UPPER RIGHT
            if(i < j + 2)
                color = 0xFFFFFF;
            else
                color = 0x000000;
            drawPixel(x + i + 8, y + j, color);
            // BOTTOM LEFT
             if(i > j - 2)
                color = 0xFFFFFF;
            else
                color = 0x000000;
            drawPixel(x + i, y + j + 8, color);
            // BOTTOM RIGHT
             if(i < 7 + 2 - j)
                color = 0xFFFFFF;
            else
                color = 0x000000;
            drawPixel(x + i + 8, y + j + 8, color);
        }
}

// (x,y): Upper left corner of brick
// static void drawBrick(unsigned int x, unsigned int y, int color){
//     for (int i = 0; i < ; i++)
//     {
//         /* code */
//     }
    
// }