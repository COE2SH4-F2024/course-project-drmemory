#include "Food.h"
#include "MacUILib.h"
#include <cstdlib>  
#include <ctime>  
#include "objPos.h"


Food::Food() {
    foodPos = objPos();
    foodPos.pos->x = 5;  // DID not know we had to do random position could be explainin the out of bounds goin to assing to arbitrary values(can i even spell arbitrary)
    foodPos.pos->y = 5;
    foodPos.symbol = 'J';  
}

Food::Food(const Food &f) {
    foodPos.pos->x = f.foodPos.pos->x;
    foodPos.pos->y = f.foodPos.pos->y;
    foodPos.symbol = f.foodPos.symbol;
}
Food::~Food() {
    // nothing tbh dk if i can delete this b4 we submit might need for advanced?
}

void Food::generateFood(objPos blockOff) {

//   ppa3 bases to copy that flopped :     while (1) {
            // x = rand() % (xRange - 2) + 1; 
            // y = rand() % (yRange - 2) + 1; 
            // if (x == playerPos->x && y == playerPos->y) 
            //  continue;
 //ppa3 gonna try hard coding ngl giving me issue with having it try to grab the board coordinates in draw screen 
 //hardcoding worked are we allowed to hardcode? fix this ask prof???

    int x, y;
    srand(time(NULL)); //doesnt work without this
    int x_size= 30;//
    int y_size=15;

    while (1) { 
        x = rand() % (x_size - 2) + 1;  // randomize x within board
        y = rand() % (y_size - 2) + 1;  // randomize y within board

        if (x != blockOff.pos->x && y != blockOff.pos->y) {   // blockoff position 
            break; 
        }
    }


    foodPos.pos->x = x;
    foodPos.pos->y = y;
    foodPos.symbol = 'J'; 
}

objPos Food::getFoodPos() const {
    return foodPos; //return food position
}