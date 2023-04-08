#ifndef __OWNABLEPROPERTY_H__
#define __OWNABLEPROPERTY_H__

#include "square.h"

#include <string>
#include <vector>

using std::string;
using std::vector;

class OwnableProperty: public Square {
    protected:
        Player* owner;
        bool is_mortaged;
        int price;
        virtual int getTuition() = 0;
    public:
        OwnableProperty(string n, int p);

        MoveResponse actionOnLand(Player& player, bool regenerate = false);

        virtual string specificContext(Player& player) = 0;

        void setMortgage(bool val);
        bool isMortgaged();

        Player* getOwner();
        void setOwner(Player* new_owner);
        int getPrice();
};
#endif
