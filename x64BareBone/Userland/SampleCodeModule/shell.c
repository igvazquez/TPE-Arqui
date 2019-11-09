#include <shell.h>

int cursorTickState = 0;
typedef struct{
    char * functionName;
    int (*function)();
}functionPackage;

static int readUserInput(char * userInput, int n);
static void processInstruction(char * userInput, int functionCount, functionPackage functionArray[]);
static void tickCursor();
static void turnOffCursor();
static void loadFunctions(functionPackage functionArray[], int * functionCount);
static void loadFunction(functionPackage functionArray[], int * functionCount, char * functionName, int (*function)());
static int triggerException0();
static int triggerException6();
int triggerException6Asm();
static int inforeg();


int startShell(){

    functionPackage functionArray[FUNCTION_NUMBER];
    int functionCount = 0;
    loadFunctions(functionArray, &functionCount);
    
    char userInput[USER_INPUT_MAX_SIZE]; //Le agrego el 0

    setCursorPos(getScreenHeight() - 1, 0);
    printf(LINE_MESSAGE, 0x000000, 0x007F00);
    print("$> ");

    while(readUserInput(userInput, USER_INPUT_MAX_SIZE)){
        //SI DESCOMENTAMOS ESTA FUNCION, A PESAR DE ESTAR TODA COMENTADA, EXPLOTA.
        processInstruction(userInput, functionCount, functionArray);
        printf(LINE_MESSAGE, 0x000000, 0x007F00);
        print("$> ");
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

        //NO ES MUCHO 10*TICKS_PER_SECOND ?? CAPAZ SE ESTA TRAYENDO MAL LOS TIMER TICKS?
        // if(currentTicksElapsed != lastCursorTick && currentTicksElapsed % 10*TICKS_PER_SECOND == 0){ //Para que el cursor parpadee
        //     tickCursor();
        //     lastCursorTick = currentTicksElapsed; //Si no hago esto, el while va mas rapido que los ticks.
        // }

        if(c){

            //turnOffCursor();

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
    //turnOffCursor();
    putChar('\n');
    userInput[counter]=0;  
    return 1; 
}

static void processInstruction(char * userInput, int functionCount, functionPackage functionArray[]){
    //print("HOLA");
    // for (int i = 0; i < functionCount; i++){
        
    //    if(!strcmp(userInput, functionArray[i].functionName)){
    //        functionArray[i].function();
    //        return;
    //    }
    // }

    // print("No existe la funcion ");
    // println(userInput);
    
}

static void tickCursor(){
    if(cursorTickState){
        putChar('\b');
    } else {
        putCharf(' ', CURSOR_COLOR, DEFAULT_FONT_COLOR);
    }
    cursorTickState = !cursorTickState;
}

static void turnOffCursor(){
    if(cursorTickState)
        putChar('\b');
    cursorTickState = 0;
}

static void loadFunctions(functionPackage functionArray[], int * functionCount){
    loadFunction(functionArray, functionCount, "triggerException0", triggerException0);
    loadFunction(functionArray, functionCount, "triggerException6", triggerException6);
    loadFunction(functionArray, functionCount, "inforeg", inforeg);
}

static void loadFunction(functionPackage functionArray[], int * functionCount, char * functionName, int (*function)()){
    functionArray[*functionCount].functionName = functionName;
    functionArray[*functionCount].function = function;
    *functionCount = *functionCount + 1;
}
static int inforeg(){
    getAllRegisters();
    return 0;
}

static int triggerException0(){
    int a = 4/0;
    return 0;
}
static int triggerException6(){
    triggerException6Asm();
    return 0;
}

