#include <stdLib.h>

//Defines
    #define BRICKS_PER_COLUMN 3
    #define BRICKS_PER_ROW SCREEN_WIDTH / BRICKS_WIDTH

    #define SCREEN_WIDTH 1024
    #define SCREEN_HEIGHT 768

    #define BRICKS_HEIGHT 32
    #define BRICKS_WIDTH 64

    #define BAR_WIDTH 128
    #define BAR_HEIGHT 32

    #define RADIUS 8

    #define INVERT -1
//End Defines
static void drawBricks();
static void drawBall(unsigned int x, unsigned int y);
void drawBar(unsigned int x, unsigned int y);
void midPointCircleDraw(int x_centre, int y_centre, int r);

void startArkanoid(){
    drawBricks();
    drawBall(500,500);
    drawBar(500,700);
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
    int r = RADIUS;
    while(r > 0){
        midPointCircleDraw(x,y,r);
        r--;
    }

}

void drawBar(unsigned int x, unsigned int y){
    for (int i = 0; i < BAR_WIDTH; i++){
        for (int j = 0; j < BAR_HEIGHT; j++){
            if(i%BAR_WIDTH <=4 || j%BAR_HEIGHT<=4)
                drawPixel(x+i,y+j,0x4587f7);
            else if(i%BAR_WIDTH >=128 || j%BAR_HEIGHT>=28)
                drawPixel(x+i,y+j,0x1c5cc9);
            else
                drawPixel(x+i,y+j,0x2b66cc);
        }   
    }
}

//https://www.geeksforgeeks.org/mid-point-circle-drawing-algorithm/
void midPointCircleDraw(int x_centre, int y_centre, int r){ 
    int x = r, y = 0; 
      
    // Printing the initial point on the axes  
    // after translation 
    drawPixel(x + x_centre, y + y_centre, 0xffffff); 
      
    // When radius is zero only a single 
    // point will be printed 
    if (r > 0) 
    { 
        drawPixel(x + x_centre, -y + y_centre,0xffffff); 
        drawPixel(-x + x_centre, y + y_centre,0xffffff); 
        drawPixel(y + x_centre, x + y_centre,0xffffff); 
        drawPixel(-y + x_centre, -x + y_centre,0xffffff); 
    } 
      
    // Initialising the value of P 
    int P = 1 - r; 
    while (x > y) 
    {  
        y++; 
          
        // Mid-point is inside or on the perimeter 
        if (P <= 0) 
            P = P + 2*y + 1; 
              
        // Mid-point is outside the perimeter 
        else
        { 
            x--; 
            P = P + 2*y - 2*x + 1; 
        } 
          
        // All the perimeter points have already been printed 
        if (x < y) 
            break; 
          
        // Printing the generated point and its reflection 
        // in the other octants after translation 
        drawPixel(x + x_centre, y + y_centre,0xffffff); 
        drawPixel(-x + x_centre, y + y_centre,0xffffff); 
        drawPixel(x + x_centre, -y + y_centre,0xffffff); 
        drawPixel(-x + x_centre, -y + y_centre,0xffffff); 
          
        // If the generated point is on the line x = y then  
        // the perimeter points have already been printed 
        if (x != y) 
        { 
            drawPixel(y + x_centre, x + y_centre,0xffffff); 
            drawPixel(-y + x_centre, x + y_centre,0xffffff); 
            drawPixel(y + x_centre, -x + y_centre,0xffffff); 
            drawPixel(-y + x_centre, -x + y_centre,0xffffff); 
        } 
    }  
}