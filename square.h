#ifndef __SQUARES_H__
#define __SQUARES_H__
#include <string>
#include "enumerations.h"
#include "player.h"
#include "response.h"

using std::string;

class Square {
    protected:
        string name;
    public:
        Square(string n);
        virtual MoveResponse actionOnLand(Player& player) = 0;
        string getName();
};
#endif
