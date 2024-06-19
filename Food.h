#ifndef FOOD_H
#define FOOD_H
#include "objPosArrayList.h"
#include "GameMechs.h"

class Food
{    
    public:
        Food();
        ~Food();

        void generateFood(objPosArrayList* blockoff);
        void getFoodPos(objPos &returnPos, int index);
        objPosArrayList* getFoodList();

        void getBoardSize(GameMechs* gamemechs); //references the GameMechs class to store size of board

        

    private:
        objPos foodPos;
        objPosArrayList* foodBucket;// this is for above and beyond
        int boardX; // board X size
        int boardY; // board Y size
        
};

#endif