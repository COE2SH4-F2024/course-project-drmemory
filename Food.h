#ifndef FOOD_H

#define FOOD_H
#include "objPos.h"  


class Food {
private:
    objPos foodPos;  

public:
    Food();  
    ~Food();  
    // Food(const Food& other); 
    Food(const Food &f);
    Food& operator=(const Food& other); 
    void generateFood(objPos blockOff);
    objPos getFoodPos() const;
};
#endif