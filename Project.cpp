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
Food* food = nullptr; 

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
    food = new Food(gameMech);

    playerObject = new Player(gameMech, food);
    
    food->generateFood(playerObject->getPlayerPos());
    
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

    playerObject->updatePlayerDir();
    playerObject->movePlayer();

}

void DrawScreen(void) {
    MacUILib_clearScreen();

    int Board_Width = gameMech->getBoardSizeX(); 
    int Board_Len = gameMech->getBoardSizeY();
    bool occupied;

    MacUILib_printf("Food Positions: (%d, %d), (%d, %d), (%d, %d), (%d, %d), (%d, %d)\n",
        food->getFoodPos()->getElement(0).pos->x, food->getFoodPos()->getElement(0).pos->y, 
        food->getFoodPos()->getElement(1).pos->x, food->getFoodPos()->getElement(1).pos->y,
        food->getFoodPos()->getElement(2).pos->x, food->getFoodPos()->getElement(2).pos->y,
        food->getFoodPos()->getElement(3).pos->x, food->getFoodPos()->getElement(3).pos->y,
        food->getFoodPos()->getElement(4).pos->x, food->getFoodPos()->getElement(4).pos->y
        );  

    MacUILib_printf("Player Positions: (%d, %d)\n", playerObject->getPlayerPos()->getHeadElement().pos->x, playerObject->getPlayerPos()->getHeadElement().pos->y);

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

            if(!occupied){
                for(int i = 0; i < food->getFoodPos()->getSize(); i++){
                    if(x == food->getFoodPos()->getElement(i).pos->x && y == food->getFoodPos()->getElement(i).pos->y){
                        MacUILib_printf("%c", food->getFoodPos()->getElement(i).symbol);
                        occupied = true;
                        break;
                    }
                }
            }

            if(!occupied){ // only print blank space " " if area is not occupied by another item - prevents overwriting
                MacUILib_printf(" ");}
        }
        MacUILib_printf("\n");
    }

    MacUILib_printf("Score: %d\n", gameMech->getScore());

    MacUILib_printf("Input '!' to Quit Game\n");
    

    if (gameMech->getLoseFlagStatus()) {
        MacUILib_printf("COLLISION WITH TAIL DETECTED! YOU LOSE!!! :(\n\n");
    }

    if (gameMech->getExitFlagStatus()) {
        MacUILib_printf("Exiting the game...\n");
    }
        MacUILib_printf("Snake Length: %d\n", playerObject->getPlayerPos()->getSize());
        MacUILib_printf("Controls: W-UP,S-DOWN-D-RIGHT,A-LEFT");

}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST);
}


void CleanUp(void)
{
    // free up dynamically allocated memory
    delete gameMech;  
    delete playerObject; 
    delete food;

    MacUILib_uninit();}
