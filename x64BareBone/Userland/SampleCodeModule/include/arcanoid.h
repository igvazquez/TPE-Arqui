//arkanoid.h
#ifndef __ARKANOID_H__
#define __ARKANOID_H__

#define BRICKS_PER_COLUMN 3
#define BRICKS_PER_ROW 20

enum gameState {NEWGAME = 0, CONTINUE, WON, LOST};

typedef struct{
        char x, y, vx,vy;
}ball_t;

typedef struct {
        char bricks[BRICKS_PER_COLUMN][BRICKS_PER_ROW];
        char bar_x, speed, lives;
        ball_t ball;
        enum gameState state;
}saveFile_t;

saveFile_t startGame();

#endif
