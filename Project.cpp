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

objPosArrayList* tempPlayerPos;
objPos temp;
//objPos tempPlayerPos;
objPos tempFoodPos;

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
    //myPos.setObjPos(2, 3, '@');
    border.setObjPos(0,0, '#');
    myFood->generateFood();
    bool foodCollision = false;
    myPlayer->increasePlayerLength(0);

    

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
    myFood->getFoodPos(tempFoodPos);
    myPlayer->updatePlayerDir();
    myPlayer->movePlayer();
    //myPlayer->getPlayerPos(tempPlayerPos);
    tempPlayerPos = myPlayer->getPlayerPos();

    // UNCOMMENT AND FIX
    /*if (myPlayer->checkCollision()) {  // Hypothetical function to check self-collision
        myGM->setLoseFlag(true);
        myGM->setExitTrue();
    }*/
    tempPlayerPos->getHeadElement(temp);

    if (temp.x == tempFoodPos.x && temp.y == tempFoodPos.y) {
        myFood->generateFood();
        foodCollision = true;
        myGM->incrementScore(); 
        myPlayer->increasePlayerLength(1);
    }
    
    if (myPlayer->checkSelfCollision())
    {
        myGM->setLoseFlag(true);
        myGM->setExitTrue();
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
                tempPlayerPos->getElement(temp, p); //isnt holding aList
                if (i == temp.y && j == temp.x)
                {
                    MacUILib_printf("%c", temp.symbol);
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
                foodCollision = false;
                k = 0;
            }

        }
        MacUILib_printf("\n");
            
    }
    //GAME MESSAGES

    MacUILib_printf("Score: %d", myGM->getScore());
    
    //MacUILib_printf("Object <%d, %d> with %c\n", myPos.x, myPos.y, myPos.symbol);
    MacUILib_printf("\n\n----------DEBUGGING INFO----------\n");
    MacUILib_printf("Board Size: <%d, %d>\n", myGM->getBoardSizeX(), myGM->getBoardSizeY());
    myPlayer->printPlayerPos();
    myPlayer->printDir();
    MacUILib_printf("\nFood Position: <%d, %d>\nFood Symbol: %c", tempFoodPos.x, tempFoodPos.y, tempFoodPos.symbol);
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay

}


void CleanUp(void)
{
    MacUILib_clearScreen();
    delete myPlayer;
    delete myGM;  
    delete myFood;  
  
    MacUILib_uninit();
}
