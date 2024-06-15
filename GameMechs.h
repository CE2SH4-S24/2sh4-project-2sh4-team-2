#ifndef GAMEMECHS_H
#define GAMEMECHS_H

#include <cstdlib>
#include <time.h>

#include "objPos.h"
#include "objPosArrayList.h"

using namespace std;


class GameMechs
{   
    // GameMechs is the Game Mechanism class
    // Construct the remaining declaration from the project manual.

    // Only some sample members are included here

    // You will include more data members and member functions to complete your design.

    private:
        char input;
        bool exitFlag;
        
        int boardSizeX;
        int boardSizeY;

        bool regenerate;

        int score;

        bool loseFlag;

    public:
        GameMechs();
        GameMechs(int boardX, int boardY);
        //~GameMechs(); //Destructor, may be needed
        
        bool getExitFlagStatus();
        void setExitTrue();

        bool getRegenerateStatus();
        void setRegenerate(bool boolean);

        char getInput();
        void setInput(char this_input);
        void clearInput();

        int getBoardSizeX();
        int getBoardSizeY();
        //need to add more functions

        bool getLoseFlagStatus() const;   
        void setLoseFlag(bool value);

        int getScore() const;  
        void incrementScore(int amount = 1); 

};

#endif