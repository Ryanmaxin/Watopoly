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
    bool game_over = false;
    void commenceAuction(Player& p, int current_player_id, OwnableProperty* being_auctioned = nullptr);
    void nextTurn();
    bool command(string cmd, Player& p);
    bool move(Player& p, int roll = 0);
    void load(string filename);
    public:
        Player& playMonopoly();
};

#endif
