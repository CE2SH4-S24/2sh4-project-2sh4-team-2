#include "food.h"
#include <cstdlib> //for rand() and srand()
#include <ctime>   //for time()


Food::Food()
{
    
    //foodPos.symbol = 'o';
    foodBucket = new objPosArrayList();
    //Seed the random integer generation function with current time.
    srand(time(NULL));
    foodCollision = false;

}

Food::~Food()
{
    delete foodBucket;   
}

void Food::generateFood(objPosArrayList* blockoff)
{
    foodBucket->clear();

    int bufX, bufY, xRange, yRange,n=0;
    bool positionIsFree;

    xRange = boardX - 3;
    yRange = boardY - 3;

    objPos buf;
    objPos temp;;
    bool flag = 0;
    
    while (n < 5) //doesn't 
    {
        bufX = (rand() % xRange) + 1; //generates an x coordinate within game borders
        bufY = (rand() % yRange) + 1; //generates a y coordinate within game borders

        positionIsFree = true; // initialized to true, maintains true if it passes all boundary cases 
        for (int i = 0; i < blockoff->getSize(); i++)
        {
            blockoff->getElement(temp, i);
            if (bufX == temp.x && bufY == temp.y)
            {
                positionIsFree = false; // Position collides with player's body, generate a new position
                break;
            }
        }
        for (int i = -4; i < 4; i++) // spaces in all directions around player head
        {
            if (((bufX+i == temp.x && bufY == temp.y) || (bufY+i == temp.y && bufX == temp.x)) || ((bufX+i == temp.x && bufY+i == temp.y) || (bufX-i == temp.x && bufY+i == temp.y)))
            {
                positionIsFree = false; // Position too close to player head, generate a new position
                flag = 1;
                break;
            }
        }
        if (!flag)
        {
            for (int i = 0; i < n; i++) // checks food bucket items to ensure no two items hold identical coordinates
            {
                foodBucket->getElement(temp, i);
                if (bufX == temp.x && bufY == temp.y)
                {
                    positionIsFree = false; // prior food bucket item already holds these coordinates, generate new a position
                    break;
                }
            }
        }

        if (positionIsFree) //if random coordinates generated pass all above tests, insert them as 1 objPos item in the foodBucket 
        {
            foodPos.x = bufX;
            foodPos.y = bufY;
            
            if (n < 3) // for 3/5 food items, symbol is 'o'
            {
                buf.symbol = 'o';
            }
            else if (n == 3) //for 1/5 food items, symbol is '0'
            {
                buf.symbol = '0';
            }
            else if (n == 4) //for 1/5 food items, symbol is '+'
            {
                buf.symbol = '+';
            }

            buf.x = bufX;
            buf.y = bufY;

            if (n == 0)
            {
                foodBucket->insertHead(buf); // inserts first element in foodBucket
            }
            else
            {
                foodBucket->insertTail(buf); // inserts next 4 elements in foodBucket
            }
            n++;
        }
    }
}


void Food::getFoodPos(objPos &returnPos, int index)
{
    objPos buffer; //temporary holder to recieve all members of objPos for foodBucket element
    foodBucket->getElement(buffer, index);
    returnPos.setObjPos(buffer.x, buffer.y, buffer.symbol);
}

objPosArrayList* Food::getFoodList()
{
    return foodBucket;
}

void Food::getBoardSize(GameMechs* gamemechs)
{
    boardX = gamemechs->getBoardSizeX();
    boardY = gamemechs->getBoardSizeY();
}

bool Food::getFoodCollision()
{
    return foodCollision;
}

void Food::setFoodCollision(bool boolean)
{
    foodCollision = boolean;
}

