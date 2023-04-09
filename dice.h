#ifndef __DICE_H__
#define __DICE_H__

#include <string>
#include <vector>

using std::string;

class Dice {
    int die1;
    int die2;
    int doubles_rolled;
    int rollDie1();
    int rollDie2();
    int rollInternal(std::vector<int> const & v );
    bool testingmode = false;

    public:
        Dice();
        int roll();
        int roll(int die1, int die2);
        void thetesting(bool value);
        bool isDoubles();
        bool threeDoubles();
        int getDie1();
        int getDie2();
        std::pair<int,int> getFaceValues();
        void setDie1(int value);
        void setDie2(int value);
};

#endif
