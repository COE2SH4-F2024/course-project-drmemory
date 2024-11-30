#ifndef PLAYER_H
#define PLAYER_H

#include "GameMechs.h"
#include "objPos.h"
#include "objPosArrayList.h"

class Player
{
    // Construct the remaining declaration from the project manual.

    // Only some sample members are included here

    // You will include more data members and member functions to complete your design.

    
    public:
        enum Dir {UP, DOWN, LEFT, RIGHT, STOP};  // This is the direction state

        Player(GameMechs* thisGMRef); // default constructor
        Player(GameMechs* thisGMRef, int size); // additional constructor
        Player(const Player &p); // copy constructor
        ~Player(); // destructor
        Player& operator= (const Player &p); // copy assignment operator

        // objPos getPlayerPos() const; // Upgrade this in iteration 3.   
        objPosArrayList* getPlayerPos() const; 
        void updatePlayerDir();
        void movePlayer();

        // More methods to be added here

    private:
        // objPos playerPos; // Upgrade this in iteration 3.     
        objPosArrayList* playerPosList;  
        enum Dir myDir;

        // Need a reference to the Main Game Mechanisms
        GameMechs* mainGameMechsRef;
};

#endif