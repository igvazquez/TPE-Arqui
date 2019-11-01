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

char bricks[BRICKS_PER_COLUMN][BRICKS_PER_ROW];

typedef struct{
    char x, y, vx,vy;
}ball_t;

ball_t ball;

char bar_x;

void startGame(){
    for (int i = 0; i < BRICKS_PER_COLUMN; i++)
        for (int k = 0; k < BRICKS_PER_ROW; k++)
            bricks[i][k] = BRICK_PRESENT;
}

void printBricks(){
    
    setCursorPos(0,0);

    for (int i = 0; i < BRICKS_PER_COLUMN; i++){
        printBricksRow(i);
    }
}

void printBar(){
    //Print Upper Bar
    setCursorPos(BAR_Y, bar_x);
    putchar(BAR_SYMBOL_UL);
    for(int i = 0; i < BAR_LENGTH - 2; i++)
        putchar(BAR_SYMBOL_H);
    putchar(BAR_SYMBOL_UR);

    //Print Lower Bar
    setCursorPos(BAR_Y + 1, bar_x);
    putchar(BAR_SYMBOL_DL);
    for(int i = 0; i < BAR_LENGTH - 2; i++)
        putchar(BAR_SYMBOL_H);
    putchar(BAR_SYMBOL_DR);
}

void printBall(){
    setCursorPos(ball.y,ball.x);
    putchar(BALL_SYMBOL);
}

void removeBall(){
    setCursorPos(ball.y,ball.x);
    putchar(0);
}

void removeBrick(char row, char column){

}

void printBricksRow(char row){
    printBricksUpperHalf(row);
    printBricksLowerHalf(row);
}

void printBricksUpperHalf(char row){
    for (int i = 0; i < BRICKS_PER_ROW; i++){
       if(bricks[row][i] == BRICK_PRESENT){
            putchar(BRICK_SYMBOL_UL);
            for (int k = 0; k < BRICKS_WIDTH - 2; k++)
                putchar(BRICK_SYMBOL_H);
            putchar(BRICK_SYMBOL_UR);
       }
    }
}

void printBricksLowerHalf(char row){
    for (int i = 0; i < BRICKS_PER_ROW; i++){
       if(bricks[row][i] == BRICK_PRESENT){
            putchar(BRICK_SYMBOL_DL);
            for (int k = 0; k < BRICKS_WIDTH - 2; k++)
                putchar(BRICK_SYMBOL_H);
            putchar(BRICK_SYMBOL_DR);
       }
    }
}