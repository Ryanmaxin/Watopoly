#ifndef __OWNABLEPROPERTY_H__
#define __OWNABLEPROPERTY_H__

#include "square.h"
#include "player.h"

#include <string>
#include <vector>

using std::string;
using std::vector;

class OwnableProperty: public Square {
    Player* owner;
    int price;
    // vector<int> rent_vector;
    public:
        OwnableProperty(string n, int p);

        virtual int getRent() = 0;

        Player* getOwner();
        void setOwner(Player* new_owner);
        
        int getPrice();
};
#endif
