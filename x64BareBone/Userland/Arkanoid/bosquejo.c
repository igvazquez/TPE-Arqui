#include <stdLib.h>
#include <pcInfo.h>
#include <stdint.h>

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

    #define BAR_COLOR NEGRO * 16 + ROJO_O

    #define USER_INTERFACE_COLOR NEGRO * 16 + CELESTE_C

    #define BRICK_PRESENT 1
    #define BRICK_BROKEN 0
//End Defines

//Variables
    
    static uint8_t colors[BRICKS_PER_COLUMN][2] = {
        {NEGRO * 16 + VERDE_C, NEGRO * 16 + VERDE_O}, 
        {NEGRO * 16 + GRIS_C, NEGRO * 16 + GRIS_O}, 
        {NEGRO * 16 + CELESTE_C, NEGRO * 16 + CELESTE_O} };
    
    typedef struct{
        char x, y, vx,vy;
    }ball_t;

    typedef struct {
        char bricks[BRICKS_PER_COLUMN][BRICKS_PER_ROW];
        ball_t ball;
        char bar_x;
        char lives;
    }gameState_t;


    char bricks[BRICKS_PER_COLUMN][BRICKS_PER_ROW];
    ball_t ball;
    char bar_x;
    char lives;
    int lastTick, currentTick;
    int speed, aux;
//END Variables

//Static Functions Prototypes
    static void printBricks();
    static void printBar();
    static void printBall();
    static void removeBall();
    static void removeBrick(int row, int column);
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
    static void tryVerticalBounce();
    static void setUpBall();
    static void printUserInterface();
    static void updateLives();
//End Static Functions Prototypes

void startGame(){
    
    cleanScreen();
    
    for (int i = 0; i < BRICKS_PER_COLUMN; i++)
        for (int k = 0; k < BRICKS_PER_ROW; k++)
            bricks[i][k] = BRICK_PRESENT;

    bar_x = 40;  
    lives = 3;
    speed = 3;
    aux = 0;
    setUpBall();

    printUserInterface();    
    printBricks();
    printBall();
    printBar();

    play();
}

static void setUpBall(){
    
    ball.y = 8;
    ball.x = 40;

    ball.vx = -1;
    ball.vy = 1;
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
        // for (int i = 0; i < BRICKS_PER_COLUMN; i++){
        //     setCursorPos(10 + i,40);
        //     for (int k = 0; k < BRICKS_PER_ROW; k++)
        //     putChar(bricks[i][k] + '0');
        // }

        // setCursorPos(10, 35);
        // putChar(ball.y / 10 + '0');
        // putChar(ball.y % 10 + '0');
        // putChar(' ');
        // putChar(ball.x / 10 + '0');
        // putChar(ball.x % 10 + '0');

        
        if(((currentTick = getTicksElapsed()) % speed == 0) && lastTick != currentTick){
            // aux++;
            // if(aux % 50 == 0)
            //     speed--;
            lastTick = currentTick;
            moveBall();
        }
    }    

    return ans;
}

static int gameOver(){
    return lives <= 0;
}

static void moveBall(){
    removeBall();
    ball.x += ball.vx;
    ball.y += ball.vy;
    if(ball.y < BAR_Y){
        tryHorizontalBounce();
        tryVerticalBounce();
    }else{
        lives--;
        updateLives();
        setUpBall();
    }
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
    }else if (ball.x >= SCREEN_WIDTH - 1 || ball.x <= 0)
        ball.vx *= INVERT;
}

static void tryVerticalBounce(){
    if(ball.y == 0){
        ball.vy *= INVERT;   
    }else if( ball.y <= BRICKS_HEIGHT * BRICKS_PER_COLUMN ){
        if ((ball.y + 1 < BRICKS_HEIGHT * BRICKS_PER_COLUMN) && bricks[(ball.y + 1) / BRICKS_HEIGHT][ball.x / BRICKS_WIDTH] == BRICK_PRESENT ){
            removeBrick((ball.y + 1) / BRICKS_HEIGHT, ball.x / BRICKS_WIDTH);
            ball.vy *= INVERT;
        } else if(bricks[(ball.y - 1) / BRICKS_HEIGHT][ball.x / BRICKS_WIDTH] == BRICK_PRESENT ){
            removeBrick((ball.y - 1) / BRICKS_HEIGHT, ball.x / BRICKS_WIDTH);
            ball.vy *= INVERT;
        }
    }else if( (ball.y == BAR_Y - 1) && (ball.x >= bar_x) && (ball.x < bar_x + BAR_LENGTH)){
        ball.vy *= INVERT;
    }
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
    gamestate.lives = lives;

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

    static void printUserInterface(){
        setCursorPos(0,0);
        printf("Lives ", USER_INTERFACE_COLOR);
        putCharf(3, NEGRO * 16 + ROJO_O);
        printf(": ", USER_INTERFACE_COLOR);
        putCharf(lives + '0', USER_INTERFACE_COLOR);
        
        
    }

    static void updateLives(){
        setCursorPos(0, strlen("Lives  : "));
        putCharf(lives + '0', USER_INTERFACE_COLOR);

    }

    static void printBricks(){
        
        setCursorPos(1,0);

        for (int i = 0; i < BRICKS_PER_COLUMN; i++){
            printBricksRow(i);
        }
    }

    static void printBar(){
        //Print Upper Bar
        setCursorPos(BAR_Y, bar_x);
        putCharf(BAR_SYMBOL_UL, BAR_COLOR);
        for(int i = 0; i < BAR_LENGTH - 2; i++)
            putCharf(BAR_SYMBOL_UL, BAR_COLOR);
        putCharf(BAR_SYMBOL_UL, BAR_COLOR);

        //Print Lower Bar
        setCursorPos(BAR_Y + 1, bar_x);
        putCharf(BAR_SYMBOL_DL, BAR_COLOR);
        for(int i = 0; i < BAR_LENGTH - 2; i++)
            putCharf(BAR_SYMBOL_DL, BAR_COLOR);
        putCharf(BAR_SYMBOL_DL, BAR_COLOR);
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
        putCharf(BALL_SYMBOL, NEGRO * 16 + VIOLETA);
    }

    static void removeBall(){
        setCursorPos(ball.y,ball.x);
        putChar(' ');
    }

    static void removeBrick(int row, int column){
        bricks[row][column] = BRICK_BROKEN;
        for (int i = 0; i < BRICKS_HEIGHT; i++){
            setCursorPos(row * BRICKS_HEIGHT + i, column * BRICKS_WIDTH);
            for (int k = 0; k < BRICKS_WIDTH; k++)
                putChar(' ');
        }
    }

    static void printBricksRow(char row){
        printBricksUpperHalf(row);
        printBricksLowerHalf(row);
    }

    static void printBricksUpperHalf(int row){
        
        uint8_t format;
        for (int i = 0; i < BRICKS_PER_ROW; i++){
            format = colors[row][i % 2];
            if(bricks[row][i] != BRICK_BROKEN){
                    putCharf(BRICK_SYMBOL_UL,format);
                    for (int k = 0; k < BRICKS_WIDTH - 2; k++)
                        putCharf(BRICK_SYMBOL_H,format);
                    putCharf(BRICK_SYMBOL_UR,format);
            }
        }
    }

    static void printBricksLowerHalf(int row){
        uint8_t format;
        for (int i = 0; i < BRICKS_PER_ROW; i++){
            format = colors[row][i % 2];
            if(bricks[row][i] == BRICK_PRESENT){
                    putCharf(BRICK_SYMBOL_DL, format);
                    for (int k = 0; k < BRICKS_WIDTH - 2; k++)
                        putCharf(BRICK_SYMBOL_H, format);
                    putCharf(BRICK_SYMBOL_DR,format);
            }
        }
    }

    static void cleanScreen(){
        setCursorPos(0,0);

        for (int i = 0; i < SCREEN_HEIGHT * SCREEN_WIDTH; i++)
            putChar(' ');
    }

//End Video Functions