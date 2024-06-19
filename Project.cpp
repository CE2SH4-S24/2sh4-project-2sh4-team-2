#include <iostream> 
#include "MacUILib.h"
#include "objPos.h"
#include "GameMechs.h"
#include "Player.h"
#include "Food.h"


using namespace std;

#define DELAY_CONST 100000

//objPos myPos;
Player* myPlayer;
objPos border;
Food* myFood;
objPos tempFoodPos; // holds one objPos value of food (food coordinates)
objPosArrayList* tempPlayerPos;
objPos temp; // holds one objPos index value of playerPosList (snake body coordinates)
//const int msgTime = 7; // number of screen refreshes before game messages disappear
//int countMsg;
//int gameMsg;


//bool exitFlag;
GameMechs* myGM;

bool foodCollision;
//Function Declarations

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);


//WIP Functions 


int main(void)
{

    Initialize();

    while(myGM->getExitFlagStatus() == false)  
    {
        GetInput();
        RunLogic();
        DrawScreen();
        LoopDelay();
    }

    CleanUp();
    return 0;
}


void Initialize(void)
{
    MacUILib_init();
    MacUILib_clearScreen();
    
    // possible board sizes
    // small board :20, 30 --> call with no parameters
    // medium 1: 24, 12 medium2: 26, 13, medium3: 28, 14
    //large1: 30,15, large2: 32, 16
    myGM = new GameMechs(28, 14); 
    myPlayer = new Player(myGM);
    myFood = new Food(myPlayer, myGM);
    border.setObjPos(0,0, '#'); //starting position and character symbol of border to be printed
    myFood->generateFood(); //generates a random coordinate for food
    bool foodCollision = false; // initializes snake head collision with food to false
    myPlayer->increasePlayerLength(0); //initializes player length growth to 0;
    myGM->setLoseFlag(false);
    myPlayer->initializeSpeed();
    //gameMsg = 0;
    //countMsg = 0;

}

void GetInput(void)
{
    if (MacUILib_hasChar())
    {
        char input = MacUILib_getChar();
        myGM->setInput(input);
    }

     
}

void RunLogic(void)
{
    if(myGM->getRegenerateStatus())
    {
        myFood->generateFood();
        myGM->setRegenerate(false);
        
    }
    myPlayer->updatePlayerDir();
    myPlayer->movePlayer();
    
    tempPlayerPos = myPlayer->getPlayerPos();
 
    tempPlayerPos->getHeadElement(temp);
    foodCollision = false;
    
    objPos tempFoodPos;

    if (myGM->getGameMsg())
    {
        myGM->addCountMsg();
    }
    else
    {
        myGM->resetCountMsg();
    }

    for (int n = 0; n < 5; n++)
    {
        myFood->getFoodPos(tempFoodPos, n);
        if (temp.x == tempFoodPos.x && temp.y == tempFoodPos.y)
        {
            foodCollision = true;
            
            if(tempFoodPos.symbol == '0') {
                myGM->incrementScore(30); 
                myPlayer->increasePlayerLength(0);
                myGM->setGameMsg(1);
                myGM->resetCountMsg();
            } else if(tempFoodPos.symbol == '+') {
                myGM->incrementScore(50); 
                myPlayer->increasePlayerLength(5);
                myGM->setGameMsg(2);
                myGM->resetCountMsg();
            } else {
                myGM->incrementScore(10); 
                myPlayer->increasePlayerLength(1);
                myGM->setGameMsg(3);
                myGM->resetCountMsg();
            }
            myFood->generateFood();
            break;
        }
    }
    
    if (myPlayer->checkSelfCollision())
    {
       myGM->setLoseFlag(true);   
    }
}

void DrawScreen(void)
{
    int k = 0, t = 0;
    
    MacUILib_clearScreen();
    for (int i = 0; i < myGM->getBoardSizeY(); i++)
    {
        for (int j = 0; j < myGM->getBoardSizeX(); j++)
        {
    //          If at the player object position, print the player symbol
            for (int p = 0; p < tempPlayerPos->getSize(); p++)
            {
                k = 0;
                tempPlayerPos->getElement(temp, p); 
                if (i == temp.y && j == temp.x)
                {
                    if (p == 0)
                    {
                        MacUILib_printf("@");                        
                    }
                    else
                    {
                        MacUILib_printf("%c", temp.symbol);                        
                    }
                    k = 1;
                    break;
                }
            }
    //          If at food item position, print food symbol
            for (int n = 0; n < 5; n++)
            {
                t = 0;
                myFood->getFoodPos(tempFoodPos, n);
                if (!foodCollision && i == (tempFoodPos.y) && j == (tempFoodPos.x))
                {
                    MacUILib_printf("%c", tempFoodPos.symbol);
                    t = 1;
                    break;
                }
            }
            if (i == 0 || i == (myGM->getBoardSizeY() - 1) || j == 0 || j == (myGM->getBoardSizeX() - 1))
            {
                MacUILib_printf("%c", border.getSymbol());
            }
    //          Otherwise, print the space character
            else if (k == 0 && t == 0)
            {
                MacUILib_printf(" ");
            }
            else
            {
                k = 0;
                t = 0;
            }

        }
        if (i == 5)
        {
            myGM->printSpecialMessages();
        }
        MacUILib_printf("\n");   
    }
    //GAME MESSAGES
    if (myGM->getLoseFlagStatus() == true)
    {
        MacUILib_printf("Self collision occurred! You lose.\nYour final score is: %d\n", myGM->getScore());
    
    }
    else
    {
        MacUILib_printf("Score: %d", myGM->getScore());
        myPlayer->printSpeed();
        MacUILib_printf("\nPress < or > to change Game Speed.\n");
        MacUILib_printf("Press n to generate new food.\n");
    }
    /*
    MacUILib_printf("\n\n----------DEBUGGING INFO----------\n");
    MacUILib_printf("Board Size: <%d, %d>\n", myGM->getBoardSizeX(), myGM->getBoardSizeY());
    myPlayer->printPlayerPosHead();
    myPlayer->printDir();
    MacUILib_printf("\nFood Position: <%d, %d>\nFood Symbol: %c", tempFoodPos.x, tempFoodPos.y, tempFoodPos.symbol);
    */
}

void LoopDelay(void)
{
    MacUILib_Delay(myPlayer->getSpeed()); // 0.1s delay

}


void CleanUp(void)
{
    //MacUILib_clearScreen();
    delete myPlayer;
    delete myGM;  
    delete myFood;  
  
    MacUILib_uninit();
}