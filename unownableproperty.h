#ifndef __UNOWNABLEPROPERTY_H__
#define __UNOWNABLEPROPERTY_H__
#include <string>
#include "square.h"
#include "response.h"

using std::string;

class UnownableProperty: public Square {
    public:
        UnownableProperty(string n);
        MoveResponse actionOnLand(Player& player) override;
};
#endif
