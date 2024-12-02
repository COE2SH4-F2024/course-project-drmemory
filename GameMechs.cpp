#include "GameMechs.h"


GameMechs::GameMechs()
{boardSizeX = 30;
boardSizeY = 15;
score = 0;
exitFlag = false;
loseFlag = false;
input = 0;




}

 

GameMechs::GameMechs(int boardX, int boardY)
{ boardSizeX = boardX;
boardSizeY= boardY;
score = 0;
exitFlag = false;
loseFlag = false;
input = 0;


    
}


bool GameMechs::getExitFlagStatus() const
{    return exitFlag;


}

bool GameMechs::getLoseFlagStatus() const
{return loseFlag;

}
    

char GameMechs::getInput() const
{return input;

}

int GameMechs::getScore() const
{return score;
 

}

void GameMechs::incrementScore(int size)
{score+=size; 

    
}

int GameMechs::getBoardSizeX() const
{ return boardSizeX;

}

int GameMechs::getBoardSizeY() const
{return boardSizeY;

}


void GameMechs::setExitTrue()
{exitFlag = true;  

}

void GameMechs::setLoseFlag()
{loseFlag = true;  
    
}

void GameMechs::setInput(char this_input)
{input = this_input;  

}

void GameMechs::clearInput()
{input = 0;

}

GameMechs::~GameMechs()
{
}
