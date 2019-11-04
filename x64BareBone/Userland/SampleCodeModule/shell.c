#include <shell.h>

int cursorTickState = 0;


static int readUserInput(char * userInput, int n);
static void processInstruction(char * userInput);
static void tickCursor();
static void turnOffCursor();

int startShell(){
    char userInput[USER_INPUT_MAX_SIZE]; //Le agrego el 0

    setCursorPos(SCREEN_HEIGHT - 1, 0);
    printf(LINE_MESSAGE, 0x02);
    print("$ ");

    while(readUserInput(userInput, USER_INPUT_MAX_SIZE)){
        processInstruction(userInput);
        printf(LINE_MESSAGE, 0x02);
        print("$ ");
    }

    return 0;
}

static int readUserInput(char * userInput, int n){
    char c;
    int counter = 0;
    int lastCursorTick = 0;
    int currentTicksElapsed = 0;

    while(counter < n-1 && (c=getChar())!='\n'){

        currentTicksElapsed = getTicksElapsed();
        if(currentTicksElapsed != lastCursorTick && currentTicksElapsed % 10*TICKS_PER_SECOND == 0){ //Para que el cursor parpadee
            tickCursor();
            lastCursorTick = currentTicksElapsed; //Si no hago esto, el while va mas rapido que los ticks.
        }

        if(c){

            turnOffCursor();

            if(c == END_SHELL_KEY) //Cortar ejecucion
                return 0;

            if(c != '\b') //Si es backspace, no siempre hay que imprimirlo
                putChar(c);

            if(c == '\b'){
                if(counter >= 1){
                    putChar(c);
                    counter--;
                }

            } else if(c == '\t')
                userInput[counter++]=' ';

            else
                userInput[counter++]=c;
        }
    }
    turnOffCursor();
    putChar('\n');
    userInput[counter]=0;  
    return 1; 
}

static void processInstruction( char * userInput){
    println(userInput);
}

static void tickCursor(){
    if(cursorTickState){
        putChar('\b');
    } else {
        putCharf(' ', CURSOR_COLOR);
    }
    cursorTickState = !cursorTickState;
}

static void turnOffCursor(){
    if(cursorTickState)
        putChar('\b');
    cursorTickState = 0;
}

