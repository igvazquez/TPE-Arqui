#include <shell.h>
#include <clock.h>
#include <stdLib.h>

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
    static int printTime();
    static int triggerException6();
    static int inforeg();
    static int clear();
//End static prototypes

int functionCount;
functionPackage functionArray[FUNCTION_NUMBER];

int startShell(){
    // char s[] = "asd";
    usrClearScreen();
    // setCursorPos(getScreenHeight()-1,0);
    // print(s);

    /* // ERROR 1
    int a = 12;
    ncPrintBase(21,10);
    ncPrintBase(a,10);
    ncPrintBase(12,10);
    */

  //ERROR 2 CANTIDAD DE PRINTS
    // int a=3;
    // putChar(a + '0');
    // print("Test funciona");
    // print("1");
    // print("2");
    // print("3");
    // print("4");
    // putChar(a + '2');
    // loadFunctions();
//ERROR 3 NCPRINTBASE CON VARIABLE
    uint64_t a = 300002;
    ncPrintBase(a, 10);
   
//ERROR 4 MAS DE 3 FUNCIONES LO ROMPE   
        // inforeg();
        // printTime();
        // printTime();
        // triggerException0();
//     arkanoid();
//     triggerException6();
        // inforeg();
        // clear();
        // printTime();
   // while (1);

   //ERROR 5 SI HAGO UN ARRAY DE 50 DE CHAR FUNCIONA PERO DE INT NO
   //char array[USER_INPUT_MAX_SIZE];
   // uint8_t array[USER_INPUT_MAX_SIZE];
   // uint16_t array[USER_INPUT_MAX_SIZE];
  //  uint32_t array[USER_INPUT_MAX_SIZE]; HASTA ACA LLEGAMOS
   //int array [USER_INPUT_MAX_SIZE];

    // END TEST

    loadFunctions();
    //char userInput[USER_INPUT_MAX_SIZE]; //Le agrego el 0
    //print("1");
    //print("1");
    
    // setCursorPos(getScreenHeight() - 1, 0);
    // printf(LINE_MESSAGE, NEGRO, VERDE_O);
    // print("$> ");

    // while(readUserInput(userInput, USER_INPUT_MAX_SIZE)){
    //     processInstruction(userInput);
    //     printf(LINE_MESSAGE, NEGRO, VERDE_O);
    //     print("$> ");
    // }

    // return 0;
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
          // print("aca");
           functionArray[i].function();
           return;
        }
    }
        print("si");

    print("No existe la funcion ");
    println(userInput);
}

static void loadFunctions(){
    loadFunction( "inforeg", inforeg);
    loadFunction("clear", clear);
    loadFunction("clock",printTime);
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
