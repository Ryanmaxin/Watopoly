#ifndef __GYM_H__
#define __GYM_H__

#include <string>

#include "ownableproperty.h"
#include "dice.h"

using std::string

class Gym: public OwnableProperty {
    Dice dice;
    int getTuition() override;
    public:
        Gym(string name, int p);

        string specificContext(Player& player) override;
};

#endif
