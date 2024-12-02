#include "Food.h"
#include "MacUILib.h"
#include <cstdlib>  
#include <ctime>  
#include "objPos.h"
#include "objPosArrayList.h"


Food::Food() {
    foodPos = objPos();
    foodPos.pos->x = 5;  // DID not know we had to do random position could be explainin the out of bounds goin to assing to arbitrary values(can i even spell arbitrary)
    foodPos.pos->y = 5;
    foodPos.symbol = 'J';
    Foodbucket = new objPosArrayList();  
}

// Food::Food(const Food &f) {
//     foodPos.pos->x = f.foodPos.pos->x;
//     foodPos.pos->y = f.foodPos.pos->y;
//     foodPos.symbol = f.foodPos.symbol;
// }

Food::~Food() {
    // nothing tbh dk if i can delete this b4 we submit might need for advanced?
    delete Foodbucket;
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


// void Food::generateFood(objPosArrayList* blockOff) {

// //   ppa3 bases to copy that flopped :     while (1) {
//             // x = rand() % (xRange - 2) + 1; 
//             // y = rand() % (yRange - 2) + 1; 
//             // if (x == playerPos->x && y == playerPos->y) 
//             //  continue;
//  //ppa3 gonna try hard coding ngl giving me issue with having it try to grab the board coordinates in draw screen 
//  //hardcoding worked are we allowed to hardcode? fix this ask prof???

//     srand(time(NULL));  // Seed the random number generator
//     int x, y;
//     int x_size = 30;  
//     int y_size = 15;  

//     for (int i = 0; i < 5; i++) {  
//         bool overlap = true;
//         while (overlap) {
//             x = rand() % (x_size - 2) + 1;  
//             y = rand() % (y_size - 2) + 1;  

//             for (int j = 0; j < blockOff->getSize(); ++j) {
//                 if (x == blockOff->getElement(j).pos->x && y == blockOff->getElement(j).pos->y) {
//                     overlap = false;
//                     break;
//                 }
//             }

//             for (int j = 0; j < Foodbucket->getSize(); ++j) {
//                 if (x == Foodbucket->getElement(j).pos->x ==x && y == Foodbucket->getElement(j).pos->y==y) {
//                     overlap = false;
//                     break;
//                 }
//             }

//             if (!overlap) {
//                 break;  
//             }
//         // foodPos.pos->x = x;
//         // foodPos.pos->y = y;
//         char foodSymbol = (rand() % 5 == 0) ? 'H' : 'A';
//         objPos foodPos = {x, y, foodSymbol};
//         Foodbucket->insertTail(foodPos); 
//         overlap=false;
//         }

    

    


//     // int x, y;
//     // srand(time(NULL)); //doesnt work without this
//     // int x_size= 30;//
//     // int y_size=15;

//     // while (1) { 
//     //     x = rand() % (x_size - 2) + 1;  // randomize x within board
//     //     y = rand() % (y_size - 2) + 1;  // randomize y within board

//     //     if (x != blockOff.pos->x && y != blockOff.pos->y) {   // blockoff position 
//     //         break; 
//     //     }
//     // }


//     // foodPos.pos->x = x;
//     // foodPos.pos->y = y;
//     // foodPos.symbol = 'J'; 
// }
// }

void Food::generateFood(objPosArrayList* blockOff) {

//   ppa3 bases to copy that flopped :     while (1) {
            // x = rand() % (xRange - 2) + 1; 
            // y = rand() % (yRange - 2) + 1; 
            // if (x == playerPos->x && y == playerPos->y) 
            //  continue;
 //ppa3 gonna try hard coding ngl giving me issue with having it try to grab the board coordinates in draw screen 
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
        
        foodPos.pos->x = x;
        foodPos.pos->y = y;
        if (i < 4) {  
            foodPos.symbol = 'J';
        } else {  
            foodPos.symbol = (rand() % 2 == 0) ? 'A' : 'H';
        }


        Foodbucket->insertTail(foodPos); 
        overlap=false;
        }

       
}
}

void Food::updateFood(objPosArrayList* blockOff) {

//   ppa3 bases to copy that flopped :     while (1) {
            // x = rand() % (xRange - 2) + 1; 
            // y = rand() % (yRange - 2) + 1; 
            // if (x == playerPos->x && y == playerPos->y) 
            //  continue;
 //ppa3 gonna try hard coding ngl giving me issue with having it try to grab the board coordinates in draw screen 
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

            for (int j = 0; j < Foodbucket->getSize(); ++j) {
                if (x == Foodbucket->getElement(j).pos->x ==x && y == Foodbucket->getElement(j).pos->y==y) {
                    overlap = false;
                    break;
                }
            }

            if (!overlap) {
                break;  
            }
        // foodPos.pos->x = x;
        // foodPos.pos->y = y;
        char foodSymbol = (rand() % 5 == 0) ? 'H' : 'A';
        objPos foodPos = {x, y, foodSymbol};
        Foodbucket->removeHead(); 
        Foodbucket->insertTail(foodPos); 
        overlap=false;
        }

    

    


    // int x, y;
    // srand(time(NULL)); //doesnt work without this
    // int x_size= 30;//
    // int y_size=15;

    // while (1) { 
    //     x = rand() % (x_size - 2) + 1;  // randomize x within board
    //     y = rand() % (y_size - 2) + 1;  // randomize y within board

    //     if (x != blockOff.pos->x && y != blockOff.pos->y) {   // blockoff position 
    //         break; 
    //     }
    // }


    // foodPos.pos->x = x;
    // foodPos.pos->y = y;
    // foodPos.symbol = 'J'; 
}
}

// objPos Food::getFoodPos() const {
//     return foodPos; //return food position
// }
objPosArrayList* Food::getFoodPos() const {
    return Foodbucket;  
}
