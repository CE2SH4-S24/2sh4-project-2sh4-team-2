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

//additional features
    gameMsg = 0;
    countMsg = 0;
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

    //additional features
    gameMsg = 0;
    countMsg = 0;
}

// do you need a destructor? no
/*
GameMechs::~GameMechs()
{

}
*/

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
    if (loseFlag) //sets exit flag to true once lose flag is set to true
    {
        exitFlag = true;
    }
}
// functions to implement dissapearing messages
int GameMechs::getGameMsg()
{
    return gameMsg;
}

int GameMechs::getMsgTime()
{
    return msgTime;
}

int GameMechs::getCountMsg()
{
    return countMsg;
}

void GameMechs::addCountMsg()
{
    countMsg++;
}

void GameMechs::resetCountMsg()
{
    countMsg = 0;
}
void GameMechs::setGameMsg(int n)
{
    gameMsg = n;
}

void GameMechs::GameMechs::printSpecialMessages() 
{
    if(!getLoseFlagStatus() && gameMsg)
    {
        if (countMsg < msgTime)
        {
            MacUILib_printf("   ");
            if (gameMsg == 1)
            {
                MacUILib_printf("+%d score! +%d length!", 30, 0);
            }
            else if (gameMsg == 2)
            {
                MacUILib_printf("+%d score! +%d length!", 50, 5);
            }
            else if (gameMsg == 3)
            {
                MacUILib_printf("+%d score! +%d length!", 10, 1);
            }
        }
        else
        {
            gameMsg = 0;
        }
    }
}
