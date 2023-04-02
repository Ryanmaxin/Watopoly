#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <vector>
#include <map>

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
