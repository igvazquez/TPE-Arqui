#include <shell.h>
#include <clock.h>
#include <stdLib.h>

#define NEGRO 0x000000
#define VERDE_O 0x007F00

saveFile_t arcanoidSaveFile;

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
    static int printTime();
    static int triggerException6();
    static int inforeg();
    static int arkanoid();
    static int clear();
//End static prototypes

int functionCount;
functionPackage functionArray[FUNCTION_NUMBER];

int startShell(){
    
    usrClearScreen();
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
        
        if(!strcmp( userInput, functionArray[i].functionName)){
          functionArray[i].function();
           return;
        }
     }

    print("No existe la funcion ");
    println(userInput);
}

static void loadFunctions(){
    loadFunction( "inforeg", inforeg);
    loadFunction("clear", clear);
    loadFunction("clock",printTime);
    loadFunction("arcanoid", arkanoid);
    loadFunction( "triggerException0", triggerException0);
    loadFunction( "triggerException6", triggerException6);
}

static void loadFunction(char * functionName, int (*function)()){
    functionArray[functionCount].functionName = functionName;
    functionArray[functionCount].function = function;
    functionCount++;
}
//Modules
    static int printTime(){
        int aux = bsdToInt(getCurrentTime(HOURS));
        if( aux < 3)
            aux = 24 + aux - 3;
        else
            aux -= 3;
        
        ncPrintBase(aux, 10);

        putChar(':');

        ncPrintBase(bsdToInt(getCurrentTime(MINUTES)), 10);

        putChar(':');

        ncPrintBase(bsdToInt(getCurrentTime(SECONDS)), 10);
        
        putChar('\n');
        return 0;

    }

    static int arkanoid(){
        arcanoidSaveFile = startGame(arcanoidSaveFile);
        usrClearScreen();  
        return 0;
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

    static int clear(){
        usrClearScreen();
        return 0;
    }
//END Modules
