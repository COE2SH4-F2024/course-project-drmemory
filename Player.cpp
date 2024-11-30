#include "Player.h"

Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;

    // more actions to be included
    int xInitial = 3;
    int yInitial = 5;

    playerPosList = new objPosArrayList();
    playerPosList->insertHead(objPos(xInitial, yInitial, 'M'));
    // playerPos = objPos();
    // playerPos.setObjPos(xInitial, yInitial, '*');
}

Player::Player(GameMechs* thisGMRef, int size)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;

    // more actions to be included
    int xInitial = mainGameMechsRef->getBoardSizeX() / 2;
    int yInitial = mainGameMechsRef->getBoardSizeY() / 2;

    playerPosList = new objPosArrayList();
    for(int i = 0; i < size; i++){
        playerPosList->insertHead(objPos(xInitial + i, yInitial, 'M'));
    }
}

//destructor
Player::~Player()
{
    // delete any heap members here
    delete playerPosList;
}

//copy assignment operator

Player& Player::operator= (const Player &p){
    if(this != &p)
    {
        this->mainGameMechsRef = p.mainGameMechsRef;
        this->myDir = p.myDir;
        // this->playerPos.pos->x = p.playerPos.pos->x;
        // this->playerPos.pos->y = p.playerPos.pos->y;
        // this->playerPos.symbol = p.playerPos.symbol;    
                // this->playerPos.setObjPos(p.playerPos.pos->x, p.playerPos.pos->y, p.playerPos.symbol);
    }
    return *this;
    }
// objPos Player::getPlayerPos() const
objPosArrayList* Player::getPlayerPos() const
{
    // return the reference to the playerPos arrray list
    // return playerPos;
    return playerPosList;
}

void Player::updatePlayerDir()
{
    char playerInput = mainGameMechsRef->getInput();

    if(playerInput != '0')
    {
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
        playerInput = '0';
    }
}

void Player::movePlayer()
{
    int xLimit = mainGameMechsRef->getBoardSizeX() - 2;
    int yLimit = mainGameMechsRef->getBoardSizeY() - 2;

    switch(myDir)
    {
        case UP:
            // playerPos.pos->y--;
            // if(playerPos.pos->y < 1){
            //     playerPos.pos->y = yLimit;}
            if(playerPosList->getHeadElement().pos->y == 1){
                playerPosList->insertHead(objPos(playerPosList->getHeadElement().pos->x, yLimit, playerPosList->getHeadElement().symbol));
                playerPosList->removeTail();
            } else{
                playerPosList->insertHead(objPos(playerPosList->getHeadElement().pos->x, playerPosList->getHeadElement().pos->y - 1, playerPosList->getHeadElement().symbol));
                playerPosList->removeTail();
            }
            break;
        case LEFT:
        //     playerPos.pos->x--;
        //     if(playerPos.pos->x < 1){
        //         playerPos.pos->x = xLimit;}
            if(playerPosList->getHeadElement().pos->x == 1){
                    playerPosList->insertHead(objPos(xLimit, playerPosList->getHeadElement().pos->y, playerPosList->getHeadElement().symbol));
                    playerPosList->removeTail();
            } else{
                playerPosList->insertHead(objPos(playerPosList->getHeadElement().pos->x - 1, playerPosList->getHeadElement().pos->y, playerPosList->getHeadElement().symbol));
                playerPosList->removeTail();
            }
            break;
        case DOWN:
        //     playerPos.pos->y++;
        //     if (playerPos.pos->y > yLimit){
        //         playerPos.pos->y = 1;}
            if(playerPosList->getHeadElement().pos->y == yLimit){
                playerPosList->insertHead(objPos(playerPosList->getHeadElement().pos->x, 1, playerPosList->getHeadElement().symbol));
                playerPosList->removeTail();
            } else{
                playerPosList->insertHead(objPos(playerPosList->getHeadElement().pos->x, playerPosList->getHeadElement().pos->y + 1, playerPosList->getHeadElement().symbol));
                playerPosList->removeTail();
            }
            break;
        case RIGHT:
        //     playerPos.pos->x++;
        //     if(playerPos.pos->x > xLimit){
        //         playerPos.pos->x = 1;}
            if(playerPosList->getHeadElement().pos->x == xLimit){
                playerPosList->insertHead(objPos(1, playerPosList->getHeadElement().pos->y, playerPosList->getHeadElement().symbol));
                playerPosList->removeTail();
            } else{
                playerPosList->insertHead(objPos(playerPosList->getHeadElement().pos->x + 1, playerPosList->getHeadElement().pos->y, playerPosList->getHeadElement().symbol));
                playerPosList->removeTail();
            }
            break;
        //     break;
        case STOP:
            break;
        default:
            break;
    }  

}

// More methods to be added
