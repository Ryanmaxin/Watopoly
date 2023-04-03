#ifndef __SQUARES_H__
#define __SQUARES_H__
#include <string>
#include "enumerations.h"

using std::string;

class Square {
    string name;
    public:
        Square(string n);
        virtual Action actionOnLand() = 0;
        string getName();
};
#endif
