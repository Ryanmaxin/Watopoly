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
    
    void nextTurn();
    void load(string filename);
    public:
        void playMonopoly();
        // void user_input();
        // Response move();
        // void purchase();
        // void auction();
        // bool improve();
        // bool trade();
        // bool mortgage();
        // bool unmortgage();
        // bool bankrupt();
        // bool assets();
        // void all();
        // void save(string the_filename);
};

#endif
