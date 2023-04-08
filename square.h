#ifndef __SQUARES_H__
#define __SQUARES_H__

#include <string>

class Player;
struct MoveResponse;

using std::string;

class Square {
    protected:
        string name;
    public:
        Square(string n);
        virtual MoveResponse actionOnLand(Player& player, bool regenerate = true) = 0;
        string getName();
};

#endif
