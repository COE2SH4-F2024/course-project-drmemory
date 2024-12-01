#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "GameMechs.h"
#include "Player.h" 
#include "Food.h"


using namespace std;

#define DELAY_CONST 100000

GameMechs* gameMech = nullptr;  

Player* playerObject = nullptr;
Food* food = nullptr; // did


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
    food = new Food();

    playerObject = new Player(gameMech, food, 10);
    
    //food->generateFood(playerObject->getPlayerPos()); // praying it works now hardcoded location of board in generate food(WILL TRY TO FIX)
    food->generateFood(playerObject->getPlayerPos()->getHeadElement());
    
    exitFlag = false;
}

void GetInput(void)
{   
    if(MacUILib_hasChar()) // collect input if input is detected
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

    gameMech->incrementScore();   

    playerObject->updatePlayerDir();
    playerObject->movePlayer();

}

void DrawScreen(void) {
    MacUILib_clearScreen();

    int Board_Width = gameMech->getBoardSizeX(); 
    int Board_Len = gameMech->getBoardSizeY();
    bool occupied;

    // *** Code from prev iteration:

    // int playerX = playerObject->getPlayerPos()->getHeadElement().pos->x;
    // int playerY = playerObject->getPlayerPos()->getHeadElement().pos->y;
    // char playerSymbol = playerObject->getPlayerPos().getSymbol();

    // *** code from prev it ends here

    objPos foodPos = food->getFoodPos();
    int foodX = foodPos.pos->x;
    int foodY = foodPos.pos->y;
    char foodSymbol = foodPos.symbol;

    MacUILib_printf("Food Position: (%d, %d)\nHi Pookie :)\n", foodX, foodY);  

    for (int y = 0; y < Board_Len; ++y) {   
        for (int x = 0; x < Board_Width; ++x) { 
            occupied = false; 
            if (x == 0 || x == Board_Width - 1 || y == 0 || y == Board_Len - 1) {
                MacUILib_printf("#");
                continue;  // skips rest of code in x-loop iteration - boarder would conflict 
            }

            for(int i = 0; i < playerObject->getPlayerPos()->getSize(); i++){ // iterate through body of snake to account for every element
                
                if(x == playerObject->getPlayerPos()->getElement(i).pos->x && y == playerObject->getPlayerPos()->getElement(i).pos->y){
                    MacUILib_printf("%c", playerObject->getPlayerPos()->getElement(i).symbol);
                    occupied = true; // set occupied flag to true to prevent blank spaced " " from overwriting player
                    break; // break out of current i-loop - does not need to check rest of coordinates (ONLY ONE VALID SET PER ELEMENT!)
                }
            }

            if(!occupied){ // only print blank space " " if area is not occupied by another item - prevents overwriting
                
                // hi pookie, for multiple food, if u have to use an array, i think using a 
                // loop like the player one could work?
                // if that is the case, we can get rid of the ifs in here and just leave it as 
                // if(!occupied){
                // MacUILib_printf(" ");}

                if (x == foodX && y == foodY) { 
                MacUILib_printf("%c", foodSymbol);  
                } else {
                MacUILib_printf(" ");  
                }
            }

        }
        MacUILib_printf("\n");
    }

    MacUILib_printf("Score: %d\n", gameMech->getScore());

    if (gameMech->getExitFlagStatus()) {
        MacUILib_printf("Exiting the game\n");
    }

    if (gameMech->getLoseFlagStatus()) {
        MacUILib_printf("You Lose! :(\n");
    }

}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST);
}


void CleanUp(void)
{
    // MacUILib_clearScreen(); 

    // free up dynamically allocated memory
    delete gameMech;  
    delete playerObject; 
    delete food;

    MacUILib_uninit();
}