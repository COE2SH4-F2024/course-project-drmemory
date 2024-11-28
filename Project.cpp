#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "GameMechs.h"
#include "Player.h" //temp including for testing

using namespace std;

#define DELAY_CONST 100000

GameMechs* gameMech = nullptr;  

Player* playerObject = nullptr;


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

    input = 0;
    
    gameMech = new GameMechs(30,15);

    playerObject = new Player(gameMech, 5, 5);

    exitFlag = false;
}

void GetInput(void)
{   
    if(MacUILib_hasChar())
    {
        input = MacUILib_getChar();
    }

    gameMech->setInput(input);

    

   
}

void RunLogic(void){

    if (input == '!') {
        gameMech->setExitTrue();
    }

    if (gameMech->getExitFlagStatus())
    {
        exitFlag = true;  
    }

    // gameMech->incrementScore();   
  
    playerObject->updatePlayerDir();
    playerObject->movePlayer();
    
}

void DrawScreen(void)
{

    MacUILib_clearScreen();  

    int Board_Width = gameMech->getBoardSizeX(); 
    int Board_Len = gameMech->getBoardSizeY(); 

    int playerX = playerObject->getPlayerPos().pos->x;
    int playerY = playerObject->getPlayerPos().pos->y;
    char playerSymbol = playerObject->getPlayerPos().getSymbol();
    
    // int x, y;
    // char board[Board_Len][Board_Width]; // y represents rows, x represents columns
    // for(y=0; y<=Board_Len; y++)
    // {
    //     for(x=0; x<=Board_Width; x++)
    //     {
    //         if(y!=0 && y!=Board_Len)
    //         {
    //             if(x==0 || x == Board_Width)
    //             {
    //                 board[y][x] = '#';
    //             } 
    //             else
    //             {
    //                 board[y][x] = ' ';
    //             }
    //         }
    //         else
    //         {
    //             board[y][x] = '#';

    //         }
    //     }
    // }

    // board[playerY][playerX] = playerSymbol;

    // for(y=0; y<=Board_Len; y++)
    // {
    //     for(x=0; x<=Board_Width; x++)
    //     {
    //         MacUILib_printf("%c", board[y][x]);
    //     }
    //     MacUILib_printf("\n");
    // }

    for (int y = 0; y < Board_Len; ++y) {   
        for (int x = 0; x < Board_Width; ++x) {  
            if (x == 0 || x == Board_Width - 1 || y == 0 || y == Board_Len - 1) {
                MacUILib_printf("#"); 
            } else if (x == playerX && y == playerY){
                MacUILib_printf("%c", playerSymbol);} 
            else {
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
    delete playerObject; 

    MacUILib_uninit();
}
