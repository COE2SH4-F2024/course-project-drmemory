#include "Food.h"
#include "MacUILib.h"
#include <cstdlib>  
#include <ctime>  
#include "objPos.h"
#include "objPosArrayList.h"


Food::Food() {
    foodPos = objPos();
    // foodPos.pos->x = 5;  // DID not know we had to do random position could be explainin the out of bounds goin to assing to arbitrary values(can i even spell arbitrary)
    // foodPos.pos->y = 5;
    // foodPos.symbol = 'J';
    Foodbucket = new objPosArrayList();  
}


Food::~Food() {
    delete Foodbucket; // deletes foodbucket array to free up memory
}

Food& Food::operator=(const Food &f) {
    if (this != &f) {  // Prevent self-assignment
        // Clean up current resources
        delete Foodbucket;

        // Copy the simple members
        foodPos.pos->x = f.foodPos.pos->x;
        foodPos.pos->y = f.foodPos.pos->y;
        foodPos.symbol = f.foodPos.symbol;

        Foodbucket = new objPosArrayList();
        for (int i = 0; i < f.Foodbucket->getSize(); i++) {
            Foodbucket->insertTail(f.Foodbucket->getElement(i));
        }
    }
    return *this;
}

void Food::generateFood(objPosArrayList* blockOff) {
 //hardcoding worked are we allowed to hardcode? fix this ask prof???
    srand(time(NULL));  // Seed the random number generator
    int x, y;
    int x_size = 30;  
    int y_size = 15;  

    for (int i = 0; i < 5; i++) {  
        bool overlap = true;
        while (overlap) {
            x = rand() % (x_size - 2) + 1;  
            y = rand() % (y_size - 2) + 1;  

            for (int j = 0; j < blockOff->getSize(); ++j) {
                if (x == blockOff->getElement(j).pos->x && y == blockOff->getElement(j).pos->y) {
                    overlap = false;
                    break;
                }
            }

            for (int k = 0; k < Foodbucket->getSize(); k++) {
                if (x == Foodbucket->getElement(k).pos->x && y == Foodbucket->getElement(k).pos->y) {
                    overlap = false;
                    break;
                }
            }

            if (!overlap) {
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
