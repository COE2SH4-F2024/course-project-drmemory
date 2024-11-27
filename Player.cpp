#include "Player.h"


Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;

    // more actions to be included

    playerPos.pos = new Pos;
    playerPos.pos->x = mainGameMechsRef->getBoardSizeX() / 2;
    playerPos.pos->y = mainGameMechsRef->getBoardSizeY() / 2;
    playerPos.symbol = '*';

}

Player::~Player()
{
    // delete any heap members here
    delete mainGameMechsRef;
}

objPos Player::getPlayerPos() const
{
    // return the reference to the playerPos arrray list
    return playerPos;
}

void Player::updatePlayerDir()
{
    char playerInput = mainGameMechsRef->getInput();

    switch(playerInput)
    {                      
        case 'W':
        case 'w':
            if(myDir != DOWN){
                myDir = UP;
            }
            break;        
        case 'A':
        case 'a':
            if(myDir != RIGHT){
                myDir = LEFT;
            }
            break;
        case 'S':
        case 's':
            if(myDir != UP){
                myDir = DOWN;
            }
            break;
        case 'D':
        case 'd':
            if(myDir != LEFT){
                myDir = RIGHT;
            }
            break;
        default:
            break;
    }
}

void Player::movePlayer()
{
    int xLimit = mainGameMechsRef->getBoardSizeX() - 2;
    int yLimit = mainGameMechsRef->getBoardSizeY() - 2;

    switch(myDir)
    {
        case UP:
            playerPos.pos->y--;
            if(playerPos.pos->y > yLimit){
                playerPos.pos->y = 1;}
            break;
        case LEFT:
            playerPos.pos->x--;
            if(playerPos.pos->x < 1){
                playerPos.pos->x = xLimit;}
            break;
        case DOWN:
            playerPos.pos->y++;
            if (playerPos.pos->y < 1){
                playerPos.pos->y = yLimit;}
            break;
        case RIGHT:
            playerPos.pos->x++;
            if(playerPos.pos->x > xLimit){
                playerPos.pos->x = 1;}
            break;
        case STOP:
            break;
        default:
            break;
    }  
    
}

// More methods to be added