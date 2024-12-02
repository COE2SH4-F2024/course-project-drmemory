#ifndef FOOD_H
#define FOOD_H
#include "objPos.h" 
#include "objPosArrayList.h" 


class Food {
private:
    objPos foodPos;  
    objPosArrayList* Foodbucket;

public:
    Food();  
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