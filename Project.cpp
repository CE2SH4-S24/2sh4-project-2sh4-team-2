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


//bool exitFlag;
GameMechs* myGM;

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

}


void Initialize(void)
{
    MacUILib_init();
    MacUILib_clearScreen();

    myGM = new GameMechs(20, 10);
    myPlayer = new Player(myGM);
    //myPos.setObjPos(2, 3, '@');
    border.setObjPos(0,0, '#');
    
    myFood = new Food(myPlayer, myGM);

}

void GetInput(void)
{
    if (MacUILib_hasChar())
    {
        myGM->setInput(MacUILib_getChar());
    }   
}

void RunLogic(void)
{
    myPlayer->updatePlayerDir();
    myPlayer->movePlayer();
}

void DrawScreen(void)
{
    objPos tempPlayerPos;
    myPlayer->getPlayerPos(tempPlayerPos);
    objPos tempFoodPos;
    myFood->getFoodPos(tempFoodPos);
    

    MacUILib_clearScreen();
    for (int i = 0; i < myGM->getBoardSizeY(); i++)
    {
        for (int j = 0; j < myGM->getBoardSizeX(); j++)
        {

            if (i == 0 || i == (myGM->getBoardSizeY() - 1) || j == 0 || j == (myGM->getBoardSizeX() - 1))
            {
                MacUILib_printf("%c", border.getSymbol());
            }
    //          If at the player object position, print the player symbol
            else if (i == tempPlayerPos.y && j == tempPlayerPos.x)
            {
                MacUILib_printf("%c", tempPlayerPos.symbol);
            }
    //          If at food item position, print food symbol
            else if(i == (tempFoodPos.y) && j == (tempFoodPos.x))
            {
                MacUILib_printf("%c", tempFoodPos.symbol);
            }
    //          Otherwise, print the space character
            else
            {
                MacUILib_printf(" ");

            }

        }
        MacUILib_printf("\n");
            
    }
    //MacUILib_printf("Object <%d, %d> with %c\n", myPos.x, myPos.y, myPos.symbol);
    MacUILib_printf("\n\n----------DEBUGGING INFO----------\n");
    MacUILib_printf("Board Size: <%d, %d>\nPlayer Position: <%d, %d>\nPlayer Symbol: %c\n", myGM->getBoardSizeX(), myGM->getBoardSizeY(), tempPlayerPos.x, tempPlayerPos.y, tempPlayerPos.symbol);
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
