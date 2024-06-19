#ifndef FOOD_H
#define FOOD_H
#include "objPosArrayList.h"
#include "Player.h"
#include "GameMechs.h"

class Food
{    
    public:
        Food(Player* thisPlrRef, GameMechs* thisGMRef);
        ~Food();

        void generateFood();
        void getFoodPos(objPos &returnPos, int index);
        

    private:
        objPos foodPos;
        objPosArrayList* foodBucket;// this is for above and beyond

        // Need a reference to the Main Game Mechanisms
        GameMechs* mainGMRef;
        Player* mainPlayer;
        
};

#endif