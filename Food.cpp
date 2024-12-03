#include "Food.h"
#include "MacUILib.h"
#include <cstdlib>  
#include <ctime>  
#include "objPos.h"
#include "objPosArrayList.h"


Food::Food(GameMechs* thisGMRef) { //default contructor
    mainGameMechsRef=thisGMRef;  // 
    foodPos = objPos();
    Foodbucket = new objPosArrayList();  
}

Food::~Food() { //destructor 
    delete Foodbucket; // deletes foodbucket array to free up memory
}


void Food::generateFood(objPosArrayList* blockOff) {
    srand(time(NULL));  //using to do random number generator
    int x, y;
    // using gamemechs pointer to grab the size of the board 
    int x_size = mainGameMechsRef->getBoardSizeX(); 
    int y_size =mainGameMechsRef->getBoardSizeY();

    for (int i = 0; i < 5; i++) {  // iterate through 5 food items
        bool overlap = true; // indicator to check if there is overlap
        while (overlap) {
            // randomize x between 28 and 13, to avoid generating food at the borders
            x = rand() % (x_size - 2) + 1;  
            y = rand() % (y_size - 2) + 1;  
          // check to see if generated posiition overlaps with the player position(blockoff position) 
            for (int j = 0; j < blockOff->getSize(); ++j) {  //
                if (x == blockOff->getElement(j).pos->x && y == blockOff->getElement(j).pos->y) {
                    overlap = false; //if overlap is found break from loop and look for a new posiition
                    break;
                }
            }
            // check if the generated position overlaps with any existing food
            for (int k = 0; k < Foodbucket->getSize(); k++) {
                if (x == Foodbucket->getElement(k).pos->x && y == Foodbucket->getElement(k).pos->y) {
                    overlap = false; //if overlap found break from loop
                    break;
                }
            }

            if (!overlap) { // no overlap exit loop)
                break;  
            }
        
            // Updating values of foodPos bc to use insert tail function, we need to use a variable of type objPos 
            foodPos.pos->x = x;
            foodPos.pos->y = y;
            if (i < 4) {  
                foodPos.symbol = 'J';
            } else {  
                foodPos.symbol = (rand() % 2 == 0) ? 'A' : 'H';
            }

            if(Foodbucket->getSize() <= i){ // we want a list of 5 elements: insert an additional if the list is equal to or smaler than the current iteration
            // this is bc in iteration 0, the first element in list is focus: if list size is 0, there is no element in list
                Foodbucket->insertTail(foodPos);
            } else {
                Foodbucket->setElement(i, x, y, foodPos.symbol); // update positions of element in focus
                // we do NOT want to expand list bc we ONLY want FIVE food elements on screen at a time
            }
            
            overlap=false;
        }
    }
}

objPosArrayList* Food::getFoodPos() const {
    return Foodbucket;  
}
