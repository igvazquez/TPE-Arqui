#include <stdLib.h>

//Defines
    #define BRICKS_PER_COLUMN 3
    #define BRICKS_PER_ROW SCREEN_WIDTH / BRICKS_WIDTH

    #define BRICKS_HEIGHT 2
    #define BRICKS_WIDTH 5

    #define SCREEN_WIDTH 80
    #define SCREEN_HEIGHT 25

    #define BAR_Y 22
    #define BAR_LENGTH 12

    #define INVERT -1

    #define BRICK_SYMBOL_H 'x'
    #define BRICK_SYMBOL_UR 'x'
    #define BRICK_SYMBOL_UL 'x'
    #define BRICK_SYMBOL_DR 'x'
    #define BRICK_SYMBOL_DL 'x'

    #define BAR_SYMBOL_H 'x'
    #define BAR_SYMBOL_UR 'x'
    #define BAR_SYMBOL_UL 'x'
    #define BAR_SYMBOL_DR 'x'
    #define BAR_SYMBOL_DL 'x'

    #define BALL_SYMBOL 'x'

    #define BRICK_PRESENT 1
    #define BRICK_BROKEN 0
//End Defines

//Variables
    typedef struct{
        char x, y, vx,vy;
    }ball_t;

    typedef struct {
        char bricks[BRICKS_PER_COLUMN][BRICKS_PER_ROW];
        ball_t ball;
        char bar_x;
        char lifes;
    }gameState_t;


    char bricks[BRICKS_PER_COLUMN][BRICKS_PER_ROW];
    ball_t ball;
    char bar_x;
    char lifes;
    int lastTick, currentTick;
//END Variables

//Static Functions Prototypes
    static void printBricks();
    static void printBar();
    static void printBall();
    static void removeBall();
    static void removeBrick(char row, char column);
    static void printBricksRow(char row);
    static void printBricksUpperHalf(int row);
    static void printBricksLowerHalf(int row);
    static void cleanScreen();
    static gameState_t play();
    static int gameOver();
    static void moveLeft();
    static void moveRight();
    static void removeBar();
    static gameState_t exitGame();
    static void moveBall();
    static void tryHorizontalBounce();
    static void tryHorizontalBounce()
//End Static Functions Prototypes



void startGame(){
    
    cleanScreen();
    
    for (int i = 0; i < BRICKS_PER_COLUMN; i++)
        for (int k = 0; k < BRICKS_PER_ROW; k++)
            bricks[i][k] = BRICK_PRESENT;

    bar_x = 65;
    ball.x = 5;
    ball.vx = -1;
    ball.vy = 1;
    ball.y = 15;
    lifes = 3;
    
    printBricks();
    printBall();
    printBar();

    play();
}

gameState_t play(){
    
    char c;
    gameState_t ans;
    lastTick = 0;

    while(! gameOver()){

        c = getChar();
        
        if(c == 'a' || c == 'A')
            moveLeft();
        else if(c == 'd' || c == 'D')
            moveRight();
        else if (c == 'x')
            return exitGame();
        
        // for (int i = 0; i < 500000; i++)
        // {
        //     lastTick += 1;
        //     if(getTicksElapsed())
        //         lastTick--;
        // }
        
        if(((currentTick = getTicksElapsed()) % 3 == 0) && lastTick != currentTick){
            lastTick = currentTick;
            moveBall();
        }
    }

    return ans;
}

static int gameOver(){
    return lifes <= 0;
}

static void moveBall(){
    removeBall();
    ball.x += ball.vx;
   // ball.y += ball.vy;
    tryHorizontalBounce();
    //tryVerticalBounce();
    printBall();

}

static void tryHorizontalBounce(){
    if(ball.y < BRICKS_HEIGHT * BRICKS_PER_COLUMN){
        if (bricks[ball.y / BRICKS_HEIGHT][(ball.x + 1) / BRICKS_WIDTH] == BRICK_PRESENT ){
            removeBrick(ball.y / BRICKS_HEIGHT, (ball.x + 1) / BRICKS_WIDTH);
            ball.vx *= INVERT;
        } else if(bricks[ball.y / BRICKS_HEIGHT][(ball.x - 1) / BRICKS_WIDTH] == BRICK_PRESENT ){
            removeBrick(ball.y / BRICKS_HEIGHT, (ball.x - 1) / BRICKS_WIDTH);
            ball.vx *= INVERT;
        }
    }else if ((ball.x + 1) >= SCREEN_WIDTH || (ball.x - 1) <= -1)
        ball.vx *= INVERT;
}

static void tryHorizontalBounce(){
    
}

static gameState_t exitGame(){
    gameState_t gamestate;

    for (int i = 0; i < BRICKS_PER_COLUMN; i++){
        for (int j = 0; j < BRICKS_PER_ROW; j++){
            gamestate.bricks[i][j] = bricks[i][j];   
        }
    }
    
    gamestate.ball = ball;
    gamestate.bar_x = bar_x;
    gamestate.lifes = lifes;

    return gamestate;

}
//Video Functions

    static void moveLeft(){
        if(bar_x > 0){
            removeBar();
            bar_x--;
            printBar();
        }
    }

    static void moveRight(){
        if(bar_x + BAR_LENGTH < SCREEN_WIDTH ){
            removeBar();
            bar_x++;
            printBar();
        }
    }

    static void printBricks(){
        
        setCursorPos(0,0);

        for (int i = 0; i < BRICKS_PER_COLUMN; i++){
            printBricksRow(i);
        }
    }

    static void printBar(){
        //Print Upper Bar
        setCursorPos(BAR_Y, bar_x);
        putChar(BAR_SYMBOL_UL);
        for(int i = 0; i < BAR_LENGTH - 2; i++)
            putChar(BAR_SYMBOL_H);
        putChar(BAR_SYMBOL_UR);

        //Print Lower Bar
        setCursorPos(BAR_Y + 1, bar_x);
        putChar(BAR_SYMBOL_DL);
        for(int i = 0; i < BAR_LENGTH - 2; i++)
            putChar(BAR_SYMBOL_H);
        putChar(BAR_SYMBOL_DR);
    }

    static void removeBar(){
        setCursorPos(BAR_Y, bar_x);

        for(int i = 0; i < BAR_LENGTH ; i++)
            putChar(' ');

        setCursorPos(BAR_Y + 1, bar_x);

        for(int i = 0; i < BAR_LENGTH; i++)
            putChar(' ');
    }

    static void printBall(){
        setCursorPos(ball.y,ball.x);
        putChar(BALL_SYMBOL);
    }

    static void removeBall(){
        setCursorPos(ball.y,ball.x);
        putChar(' ');
    }
    //ToDo
    static void removeBrick(char row, char column){
    }

    static void printBricksRow(char row){
        printBricksUpperHalf(row);
        printBricksLowerHalf(row);
    }

    static void printBricksUpperHalf(int row){
        for (int i = 0; i < BRICKS_PER_ROW; i++){
        if(bricks[row][i] != BRICK_BROKEN){
                putChar(BRICK_SYMBOL_UL);
                for (int k = 0; k < BRICKS_WIDTH - 2; k++)
                    putChar(BRICK_SYMBOL_H);
                putChar(BRICK_SYMBOL_UR);
        }
        }
    }

    static void printBricksLowerHalf(int row){
        for (int i = 0; i < BRICKS_PER_ROW; i++){
        if(bricks[row][i] == BRICK_PRESENT){
                putChar(BRICK_SYMBOL_DL);
                for (int k = 0; k < BRICKS_WIDTH - 2; k++)
                    putChar(BRICK_SYMBOL_H);
                putChar(BRICK_SYMBOL_DR);
        }
        }
    }

    static void cleanScreen(){
        setCursorPos(0,0);

        for (int i = 0; i < SCREEN_HEIGHT * SCREEN_WIDTH; i++)
            putChar(' ');
    }

//End Video Functions