#ifndef FOOD_H

#define FOOD_H
#include "objPos.h" 
#include "objPosArrayList.h" 
#include "GameMechs.h"


class Food {
private:
    objPos foodPos;  
    objPosArrayList* Foodbucket;
    GameMechs* mainGameMechsRef;
public:
    Food(GameMechs* thisGMRef);
    ~Food();  
    // Food(const Food& other); 
    Food(const Food &f);
    Food& operator=(const Food& other); 
    // void generateFood(objPos blockOff);
    void generateFood(objPosArrayList* blockOff);
    void updateFood(objPosArrayList* blockOff);
    // objPos getFoodPos() const;
    objPosArrayList* getFoodPos() const;
};
#endif