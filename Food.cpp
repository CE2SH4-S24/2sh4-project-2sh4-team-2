#include "food.h"


Food::Food(Player* thisPlrRef, GameMechs* thisGMRef)
{
    mainGMRef = thisGMRef;
    mainPlayer = thisPlrRef;
    foodPos.symbol = '*';
    //Seed the random integer generation function with current time.
    srand(time(NULL));
    generateFood();
}

Food::~Food()
{
    
}

void Food::generateFood()
{
    int bufX, bufY, xRange, yRange;
    bool flag = false;
    xRange = mainGMRef->getBoardSizeX() - 3;
    yRange = mainGMRef->getBoardSizeY() - 3;
    objPos playerPos;
    mainPlayer->getPlayerPos(playerPos);

    while (true)
    {
        bufX = (rand() % xRange) + 1;
        bufY = (rand() % yRange) + 1;
        if (bufX != playerPos.x && bufY != playerPos.y)
        {
            foodPos.x = bufX;
            foodPos.y = bufY;
            break;
        }
        else
        {
            continue; // get a new buf.
        }
    }    
}

void Food::getFoodPos(objPos &returnPos)
{
    returnPos.setObjPos(foodPos.x, foodPos.y, foodPos.symbol);
}