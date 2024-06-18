#include "Player.h"
#include "MacUILib.h"

 
Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;
    mainGameMechsRef->setRegenerate(false);
    // more actions to be included
    //initial place of the player position when starting
    playPosList = new objPosArrayList();
    objPos playerPos(mainGameMechsRef->getBoardSizeX() / 2, mainGameMechsRef->getBoardSizeY() / 2, '*');
    playPosList->insertHead(playerPos);
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
            
            default:
            break;
        }
        mainGameMechsRef->clearInput();
    }
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
    increasePlayerLength(0);
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
    if (growthby == 0) {
        playPosList->removeTail();
    }
    else { //don't remove the tail, and reset helper flag
        growthby--;
    }
}   

bool Player::checkSelfCollision() 
{
    for (int i = 1; i < playPosList->getSize(); ++i) //loop through entire body array
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

void Player::printPlayerPos()
{
    MacUILib_printf("Snake Coordinates: \n");
    for (int i = 0; i < playPosList->getSize(); i++)
    {
        playPosList->getElement(tempObjPos, i);
        MacUILib_printf("List[%d] = <%d, %d>, Symbol = %c\n", i, tempObjPos.x, tempObjPos.y, tempObjPos.symbol);
    }
}