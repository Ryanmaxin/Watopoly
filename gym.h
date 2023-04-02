#ifndef __GYM_H__
#define __GYM_H__
#include <string>
#include "ownableproperty.h"
#include "board.h"

using std::string;

class Gym: public OwnableProperty {
    public:
        int getCurrentRoll(); //Add as friend for board
        Gym();
        int getRent() override;
};
#endif

