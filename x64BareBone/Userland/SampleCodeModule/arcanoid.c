#include <stdLib.h>
#include <stdint.h>
#include <arcanoid.h>

/* TODO:
** -Fix bounces
*/
//Defines

    #define BRICKS_HEIGHT 2
    #define BRICKS_WIDTH 5

    #define SCREEN_WIDTH 120
    #define SCREEN_HEIGHT 48

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

    #define RIGHT_ALIGNMENT 54

    #define BALL_SYMBOL 'x'

    #define BRICK_PRESENT 1
    #define BRICK_BROKEN 0
    #define STARTING_LIVES 3
    #define STARTING_SPEED 9
//End Defines

//Variables
    char bricks[BRICKS_PER_COLUMN][BRICKS_PER_ROW];
    ball_t ball;
    char bar_x;
    char lives;
    int lastTick, currentTick;
    int speed, aux, bricksLeft;
    saveFile_t currentGameState;
//END Variables

//Static Functions Prototypes
    static void printBricks();
    static void printBar();
    static void cleanScreen();
    static void printBall();
    static void removeBall();
    static void removeBrick(int row, int column);
    static void printBricksRow(char row);
    static void printBricksUpperHalf(int row);
    static void printBricksLowerHalf(int row);
    static saveFile_t play();
    static int gameOver();
    static int losingCondition();
    static int winningCondition();
    static void moveLeft();
    static void moveRight();
    static void removeBar();
    static saveFile_t exitGame();
    static void moveBall();
    static void tryHorizontalBounce();
    static void tryVerticalBounce();
    static void setUpBall();
    static void printUserInterface();
    static void updateLives();
    static void endGame();
    static void initialScreen();
    static void loadBall(saveFile_t saveFile);
    static void initiliazeGameVariables();
    static void loadGameVariables(saveFile_t saveFile);
    static ball_t saveBall();
    static saveFile_t saveGameVariables();
//End Static Functions Prototypes

saveFile_t startGame(saveFile_t saveFile){

    if(saveFile.state == NEWGAME){
         initiliazeGameVariables();
    }else if(saveFile.state == WON || saveFile.state == LOST)
        return saveFile;
    else
        loadGameVariables(saveFile);
    
    initialScreen();

    printUserInterface();
    printBricks();
    printBall();
    printBar();

    return play();
}
//Saving & Loading
    static void initiliazeGameVariables(){
        
        for (int i = 0; i < BRICKS_PER_COLUMN; i++)
            for (int k = 0; k < BRICKS_PER_ROW; k++)
                bricks[i][k] = BRICK_PRESENT;

        bricksLeft = BRICKS_PER_COLUMN * BRICKS_PER_ROW;
        bar_x = 40;  
        lives = STARTING_LIVES;
        speed = STARTING_SPEED;
        setUpBall();
    }

    static void loadGameVariables(saveFile_t saveFile){
        
        bricksLeft = 0;
        for (int i = 0; i < BRICKS_PER_COLUMN; i++)
            for (int k = 0; k < BRICKS_PER_ROW; k++)
                if(bricks[i][k] = bricks[i][k])
                    bricksLeft++;

        bar_x = saveFile.bar_x;  
        lives = saveFile.lives;
        speed = saveFile.speed;
        loadBall(saveFile);
    }

    static saveFile_t saveGameVariables(){
        
        saveFile_t ans;

        for (int i = 0; i < BRICKS_PER_COLUMN; i++)
            for (int k = 0; k < BRICKS_PER_ROW; k++)
                ans.bricks[i][k] = bricks[i][k];

        ans.bar_x = bar_x;  
        ans.lives = lives;
        ans.speed = speed;
        ans.ball = saveBall(ans);
    }

    static void setUpBall(){
        
        ball.y = 8;
        ball.x = 40;

        ball.vx = -1;
        ball.vy = 1;
    }

    static void loadBall(saveFile_t saveFile){
        
        ball.y = saveFile.ball.y;
        ball.x = saveFile.ball.x;

        ball.vx = saveFile.ball.vx;
        ball.vy = saveFile.ball.vy;
    }

    static ball_t saveBall(){
        ball_t ans;
        ans.y = ball.y;
        ans.x = ball.x;

        ans.vx = ball.vx;
        ans.vy = ball.vy;
        return ans;
    }
//End Saving & Loading

static void cleanScreen(){
    
    setCursorPos(0,0);
    for (int i = 0; i < getScreenHeight() * getScreenWidth() ; i++){
        putChar(' ');
    }
    setCursorPos(0,0);
}

saveFile_t play(){
    
    char c;
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
            //moveBall();
            lastTick = currentTick;
        }
    }    
    
    return exitGame();
}

saveFile_t exitGame(){

    saveFile_t ans = saveGameVariables();

    if(winningCondition()){
        ans.state = WON;
    }else if(losingCondition()){
        ans.state = LOST;
    }else{
        ans.state = CONTINUE;
    }
    
    return ans;
}

static int gameOver(){
    return losingCondition() || winningCondition();
}

static int losingCondition(){
    return lives <= 0;
}

static int winningCondition(){
    return bricksLeft <= 0;
}

static void moveBall(){
    //removeBall();
    // ball.x += ball.vx;
    // ball.y += ball.vy;
    // if(ball.y < BAR_Y){
    //     tryHorizontalBounce();
    //     tryVerticalBounce();
    // }else{
    //     lives--;
    //     updateLives();
    //     setUpBall();
    // }
    //printBall();
}

static void tryHorizontalBounce(){
    if (ball.x >= SCREEN_WIDTH - 1 || ball.x <= 0)
        ball.vx *= INVERT;
    else if(ball.y < BRICKS_HEIGHT * BRICKS_PER_COLUMN + 1){
        if (bricks[(ball.y - 1) / BRICKS_HEIGHT][(ball.x + 1) / BRICKS_WIDTH] == BRICK_PRESENT ){
            removeBrick((ball.y - 1) / BRICKS_HEIGHT, (ball.x + 1) / BRICKS_WIDTH);
            ball.vx *= INVERT;
        } else if(bricks[(ball.y - 1) / BRICKS_HEIGHT][(ball.x - 1) / BRICKS_WIDTH] == BRICK_PRESENT ){
            removeBrick((ball.y - 1) / BRICKS_HEIGHT, (ball.x - 1) / BRICKS_WIDTH);
            ball.vx *= INVERT;
        }
    }
}

static void tryVerticalBounce(){
    if(ball.y <= 1){
        ball.vy *= INVERT;   
    }else if( ball.y <= BRICKS_HEIGHT * BRICKS_PER_COLUMN + 1){
        if ((ball.y <= BRICKS_HEIGHT * (BRICKS_PER_COLUMN - 1)) && bricks[(ball.y) / BRICKS_HEIGHT][ball.x / BRICKS_WIDTH] == BRICK_PRESENT ){
            removeBrick((ball.y) / BRICKS_HEIGHT, ball.x / BRICKS_WIDTH);
            ball.vy *= INVERT;
        } else if(bricks[(ball.y - 2) / BRICKS_HEIGHT][ball.x / BRICKS_WIDTH] == BRICK_PRESENT ){
            removeBrick((ball.y - 2) / BRICKS_HEIGHT, ball.x / BRICKS_WIDTH);
            ball.vy *= INVERT;
        }
    }else if( (ball.y == BAR_Y - 1) && (ball.x >= bar_x) && (ball.x < bar_x + BAR_LENGTH)){
        ball.vy *= INVERT;
    }
}

//Video Functions
    static void printBall(){
        setCursorPos(ball.y,ball.x);
        putCharf(BALL_SYMBOL, 0x000000,0xAA00BB);
    }

    static void removeBall(){
        setCursorPos(ball.y,ball.x);
        putChar(' ');
    }

    static void printUserInterface(){
        setCursorPos(0,0);
        printf("Lives ", 0xAAAAAA, 0xFFFFFF);
        putCharf(3,0xAAAAAA , 0xFF0000);
        printf(": ", 0xAAAAAA, 0xFFFFFF);
        putCharf(lives + '0', 0xAAAAAA, 0xFFFFFF);
        for (int i = 0; i < RIGHT_ALIGNMENT; i++)
        {
            putCharf(' ', 0xAAAAAA, 0xFFFFFF);
        }
        
        printf("Bricks left: ", 0xAAAAAA, 0xFFFFFF);
        //putCharf()
        
        
    }

    static void updateLives(){
        setCursorPos(0, strlen("Lives  : "));
        putCharf(lives + '0', 0xAA22CC, 0xABCDEF);
    }

    static void updateBricksLeft(){

    }

    static void printBricks(){

        for (int i = 0; i < BRICKS_PER_COLUMN; i++){
            printBricksRow(i);
            

        }
    }

    static void printBar(){
        //Print Upper Bar
        setCursorPos(BAR_Y, bar_x);
        putCharf(BAR_SYMBOL_UL, 0x000000, 0x0000FF);
        for(int i = 0; i < BAR_LENGTH - 2; i++)
            putCharf(BAR_SYMBOL_UL, 0x000000, 0x0000FF);
        putCharf(BAR_SYMBOL_UL, 0x000000, 0x0000FF);

        //Print Lower Bar
        setCursorPos(BAR_Y + 1, bar_x);
        putCharf(BAR_SYMBOL_DL, 0x000000, 0x0000FF);
        for(int i = 0; i < BAR_LENGTH - 2; i++)
            putCharf(BAR_SYMBOL_DL, 0x000000, 0x0000FF);
        putCharf(BAR_SYMBOL_DL, 0x000000, 0x0000FF);
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

    static void removeBar(){
        setCursorPos(BAR_Y, bar_x);

        for(int i = 0; i < BAR_LENGTH ; i++)
            putChar(' ');

        setCursorPos(BAR_Y + 1, bar_x);

        for(int i = 0; i < BAR_LENGTH; i++)
            putChar(' ');
    }

    static void removeBrick(int row, int column){
        bricks[row][column] = BRICK_BROKEN;
        bricksLeft--;
        updateBricksLeft();
        for (int i = 0; i < BRICKS_HEIGHT; i++){
            setCursorPos(row * BRICKS_HEIGHT + i + 1, column * BRICKS_WIDTH);
            for (int k = 0; k < BRICKS_WIDTH; k++)
                putChar(' ');
        }
    }

    static void printBricksRow(char row){
        setCursorPos(1 + row*2, 0);
        printBricksUpperHalf(row);
        setCursorPos(2 + row*2, 0);
        printBricksLowerHalf(row);
    }

    static void printBricksUpperHalf(int row){
        
        for (int i = 0; i < BRICKS_PER_ROW; i++){
            if(bricks[row][i] != BRICK_BROKEN){
                    putCharf(BRICK_SYMBOL_UL, 0x111111, 0x00AA00);
                    for (int k = 0; k < BRICKS_WIDTH - 2; k++)
                        putCharf(BRICK_SYMBOL_H, 0x111111, 0x00AA00);
                    putCharf(BRICK_SYMBOL_UR, 0x111111, 0x00AA00);
            }
        }
    }

    static void printBricksLowerHalf(int row){
        for (int i = 0; i < BRICKS_PER_ROW; i++){
            if(bricks[row][i] == BRICK_PRESENT){
                    putCharf(BRICK_SYMBOL_DL, 0x111111, 0x00AA00);
                    for (int k = 0; k < BRICKS_WIDTH - 2; k++)
                        putCharf(BRICK_SYMBOL_H, 0x111111, 0x00AA00);
                    putCharf(BRICK_SYMBOL_DR, 0x111111, 0x00AA00);
            }
        }
    }

    static void endGame(){
        //cleanScreen();
        setCursorPos(SCREEN_HEIGHT/2,SCREEN_HEIGHT/3);
        printf("Perdiste :p", 0xFFFFFF, 0xFF0000);
    }

    static void initialScreen(){
        cleanScreen();
        setCursorPos(SCREEN_HEIGHT/2,SCREEN_WIDTH/2 - 10);
        printf("Press D to start:", 0xFFFFFF, 0x00FF00);
        char c;

        while ( ((c = getChar()) != 'd') && c != 'D');
        setCursorPos(SCREEN_HEIGHT/2,SCREEN_WIDTH/2 - 10);    
        int len = strlen("Press D to start:");
        for (int i = 0; i < len; i++)
        {
            putChar(' ');
        }
        
    }
//End Video Functions