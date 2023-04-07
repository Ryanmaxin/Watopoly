#ifndef __RESIDENCE_H__
#define __RESIDENCE_H__
#include <string>
#include "ownableproperty.h"

using std::string;

class Residence: public OwnableProperty {
    int getTuition() override;
    public:
        Residence(string name, int p);
        
        string specificContext(Player& player) override;
};
#endif
