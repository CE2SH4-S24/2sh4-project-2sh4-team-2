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

    myGM = new GameMechs(20, 10);
    myPlayer = new Player(myGM);
    myFood = new Food(myPlayer, myGM);
    border.setObjPos(0,0, '#'); //starting position and character symbol of border to be printed
    myFood->generateFood(*(myPlayer->getPlayerPos())); //generates a random coordinate for food
    bool foodCollision = false; // initializes snake head collision with food to false
    myPlayer->increasePlayerLength(0); //initializes player length growth to 0;
    myGM->setLoseFlag(false);
    myPlayer->initializeSpeed();
    

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
        myFood->generateFood(*(myPlayer->getPlayerPos()));
        myGM->setRegenerate(false);
        
    }
    myFood->getFoodPos(tempFoodPos);
    myPlayer->updatePlayerDir();
    myPlayer->movePlayer();
    //myPlayer->getPlayerPos(tempPlayerPos);
    tempPlayerPos = myPlayer->getPlayerPos();

 
    tempPlayerPos->getHeadElement(temp);
    foodCollision = false;

    
    if (temp.x == tempFoodPos.x && temp.y == tempFoodPos.y) {
        foodCollision = true;
        if(tempFoodPos.symbol == 'O') {
            myGM->incrementScore(30); 
            myPlayer->increasePlayerLength(3);
        } else{
            myGM->incrementScore(10); 
            myPlayer->increasePlayerLength(1);
        }
        myFood->generateFood(*(myPlayer->getPlayerPos()));
    }
    
    if (myPlayer->checkSelfCollision())
    {
       myGM->setLoseFlag(true);
    //    
    }
}

void DrawScreen(void)
{
    int k = 0;
    
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
            if (i == 0 || i == (myGM->getBoardSizeY() - 1) || j == 0 || j == (myGM->getBoardSizeX() - 1))
            {
                MacUILib_printf("%c", border.getSymbol());
            }
    //          If at food item position, print food symbol
            else if(!foodCollision && i == (tempFoodPos.y) && j == (tempFoodPos.x))
            {
                MacUILib_printf("%c", tempFoodPos.symbol);
            }
    //          Otherwise, print the space character
            else if (k == 0)
            {
                MacUILib_printf(" ");
            }
            else
            {
                k = 0;
            }

        }
        MacUILib_printf("\n");
            
    }
    //GAME MESSAGES
    if (myGM->getLoseFlagStatus() == true)
    {
        MacUILib_printf("Self collision occurred! You lose.\nYour final score is: %d", myGM->getScore());
    }
    else
    {
        MacUILib_printf("Score: %d", myGM->getScore());
    }
    myPlayer->printSpeed();
    MacUILib_printf("Press < or > to change Game Speed.\n");
    MacUILib_printf("\n\n----------DEBUGGING INFO----------\n");
    MacUILib_printf("Board Size: <%d, %d>\n", myGM->getBoardSizeX(), myGM->getBoardSizeY());
    myPlayer->printPlayerPosHead();
    myPlayer->printDir();
    MacUILib_printf("\nFood Position: <%d, %d>\nFood Symbol: %c", tempFoodPos.x, tempFoodPos.y, tempFoodPos.symbol);
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