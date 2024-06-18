#ifndef PLAYER_H
#define PLAYER_H

#include "GameMechs.h"
#include "objPos.h"
#include "objPosArrayList.h" 

class Player
{
    // Construct the remaining declaration from the project manual.

    // Only some sample members are included here

    // You will include more data members and member functions to complete your design.

    public:
        enum Dir {STOP, UP, DOWN, LEFT, RIGHT};  // This is the direction state (FSM)
        
        Player(GameMechs* thisGMRef);
        ~Player();

        objPosArrayList* getPlayerPos();// updated for iteration 3
        void updatePlayerDir();
        void movePlayer();
        void printDir();
        //bool checkCollision() const;
        void increasePlayerLength(int growth);
        bool checkSelfCollision();
        void printPlayerPos();

        void getPlayerPos(objPos &returnPos) const;  // Getter: Populates returnPos with player's current position
        void setPlayerPos(int x, int y); 
    private:
        objPosArrayList* playPosList;   // Updated in iteration 3.       
        enum Dir myDir;
        bool regenerate;
        int growthby;
        objPos tempObjPos;


        // Need a reference to the Main Game Mechanisms
        GameMechs* mainGameMechsRef;
};

#endif