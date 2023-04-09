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
    public:
        Dice();
        int roll();
        bool isDoubles();
        bool threeDoubles();
        int getDie1();
        int getDie2();
        std::pair<int,int> getFaceValues();
};

#endif
