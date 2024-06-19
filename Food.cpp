#include "food.h"
#include <cstdlib> //for rand() and srand()
#include <ctime>   //for time()


Food::Food(Player* thisPlrRef, GameMechs* thisGMRef)
{
    mainGMRef = thisGMRef;
    mainPlayer = thisPlrRef;
    //foodPos.symbol = 'o';
    //Seed the random integer generation function with current time.
    srand(time(NULL));

}

Food::~Food()
{
    
}

void Food::generateFood(objPosArrayList& playerBody)
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
        bool positionIsFree = true;

        for (int i = 0; i < playerPos->getSize(); i++)
        {
            playerPos->getElement(temp, i);
            if (bufX == temp.x && bufY == temp.y)
            {
                positionIsFree = false; // Position collides with player's body
                break;
            }
        }

        if (positionIsFree)
        {
            foodPos.x = bufX;
            foodPos.y = bufY;
            
            // Randomly select food type with different probabilities
            int randValue = rand() % 100; // Generate a random number between 0 and 99
            if (randValue < 15) // 15% chance to generate '0'
            {
                foodPos.symbol = '0';
            }
            else // 80% chance to generate 'o'
            {
                foodPos.symbol = 'o';
            }

            return;
        }
    }
}

void Food::getFoodPos(objPos &returnPos)
{
    returnPos.setObjPos(foodPos.x, foodPos.y, foodPos.symbol);
}