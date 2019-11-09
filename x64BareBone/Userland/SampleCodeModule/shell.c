#include <shell.h>

#define NEGRO 0x000000
#define VERDE_O 0x007F00

typedef struct{
    char * functionName;
    int (*function)();
}functionPackage;

//Static prototypes
    static void loadFunction( char * functionName, int (*function)());
    static void processInstruction(char * userInput);
    static void loadFunctions();
    static int readUserInput(char * userInput, int n);
    static int triggerException0();
    static int triggerException6();
    static int inforeg();
//End static prototypes

int functionCount;
functionPackage functionArray[FUNCTION_NUMBER];

int startShell(){
    
    functionCount = 0;
    loadFunctions();
    
    char userInput[USER_INPUT_MAX_SIZE]; //Le agrego el 0

    setCursorPos(getScreenHeight() - 1, 0);
    printf(LINE_MESSAGE, NEGRO, VERDE_O);
    print("$> ");

    while(readUserInput(userInput, USER_INPUT_MAX_SIZE)){
        processInstruction(userInput);
        printf(LINE_MESSAGE, NEGRO, VERDE_O);
        print("$> ");
    }

    return 0;
}

static int readUserInput(char * userInput, int bufferSize){
    
    char c;
    int counter = 0;
    uint8_t currentTick, lastTick = -1;

    while(counter < bufferSize-1 && (c=getChar())!='\n'){

        if(c){

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
    putChar('\n');
    userInput[counter]=0;  
    return 1; 
}

static void processInstruction(char * userInput){

    for (int i = 0; i < functionCount; i++){
        
       if(!strcmp(userInput, functionArray[i].functionName)){
           functionArray[i].function();
           return;
       }
    }

    print("No existe la funcion ");
    println(userInput);
}

static void loadFunctions(){
    loadFunction( "triggerException0", triggerException0);
    loadFunction( "triggerException6", triggerException6);
    loadFunction( "inforeg", inforeg);
}

static void loadFunction(char * functionName, int (*function)()){
    functionArray[functionCount].functionName = functionName;
    functionArray[functionCount].function = function;
    functionCount++;
}

static int inforeg(){
    printAllRegisters();
    return 0;
}

static int triggerException0(){
    int a = 4/0;
    return a;
}
//TODO
static int triggerException6(){
    print("hola");
    triggerException6Asm();
    return 0;
}

