#ifndef __SQUARES_H__
#define __SQUARES_H__
#include <string>

using std::string;

class Square {
    string name;
    public:
        Square(string n);
        virtual Response actionOnLand() = 0;
        string getName();
};
#endif
