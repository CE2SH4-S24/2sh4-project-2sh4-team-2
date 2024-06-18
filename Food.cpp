#include "food.h"


Food::Food(Player* thisPlrRef, GameMechs* thisGMRef)
{
    mainGMRef = thisGMRef;
    mainPlayer = thisPlrRef;
    foodPos.symbol = 'o';
    //Seed the random integer generation function with current time.
    srand(time(NULL));

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
    objPosArrayList* playerPos = mainPlayer->getPlayerPos();
    objPos temp;

    while (true)
    {
        bufX = (rand() % xRange) + 1;
        bufY = (rand() % yRange) + 1;
        for (int i = 0; i < playerPos->getSize(); i++)
        {
            playerPos->getElement(temp, i);
            if (bufX != temp.x && bufY != temp.y)
            {
                foodPos.x = bufX;
                foodPos.y = bufY;
                return;
            }
            else
            {
                continue; // get a new buf.
            }
        }
    }

}

void Food::getFoodPos(objPos &returnPos)
{
    returnPos.setObjPos(foodPos.x, foodPos.y, foodPos.symbol);
}