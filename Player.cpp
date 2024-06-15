#include "Player.h"
#include "MacUILib.h"

 
Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;
    mainGameMechsRef->setRegenerate(false);
    // more actions to be included
    //initial place of the player position when starting
    playerPos.setObjPos(mainGameMechsRef->getBoardSizeX()/2, mainGameMechsRef->getBoardSizeY()/2, '@');
}


Player::~Player()
{
    // delete any heap members here
    
    
}

void Player::getPlayerPos(objPos &returnPos)
{
    // return the reference to the playerPos
   returnPos.setObjPos(playerPos.x, playerPos.y, playerPos.symbol);
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
    // PPA3 Finite State Machine logic
    switch (myDir)
    {   
        case LEFT:
            if(playerPos.x > 1)
            {
                playerPos.x--;
            }
            else if (playerPos.x == 1)
            {
                playerPos.x = mainGameMechsRef->getBoardSizeX() - 2;
            }
            break;
        case RIGHT:
            if(playerPos.x < mainGameMechsRef->getBoardSizeX() - 2)
            {
                playerPos.x++;
            }
            else if (playerPos.x == mainGameMechsRef->getBoardSizeX() - 2)
            {
                playerPos.x = 1;
            }
            break;
        case UP:
            if(playerPos.y > 1)
            {
                playerPos.y--;
            }
            else if (playerPos.y == 1)
            {
                playerPos.y = mainGameMechsRef->getBoardSizeY() - 2;
            }
            break;
        case DOWN:
            if(playerPos.y < mainGameMechsRef->getBoardSizeY() - 2)
            {
                playerPos.y++;
            }
            else if (playerPos.y == mainGameMechsRef->getBoardSizeY() - 2)
            {
                playerPos.y = 1;
            }
            break;
        default:
            break;
    }
}
