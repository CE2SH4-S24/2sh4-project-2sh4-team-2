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

        bool getFoodCollision();
        void setFoodCollision(bool boolean);

        

    private:
        objPos foodPos;
        objPosArrayList* foodBucket;// this is for above and beyond
        int boardX; // board X size
        int boardY; // board Y size
        bool foodCollision; // flags true when snake head and food collision occurs
        
};

#endif