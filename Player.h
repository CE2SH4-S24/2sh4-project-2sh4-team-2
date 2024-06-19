#ifndef PLAYER_H
#define PLAYER_H

#include "GameMechs.h"
#include "objPos.h"
#include "objPosArrayList.h" 
//#include "Food.h"

class Food;

class Player
{
    // Construct the remaining declaration from the project manual.

    // Only some sample members are included here

    // You will include more data members and member functions to complete your design.

    public:
        enum Dir {STOP, UP, DOWN, LEFT, RIGHT};  // This is the direction state (FSM)
        
        enum speedLevel //Changes the screen refresh rate
        {
            L1 = 500000, // slowest
            L2 = 350000,
            L3 = 200000,
            L4 = 100000,
            L5 = 50000 // fastest
        }; 

        Player(GameMechs* thisGMRef);
        ~Player();

        objPosArrayList* getPlayerPos();// updated for iteration 3
        void updatePlayerDir();
        void movePlayer();
        void printDir();
        void increasePlayerLength(int growth);
        bool checkSelfCollision();
        int checkFoodConsumption();
        void printPlayerPosHead();
        void printPlayerPosList();
        void initializeSpeed();
        int getSpeed();
        void printSpeed();

        void getPlayerPos(objPos &returnPos) const;  // Getter: Populates returnPos with player's current position
        void setPlayerPos(int x, int y); 
    private:
        objPosArrayList* playPosList;   // Updated in iteration 3.       
        enum Dir myDir;
        enum speedLevel speedLvl;
        bool regenerate;
        int growthby;
        objPos tempObjPos;

        Food* foodRef;

        // Need a reference to the Main Game Mechanisms
        GameMechs* mainGameMechsRef;
};

#endif