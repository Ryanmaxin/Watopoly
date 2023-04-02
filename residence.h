#ifndef __RESIDENCE_H__
#define __RESIDENCE_H__
#include <string>
#include "ownableproperty.h"

using std::string;

class Residence: public OwnableProperty {
    int num_owned;
    public:
        Residence();
        int getRent() override;
        int getNumOwned();
};
#endif
