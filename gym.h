#ifndef GYM_H
#define GYM_H
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

