#include <stdLib.h>

//Defines
    #define BRICKS_PER_COLUMN 3
    #define BRICKS_PER_ROW 16

    #define BRICKS_HEIGHT 2
    #define BRICKS_WIDTH 5

    #define SCREEN_WIDTH 80
    #define SCREEN_HEIGHT 25

    #define BAR_Y 22
    #define BAR_LENGTH 12

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
    static void play();
    static int gameOver();
    static void moveLeft();
    static void moveRight();
    static void removeBar();
//End Static Functions Prototypes

int bricks[BRICKS_PER_COLUMN][BRICKS_PER_ROW];

typedef struct{
    char x, y, vx,vy;
}ball_t;

ball_t ball;

char bar_x;

void startGame(){
    cleanScreen();
    
    for (int i = 0; i < BRICKS_PER_COLUMN; i++)
        for (int k = 0; k < BRICKS_PER_ROW; k++)
            bricks[i][k] = BRICK_PRESENT;
    bar_x = 65;
    ball.x = 15;
    ball.y = 15;
    
    printBricks();
    printBall();
    printBar();

    play();
}

static void play(){
    char c;

    while(! gameOver()){

        c = getChar();
        
        if(c == 'a' || c == 'A')
            moveLeft();
        else if(c == 'd' || c == 'D')
            moveRight();
        // else if (c == 'x')
        //     exitGame();
        
        if(getTicksElapsed() % 6 == 0)
            tryMoveBall();
    }
}
//ToDo
static int gameOver(){
    return 0;
}

static void tryMoveBall(){
    
}

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