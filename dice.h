#ifndef __DICE_H__
#define __DICE_H__

#include <string>
#include <vector>

using std::string;

class Dice {
    int die1;
    int die2;
    int doubles_rolled;
    int random1to6();

    public:
        Dice();
        int roll();
        int setDice(int die1, int die2);
        bool isDoubles();
        bool threeDoubles();
        std::pair<int,int> getFaceValues();
};

#endif
