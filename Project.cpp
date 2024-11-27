#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "GameMechs.h"
#include "Player.h" //temp including for testing

using namespace std;

#define DELAY_CONST 100000

GameMechs* gameMech = nullptr;  


bool exitFlag;

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);

char input;

int main(void)
{

    Initialize();
    MacUILib_clearScreen();


    while(exitFlag == false)  
    {
        GetInput();
        RunLogic();
        DrawScreen();
        LoopDelay();
    }

    CleanUp();

}


void Initialize(void)
{
    MacUILib_init();
    MacUILib_clearScreen();
    gameMech = new GameMechs(30,15);

    exitFlag = false;
}

void GetInput(void)
{   char input = MacUILib_getChar();  
    gameMech->setInput(input);

    if (input == '!') {
        gameMech->setExitTrue();
    }

   
}

void RunLogic(void){
    if (gameMech->getExitFlagStatus())
    {
        exitFlag = true;  
    }

    gameMech->incrementScore();   
  
    
    
}

void DrawScreen(void)
{       
    int Board_Width = gameMech->getBoardSizeX(); 
    int Board_Len = gameMech->getBoardSizeY(); 

        MacUILib_clearScreen();    


    for (int y = 0; y < Board_Len; ++y) {   /
        for (int x = 0; x < Board_Width; ++x) {  
            if (x == 0 || x == Board_Width - 1 || y == 0 || y == Board_Len - 1) {
                MacUILib_printf("#"); 
            } else {
                MacUILib_printf(" ");
            }
        }
        MacUILib_printf("\n");
    }

    MacUILib_printf("Score: %d\n", gameMech->getScore());
    if (gameMech->getExitFlagStatus()) {
        MacUILib_printf("Exiting the game\n");
    }

    gameMech->clearInput();



}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST);
}


void CleanUp(void)
{
    MacUILib_clearScreen(); 
    delete gameMech;   

    MacUILib_uninit();
}
