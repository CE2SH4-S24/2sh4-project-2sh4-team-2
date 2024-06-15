#include "food.h"


Food::Food(Player* thisPlrRef, GameMechs* thisGMRef)
{
    mainGMRef = thisGMRef;
    mainPlayer = thisPlrRef;
    foodPos.symbol = '*';
    //Seed the random integer generation function with current time.
    srand(time(NULL));

}

Food::~Food()
{
    
}

void Food::generateFood()
{
    objPos playerPos;
    mainPlayer->getPlayerPos(playerPos);

    int bufX, bufY, xRange, yRange;
    
    xRange = mainGMRef->getBoardSizeX() - 3;
    yRange = mainGMRef->getBoardSizeY() - 3;

    
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
    }    
}

void Food::getFoodPos(objPos &returnPos)
{
    returnPos.setObjPos(foodPos.x, foodPos.y, foodPos.symbol);
}