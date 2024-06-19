#include "Player.h"
#include "MacUILib.h"
#include "Food.h"
#include <iostream>

 
Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    this->foodRef = foodRef;

    myDir = STOP;
    mainGameMechsRef->setRegenerate(false);
    // more actions to be included
    //initial place of the player position when starting
    playPosList = new objPosArrayList();
    objPos playerPos(mainGameMechsRef->getBoardSizeX() / 2, mainGameMechsRef->getBoardSizeY() / 2, '*');
    playPosList->insertHead(playerPos);
    growthby = 0;
}


Player::~Player()
{
    // delete any heap members here
    delete playPosList;
    
}


objPosArrayList* Player::getPlayerPos() 
{
    return playPosList;
}


void Player::updatePlayerDir()
{
    char input = mainGameMechsRef->getInput();    

    if(input != 0)  // if not null character
    {
        switch(input)
        {
            case 27: // escape key        
            case ' ': // spacebar
                mainGameMechsRef->setExitTrue(); // exit
                break;
    // key 'n' or 'N' used to generate new food item
            case 'n':
            case 'N':
                mainGameMechsRef->setRegenerate(true);
                break;
    // Add more key processing here
            case 'A':
            case 'a':
            if (myDir != RIGHT)
            {
                myDir = LEFT;
            }
            break;

            case 'D':
            case 'd':
            if (myDir != LEFT)
            {
                myDir = RIGHT;
            }
            break;

            case 'W':
            case 'w':
            if (myDir != DOWN)
            {
                myDir = UP;
            }
            break;

            case 'S':
            case 's':
            if (myDir != UP)
            {
                myDir = DOWN;
            }
            break;
            case ',': // decrease speed up to 0.05s second delay
            case '<':
            switch (speedLvl)
            {
                case L5:           // 500000 (0.50s)
                    speedLvl = L4; // 350000 (0.35s)
                    break;
                case L4:
                    speedLvl = L3; // 200000 (0.20s)
                    break;
                case L3:
                    speedLvl = L2; // 100000 (0.10s)
                    break;
                case L2:
                    speedLvl = L1; // 50000 (0.05s)
                    break;
                case L1:           // do nothing (0.05s)
                    break;    
            }
            break;
            case '.': // increase speed up to 0.5s delay
            case '>':
            switch (speedLvl)
            {
                case L1:           // 50000 (0.05s)
                    speedLvl = L2; // 100000 (0.20s)
                    break;
                case L2:
                    speedLvl = L3; // 200000 (0.20s)
                    break;
                case L3:
                    speedLvl = L4; // 350000 (0.20s)
                    break;
                case L4:
                    speedLvl = L5; // 500000 (0.50s)
                    break;
                case L5:           // do nothing (0.50s)
                    break;    
            }
    break; 
            default:
            break;
        }
        mainGameMechsRef->clearInput();
    }
}

void Player::initializeSpeed()
{
    speedLvl = L4;
}
int Player::getSpeed()
{
    return speedLvl;
}
void Player::printSpeed()
{
    MacUILib_printf("\nGame Speed: ");
    switch (speedLvl)
    {
    case L1:
        MacUILib_printf("1");
        break;
    case L2:
        MacUILib_printf("2");
        break;
    case L3:
        MacUILib_printf("3");
        break;
    case L4:
        MacUILib_printf("4");
        break;
    case L5:
        MacUILib_printf("5");
        break;
    default:
        break;
    }

    MacUILib_printf(" (%.3f second delay)\n", (speedLvl/1000000.0));
}

void Player::printDir()
{
    MacUILib_printf("Direction: ");
    switch (myDir)
    {
    case STOP:
        MacUILib_printf("STOP");
        break;
    case LEFT:
        MacUILib_printf("LEFT");
        break;
    case RIGHT:
        MacUILib_printf("RIGHT");
        break;
    case UP:
        MacUILib_printf("UP");
        break;
    case DOWN:
        MacUILib_printf("DOWN");
        break;   
    default:
        break;
    }
}

void Player::movePlayer()
{

    // Get the current head position
    objPos currentHead;
    playPosList->getHeadElement(currentHead);

    // Calculate the new head position based on the current direction
    
    int newX = currentHead.x;
    int newY = currentHead.y;

    
    // PPA3 Finite State Machine logic
    switch (myDir) {
    case UP:
        if (newY > 1) {
            newY--;
        }
        else {
            newY = mainGameMechsRef->getBoardSizeY() - 2;
        }
        break;
    case DOWN:
        if (newY < mainGameMechsRef->getBoardSizeY() - 2) {
            newY++;
        }
        else {
            newY = 1;
        }
        break;
    case LEFT:
        if (newX > 1) {
            newX--;
        }
        else {
            newX = mainGameMechsRef->getBoardSizeX() - 2;
        }
        break;
    case RIGHT:
        if (newX < mainGameMechsRef->getBoardSizeX() - 2) {
            newX++;
        }
        else {
            newX = 1;
        }
        break;
    case STOP:
        return;
    default:
        return;
    }

    currentHead.setObjPos(newX, newY, currentHead.getSymbol());

    playPosList->insertHead(currentHead);

    //if player did not grow, remove the tail making it seem like the player moved
    if (growthby <= 0) {
        playPosList->removeTail();
    }
    else { //don't remove the tail, and reset helper flag
        growthby = 0;
    }   

}   

bool Player::checkSelfCollision() 
{
    for (int i = 1; i < playPosList->getSize(); i++) //loop through entire body array
    {
        objPos bodySegment;
        playPosList->getElement(bodySegment, i);

        objPos headPos;
        playPosList->getHeadElement(headPos);

        if (headPos.x == bodySegment.x && headPos.y == bodySegment.y) //player position is on one of the body segment
        {
            return true;
        }
    }
    return false;
}

void Player::increasePlayerLength(int growth) 
{
    growthby = growth;
}

void Player::printPlayerPosList()
{
    MacUILib_printf("Snake Coordinates: \n");
    for (int i = 0; i < playPosList->getSize(); i++)
    {
        playPosList->getElement(tempObjPos, i);
        MacUILib_printf("List[%d] = <%d, %d>, Symbol = %c\n", i, tempObjPos.x, tempObjPos.y, tempObjPos.symbol);
    }
}
void Player::printPlayerPosHead()
{
    playPosList->getElement(tempObjPos, 0);
    MacUILib_printf("Snake Head Position: <%d, %d>\n", tempObjPos.x, tempObjPos.y);
    MacUILib_printf("Snake Head Symbol: @\n");
}

/*int Player::checkFoodConsumption() 
{
    objPos playerPos;
    this->getPlayerPos()->getHeadElement(playerPos);

    objPos foodPos;
    for (int n = 0; n < 5; n++)
    {
        foodRef->getFoodPos(foodPos, n);

        if (playerPos.x == foodPos.x && playerPos.y == foodPos.y) 
        {
            if (foodPos.getSymbol() == '0') {
                return 3;
            } 
            else 
            {
                return 1;
            }
        }
        return 0;
    }
}*/