#include "food.h"
#include <cstdlib> //for rand() and srand()
#include <ctime>   //for time()


Food::Food(Player* thisPlrRef, GameMechs* thisGMRef)
{
    mainGMRef = thisGMRef;
    mainPlayer = thisPlrRef;
    foodPos.symbol = 'o';
    foodBucket = new objPosArrayList;
    //Seed the random integer generation function with current time.
    srand(time(NULL));

}

Food::~Food()
{
    delete foodBucket;   
}

void Food::generateFood()
{
    int bufX, bufY, xRange, yRange, n = 0;
    bool flag = false;
    xRange = mainGMRef->getBoardSizeX() - 3;
    yRange = mainGMRef->getBoardSizeY() - 3;
    objPosArrayList* playerPos = mainPlayer->getPlayerPos();
    objPos buf;
    objPos temp;
    int size = foodBucket->getSize();
    

    while(foodBucket->getSize() != 0)
    {
        foodBucket->removeTail();

    }
 //need to exclude cases where coordinates are equal to another element's coordinates for food bucket itself
   while (n < 5)
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
                buf = {bufX, bufY, 'o'};
                if(n < 3)
                {
                    buf.symbol = 'o';
                }
                else if (n == 3)
                {
                    buf.symbol = '0';
                }
                else if (n == 4)
                {
                    buf.symbol = '+';
                }

                if (n == 0)
                {
                    foodBucket->insertHead(buf);
                }
                else
                {
                    foodBucket->insertTail(buf);
                }
                n++;
            }
            else{
                break;
            }
        }
        continue;
    }
}

void Food::getFoodPos(objPos &returnPos, int index)
{
    objPos buffer;
    foodBucket->getElement(buffer, index);
    returnPos.setObjPos(buffer.x, buffer.y, buffer.symbol);
}