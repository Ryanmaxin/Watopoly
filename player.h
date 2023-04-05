#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "square.h"
#include "enumerations.h"

#include <vector>
#include <map>

using std::vector;
using std::map;

class Player {
    int cur_pos;
    int balance;
    vector<Squares &> owned_properties;
    map<Monopoly, bool> owned_monopolies;
    public:
        int getCurrentPosition();
        bool ownsMonopoly(Monopoly monopoly);
};
#endif
