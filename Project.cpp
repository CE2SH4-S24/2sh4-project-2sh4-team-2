#include <iostream> 
#include "MacUILib.h"
#include "objPos.h"
#include "GameMechs.h"
#include "Player.h"
#include "Food.h"

using namespace std;
#define DELAY_CONST 100000

Player* myPlayer; 
objPos border;
Food* myFood;
objPos tempFoodPos; // holds one objPos value of food (food coordinates)
objPosArrayList* tempPlayerPos;
objPos temp; // holds one objPos index value of playerPosList (snake body coordinates)
GameMechs* myGM;


//Function Declarations

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);



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


//Function Definitions

void Initialize(void)
{
    MacUILib_init();
    MacUILib_clearScreen();
    
    myGM = new GameMechs(28, 14); 
    myPlayer = new Player(myGM);
    myFood = new Food(); 
    
    border.setObjPos(0,0, '#'); //starting position and character symbol of border to be printed
    tempPlayerPos = myPlayer->getPlayerPos();
    myFood->getBoardSize(myGM);
    myFood->generateFood(tempPlayerPos); //generates a random coordinate for food
    //myFood->setFoodCollision(false);// initializes snake head collision with food to false
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
    if(myGM->getRegenerateStatus()) //checks for call to generate food, if true, generate food
    {
        myFood->generateFood(tempPlayerPos);
        myGM->setRegenerate(false);
    }

    myPlayer->updatePlayerDir(); 
    myPlayer->movePlayer();
    
    tempPlayerPos = myPlayer->getPlayerPos();
 
    tempPlayerPos->getHeadElement(temp); //store objPos element head of snake in temp
    myFood->setFoodCollision(false); // re-initialize foodCollisison to false every run, not just in Initialize()
    
    objPos tempFoodPos;

    if (myGM->getGameMsg()) // checks if special game messages should be printed
    {
        myGM->addCountMsg(); //monitors delay counter for special messages
    }
    else
    {
        myGM->resetCountMsg(); //reinitializes delay counter
    }

    for (int n = 0; n < 5; n++) //checks all 5 food items for collision with snake
    {
        myFood->getFoodPos(tempFoodPos, n);
        if (temp.x == tempFoodPos.x && temp.y == tempFoodPos.y)
        {
            myFood->setFoodCollision(true);
            
            if(tempFoodPos.symbol == '0') //depending on food symbol collided with, outcome changes
            {
                myGM->incrementScore(30); //self explanatory, increases score by 30
                myPlayer->increasePlayerLength(0);
                myGM->setGameMsg(1); //sets special game message, prints: "+30 score! +0 length!"
                myGM->resetCountMsg(); //resets delay counter for special message
            } 
            else if(tempFoodPos.symbol == '+') 
            {
                myGM->incrementScore(50); 
                myPlayer->increasePlayerLength(5);
                myGM->setGameMsg(2); //special game message: "+50 score! +5 length!"
                myGM->resetCountMsg();
            } 
            else 
            {
                myGM->incrementScore(10); 
                myPlayer->increasePlayerLength(1);
                myGM->setGameMsg(3); // special game message: "+10 score! +1 length!"
                myGM->resetCountMsg(); 
            }
            //myFood->generateFood(tempPlayerPos);
            myGM->setRegenerate(true);
            break;
        }
    }
    
    if (myPlayer->checkSelfCollision()) // if snake head collides with snake body, game exits
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
                if (!(myFood->getFoodCollision()) && i == (tempFoodPos.y) && j == (tempFoodPos.x))
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
            myGM->printSpecialMessages(); //prints score and length messages when collision with food occurs
        }
        MacUILib_printf("\n");   
    }
    //GAME MESSAGES
    if (myGM->getLoseFlagStatus() == true) // messages to be printed when exitflag is true
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

    //Debugging print messages
    /*
    MacUILib_printf("\n\n----------DEBUGGING INFO----------\n");
    MacUILib_printf("Board Size: <%d, %d>\n", myGM->getBoardSizeX(), myGM->getBoardSizeY());
    myPlayer->printPlayerPosList();
    myPlayer->printDir();
    MacUILib_printf("\nFood Position: <%d, %d>\nFood Symbol: %c", tempFoodPos.x, tempFoodPos.y, tempFoodPos.symbol);
    */
}
void LoopDelay(void)
{
    MacUILib_Delay(myPlayer->getSpeed()); // enumeration, player can decide delay using input keys '<' '>'

}


void CleanUp(void)
{
    //MacUILib_clearScreen(); //commented out on purpose, shows game at point when player dies
    //deallocate space on heap
    delete myPlayer; 
    delete myGM;  
    delete myFood;  
  
    MacUILib_uninit();
}