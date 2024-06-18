#include "GameMechs.h"
#include "MacUILib.h"

GameMechs::GameMechs()
{
    input = 0;
    score = 0;
    exitFlag = false;
    regenerate = false;

// default board sizes
    boardSizeX = 20;
    boardSizeY = 10;
}

GameMechs::GameMechs(int boardX, int boardY)
{
    input = 0;
    score = 0;
    exitFlag = false;
    regenerate = false;

// custom board sizes
    boardSizeX = boardX;
    boardSizeY = boardY;
}

// do you need a destructor?



bool GameMechs::getExitFlagStatus()
{
    return exitFlag;
}

char GameMechs::getInput()
{
    
    return input;
}

int GameMechs::getBoardSizeX()
{
    return boardSizeX;
}

int GameMechs::getBoardSizeY()
{
 return boardSizeY;
}

 
void GameMechs::setExitTrue()
{
    exitFlag = true;
}

void GameMechs::setInput(char this_input)
{
    input = this_input;
}

void GameMechs::clearInput()
{
    input = 0;
}

// Provide definitions of more member functions as required
// See Project Manual

bool GameMechs::getRegenerateStatus()
{
    return regenerate;
}

void GameMechs::setRegenerate(bool boolean)
{
    regenerate = boolean;
}

int GameMechs::getScore() const {
    return score;
}

void GameMechs::incrementScore(int amount) {
    score += amount;
}

bool GameMechs::getLoseFlagStatus() const {
    return loseFlag;
}

void GameMechs::setLoseFlag(bool value) {
    loseFlag = value;
    if (loseFlag)
    {
        exitFlag = true;
    }
}