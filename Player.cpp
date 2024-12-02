#include "Player.h"

Player::Player(GameMechs* thisGMRef, Food* foodRef) // default constructor, creates a snake that is 1 char long
{
    mainGameMechsRef = thisGMRef;
    foodReference = foodRef;
    myDir = STOP;

    // sets the initial position of the snake to the middle of the board
    int xInitial = mainGameMechsRef->getBoardSizeX() / 2;
    int yInitial = mainGameMechsRef->getBoardSizeY() / 2;

    playerPosList = new objPosArrayList();
    playerPosList->insertHead(objPos(xInitial, yInitial, 'M')); 

    // code from prev iteration:
    // playerPos = objPos();
    // playerPos.setObjPos(xInitial, yInitial, '*');
}

Player::Player(GameMechs* thisGMRef, Food* foodRef, int size) // additional constructor, creates a snake of a custom length
{
    mainGameMechsRef = thisGMRef;
    foodReference = foodRef;
    myDir = STOP;

    int xInitial = mainGameMechsRef->getBoardSizeX() / 2 - size / 2; // shift head left to leave space for rest of body
    int yInitial = mainGameMechsRef->getBoardSizeY() / 2; // snake is positioned horizontally, initial y is same for all elements -> can stay in middle

    playerPosList = new objPosArrayList();
    for(int i = 0; i < size; i++){
        playerPosList->insertHead(objPos(xInitial + i, yInitial, 'M')); // snake grows in horizontal direction
    }
}

Player::Player(const Player &p) // copy constructor
{
    mainGameMechsRef = p.mainGameMechsRef;
    myDir = p.myDir;
    playerPosList = new objPosArrayList();
    playerPosList = p.playerPosList;
}

//destructor
Player::~Player()
{
    delete playerPosList; // player array is dynamically allocated, must free memory
}

//copy assignment operator
Player& Player::operator= (const Player &p){
    if(this != &p)
    {
        this->mainGameMechsRef = p.mainGameMechsRef;
        this->myDir = p.myDir;
        this->playerPosList = p.playerPosList;
    }
    return *this;
}


objPosArrayList* Player::getPlayerPos() const
{
    return playerPosList; // returns reference to the playerPos arrray list
}

void Player::updatePlayerDir()
{
    char playerInput = mainGameMechsRef->getInput();

    if(playerInput != '0')
    {
        switch(playerInput) // matching input to WASD keys 
        {                      
            case 'W':
            case 'w':
                if(myDir != DOWN){ // prevents snake from going directly backwards
                    myDir = UP;
                }
                break;        
            case 'A':
            case 'a':
                if(myDir != RIGHT && myDir != STOP){ // != STOP prevents snake from going into itself if directed left at beginning of game
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
    // create variables for position limits -> used to implement wrap-around
    // limit is size of board - 2 to prevent interference with boarder (index size - 1)
    int xLimit = mainGameMechsRef->getBoardSizeX() - 2;
    int yLimit = mainGameMechsRef->getBoardSizeY() - 2;
    int headPosX = playerPosList->getHeadElement().pos->x;
    int headPosY = playerPosList->getHeadElement().pos->y;
    bool quit = false; // prevents delay - time for setting exitflag and main program retreiving exitflag causes delay in terminating game. This flag prevents that

    switch(myDir)
    {
        case UP:
            headPosY--;
            if(headPosY < 1){
                headPosY = yLimit;}
            break;
        case LEFT:
            headPosX--;
            if(headPosX < 1){
                headPosX = xLimit;}
            break;
        case DOWN:
            headPosY++;
            if (headPosY > yLimit){
                headPosY = 1;}
            break;
        case RIGHT:
            headPosX++;
            if(headPosX > xLimit){
                headPosX = 1;}
            break;
        case STOP:
        default:
            break;
    }

    for(int i = 1; i < playerPosList->getSize(); i++){
        if(playerPosList->getHeadElement().pos->x == playerPosList->getElement(i).pos->x && playerPosList->getHeadElement().pos->y == playerPosList->getElement(i).pos->y){
            quit = true;
            mainGameMechsRef->setExitTrue();
            mainGameMechsRef->setLoseFlag();
        }
    }

    if(myDir != STOP && !quit){
        if(!checkFoodConsumption()){
            playerPosList->insertHead(objPos(headPosX, headPosY, playerPosList->getHeadElement().symbol));
            playerPosList->removeTail();}
        // } else {
        //     foodReference->generateFood(playerPosList);
        // }
    }

    // if (checkFoodConsumption()) {
    //     increasePlayerLength();
    //     foodReference->generateFood(playerPosList->getHeadElement());  
    // }

    // switch(myDir)
    // {
    //     case UP:
    //         if(playerPosList->getHeadElement().pos->y == 1){
    //             playerPosList->insertHead(objPos(playerPosList->getHeadElement().pos->x, yLimit, playerPosList->getHeadElement().symbol));
    //             playerPosList->removeTail();
    //         } else{
    //             playerPosList->insertHead(objPos(playerPosList->getHeadElement().pos->x, playerPosList->getHeadElement().pos->y - 1, playerPosList->getHeadElement().symbol));
    //             playerPosList->removeTail();
    //         }
    //         break;
    //     case LEFT:
    //         if(playerPosList->getHeadElement().pos->x == 1){
    //                 playerPosList->insertHead(objPos(xLimit, playerPosList->getHeadElement().pos->y, playerPosList->getHeadElement().symbol));
    //                 playerPosList->removeTail();
    //         } else{
    //             playerPosList->insertHead(objPos(playerPosList->getHeadElement().pos->x - 1, playerPosList->getHeadElement().pos->y, playerPosList->getHeadElement().symbol));
    //             playerPosList->removeTail();
    //         }
    //         break;
    //     case DOWN:
    //         if(playerPosList->getHeadElement().pos->y == yLimit){
    //             playerPosList->insertHead(objPos(playerPosList->getHeadElement().pos->x, 1, playerPosList->getHeadElement().symbol));
    //             playerPosList->removeTail();
    //         } else{
    //             playerPosList->insertHead(objPos(playerPosList->getHeadElement().pos->x, playerPosList->getHeadElement().pos->y + 1, playerPosList->getHeadElement().symbol));
    //             playerPosList->removeTail();
    //         }
    //         break;
    //     case RIGHT:
    //         if(playerPosList->getHeadElement().pos->x == xLimit){
    //             playerPosList->insertHead(objPos(1, playerPosList->getHeadElement().pos->y, playerPosList->getHeadElement().symbol));
    //             playerPosList->removeTail();
    //         } else{
    //             playerPosList->insertHead(objPos(playerPosList->getHeadElement().pos->x + 1, playerPosList->getHeadElement().pos->y, playerPosList->getHeadElement().symbol));
    //             playerPosList->removeTail();
    //         }
    //         break;
    //     case STOP:
    //     default:
    //         break;
    // }  

    // Code from prev iteration:
    // switch(myDir)
    // {
    //     case UP:
    //         playerPos.pos->y--;
    //         if(playerPos.pos->y < 1){
    //             playerPos.pos->y = yLimit;}
    //         break;
    //     case LEFT:
    //         playerPos.pos->x--;
    //         if(playerPos.pos->x < 1){
    //             playerPos.pos->x = xLimit;}
    //     case DOWN:
    //         playerPos.pos->y++;
    //         if (playerPos.pos->y > yLimit){
    //             playerPos.pos->y = 1;}
    //         break;
    //     case RIGHT:
    //         playerPos.pos->x++;
    //         if(playerPos.pos->x > xLimit){
    //             playerPos.pos->x = 1;}
    //         break;
    //     case STOP:
    //         break;
    //     default:
    //         break;
    // }  

}

// More methods to be added

// bool Player::checkFoodConsumption(){
// // {    objPos* foodlist = foodReference->getFoodPos();  // Get the list of food positions

// //     for (int i = 0; i < foodlist->getSize(); ++i) {
// //         objPos foodPos = foodlist->getElement(i);  // Get each food position

//             if (playerPosList->getHeadElement().pos->x == foodReference->getFoodPos()->getHeadElement().pos->x &&
//         playerPosList->getHeadElement().pos->y == foodReference->getFoodPos()->getHeadElement().pos->y) {
//             // foodReference->generateFood(playerPosList);  // Generate new food
//             // mainGameMechsRef->incrementScore();  // Increment the score
//             return true;
//         }
//         return false;
//     }

// void Player::increasePlayerLength() {
//     mainGameMechsRef->incrementScore();
//     playerPosList->insertTail(playerPosList->getTailElement());}

bool Player::checkFoodConsumption(){
    objPos playerPos = playerPosList->getHeadElement();
    objPosArrayList* foodList = foodReference->getFoodPos();
    for (int i = 0; i < foodList->getSize(); ++i) {
        objPos foodItem = foodList->getElement(i);

        if (playerPos.pos->x == foodItem.pos->x && playerPos.pos->y == foodItem.pos->y) {
            if (foodItem.symbol == 'H') {
                mainGameMechsRef->incrementScore(10);  
            } else if (foodItem.symbol == 'A') {
                mainGameMechsRef->incrementScore(50); 
                increasePlayerLength(10); 
            } else {
                mainGameMechsRef->incrementScore(1); 
                increasePlayerLength(1); 
            }

            playerPosList->removeHead();  
            foodReference->generateFood(playerPosList);  
            return true; 
        }
    }
    return false;  
}

void Player::increasePlayerLength(int points) {
    playerPosList->insertTail(playerPosList->getTailElement());
    playerPosList->removeTail();

    
    }