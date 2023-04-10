#ifndef __SQUARES_H__
#define __SQUARES_H__

#include <string>
#include "subject.h"

class Player;
struct MoveResponse;

using std::string;

class Square: public Subject {
    protected:
        string name;
    public:
        Square(string n);
        virtual ~Square() = default;
        virtual MoveResponse actionOnLand(Player& player, bool regenerate = true) = 0;
        string getName();
};

#endif
