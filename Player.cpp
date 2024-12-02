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
                if(myDir != RIGHT){ // != STOP prevents snake from going into itself if directed left at beginning of game
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
{objPos playerPos = playerPosList->getHeadElement();
    // create variables for position limits -> used to implement wrap-around
    // limit is size of board - 2 to prevent interference with boarder (index size - 1)
    int xLimit = mainGameMechsRef->getBoardSizeX() - 2;
    int yLimit = mainGameMechsRef->getBoardSizeY() - 2;
    int headPosX = playerPosList->getHeadElement().pos->x;
    int headPosY = playerPosList->getHeadElement().pos->y;
    bool quit = false; // prevents delay - time for setting exitflag and main program retreiving exitflag causes delay in terminating game. This flag prevents that

    switch(myDir)
    {
        // implementing wraparound to keep player confined within borders
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

    if(checkSelfCollision()){
        quit = true;
        mainGameMechsRef->setLoseFlag();
        mainGameMechsRef->setExitTrue();
    }

    if(myDir != STOP && !quit){ // !STOP prevents actions from auto-executing at beginning of game
        playerPosList->insertHead(objPos(headPosX, headPosY, playerPosList->getHeadElement().symbol));
        if(!checkFoodConsumption()){ // if this is true, increasePlayerlength will be run inside checkFoodConsumption and possibly additional tail elements will be inserted
        // no need to remove tail if false bc we want to increase player length -> minimizes resources used in inserting AND removing -> prevents redundancy 
            playerPosList->removeTail();
        } 
    }
}

bool Player::checkFoodConsumption(){ 
    objPos playerPos = playerPosList->getHeadElement(); //get the players current position which is the head
    objPosArrayList* foodList = foodReference->getFoodPos(); 
    for (int i = 0; i < foodList->getSize(); ++i) { //iterating through the food list to check if the player is at the same position as the the food item
        objPos foodItem = foodList->getElement(i);

        if (playerPos.pos->x == foodItem.pos->x && playerPos.pos->y == foodItem.pos->y) { // checking to see if the player position matches the food item position if so food is consumed
            if (foodItem.symbol == 'H') { // if the food consumed is H then score is incremented by 10
                mainGameMechsRef->incrementScore(10);  
            } else if (foodItem.symbol == 'A') { // if food consume is A then score is incrememted by A and tail lenght is  increased by 10
                mainGameMechsRef->incrementScore(50); 
                increasePlayerLength(5); 
            } else { // else regular food score and tail is incremented by 1
                mainGameMechsRef->incrementScore(1); 
                increasePlayerLength(1); 
            }

            foodReference->generateFood(playerPosList);   // regenerate food if consumed
            return true; 
        }
    }
    return false;  
}

bool Player::checkSelfCollision(){
    int headPosX = playerPosList->getHeadElement().pos->x;
    int headPosY = playerPosList->getHeadElement().pos->y;
    for(int i = 1; i < playerPosList->getSize(); i++){ // iterate through player array to check if the head element is at the same poisiton as a body element
        if(headPosX == playerPosList->getElement(i).pos->x && headPosY == playerPosList->getElement(i).pos->y){
            return true;
        }
    }
    return false;
}

void Player::increasePlayerLength(int points) {
    for(int i = 0; i < points - 1; i++){ // insert one less element than the number of points into the tail
    // one less because by inserting a head element, if the tail is not removed, the player will already increment by one
        playerPosList->insertTail(playerPosList->getTailElement()); // insert into tail because we don't want to speed up player, only grow its body
    }    
}

