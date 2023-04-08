#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__

#include "board.h"

#include <string>
#include <vector>

using std::string;
using std::vector;

class Controller {
    Board board;
    vector<Player> players;
    Dice dice;
    int current_player_id;
    bool player_bankrupted;

    void nextTurn();
    bool command(string cmd, Player& p);
    bool move(Player& p);
    void load(string filename);
    public:
        Player& playMonopoly();
};

#endif
