#ifndef __OWNABLEPROPERTY_H__
#define __OWNABLEPROPERTY_H__
#include <string>
#include "square.h"
#include "player.h"

using std::string;

class OwnableProperty: public Square {
    Player* owner;
    public:
        OwnableProperty(string n);
        virtual int getRent() = 0;
        Player* getOwner();
};
#endif
