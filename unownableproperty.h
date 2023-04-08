#ifndef __UNOWNABLEPROPERTY_H__
#define __UNOWNABLEPROPERTY_H__
#include <string>
#include "square.h"
#include "response.h"

using std::string;

class UnownableProperty: public Square {
    int last_slc_roll;
    public:
        UnownableProperty(string n);
        MoveResponse actionOnLand(Player& player, bool regenerate = true) override;
};
#endif
