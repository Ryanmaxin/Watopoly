#ifndef __UNOWNABLEPROPERTY_H__
#define __UNOWNABLEPROPERTY_H__
#include <string>
#include "square.h"

using std::string;

class UnownableProperty: public Square {
    Action goToTims(Player* player);
    public:
        UnownableProperty(string n);
        Action actionOnLand(Player* player) override;
};
#endif
