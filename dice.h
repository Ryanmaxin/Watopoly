#ifndef __DICE_H__
#define __DICE_H__

#include <string>
#include "square.h"
#include "player.h"
#include "gym.h"

using std::string;

class Dice {
    int die1;
    int die2;
    int doubles_rolled;
    int rollDie1();
    int rollDie2();
    public:
        Dice();
        int roll();
        bool isDoubles();
        bool threeDoubles();
        std::pair<int,int> getFaceValues();
};

#endif
