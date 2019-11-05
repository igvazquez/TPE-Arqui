#include <stdLib.h>

//Defines
    #define BRICKS_PER_COLUMN 3
    #define BRICKS_PER_ROW 16

    #define BRICKS_HEIGHT 2
    #define BRICKS_WIDTH 5

    #define SCREEN_WIDTH 80
    #define SCREEN_HEIGHT 25

    #define BAR_Y 23
    #define BAR_LENGTH 12

    #define BRICK_SYMBOL_H '═'
    #define BRICK_SYMBOL_UR '╗'
    #define BRICK_SYMBOL_UL '╔'
    #define BRICK_SYMBOL_DR '╝'
    #define BRICK_SYMBOL_DL '╚'

    #define BAR_SYMBOL_H '─'
    #define BAR_SYMBOL_UR '┐'
    #define BAR_SYMBOL_UL '┌'
    #define BAR_SYMBOL_DR '┘'
    #define BAR_SYMBOL_DL '└'

    #define BALL_SYMBOL 'Ø'

    #define BRICK_PRESENT 1
    #define BRICK_BROKEN 0
//End Defines

//Static Functions Prototypes
    static void printBricks();
    static void printBar();
    static void printBall();
    static void removeBall();
    static void removeBrick(char row, char column);
    static void printBricksRow(char row);
    static void printBricksUpperHalf(char row);
    static void printBricksLowerHalf(char row);
    static void cleanScreen();
//End Static Functions Prototypes


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

void startGame(){
    cleanScreen();
    
    for (int i = 0; i < BRICKS_PER_COLUMN; i++)
        for (int k = 0; k < BRICKS_PER_ROW; k++)
            bricks[i][k] = BRICK_PRESENT;
    bar_x = 34;
    ball.x = 15;
    ball.y = 15;
    
    printBricks();
    printBall();
    printBar();
}

gameState_t play(){
    char c;

    while(! gameOver()){

        c = getChar();
        
        if(c == 'a' || c == 'A')
            moveLeft();
        else if(c == 'd' || c == 'D')
            moveRight();
        else if (c == 'x')
            return exitGame();
        
        if(getTicks() % 6 == 0)
            tryMoveBall();
    }
}
static void moveLeft(){
    if(bar_x >=)

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
    putChar(0);
}
//ToDo
static void removeBrick(char row, char column){

}

static void printBricksRow(char row){
    printBricksUpperHalf(row);
    printBricksLowerHalf(row);
}

static void printBricksUpperHalf(char row){
    for (int i = 0; i < BRICKS_PER_ROW; i++){
       if(bricks[row][i] == BRICK_PRESENT){
            putChar(BRICK_SYMBOL_UL);
            for (int k = 0; k < BRICKS_WIDTH - 2; k++)
                putChar(BRICK_SYMBOL_H);
            putChar(BRICK_SYMBOL_UR);
       }
    }
}

static void printBricksLowerHalf(char row){
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