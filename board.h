#ifndef __BOARD_H__
#define __BOARD_H__
#include <vector>
#include "square.h"
#include "player.h"
#include "dice.h"
#include "response.h"
#include "memory"

using std::vector;
using std::unique_ptr;
using std::pair;

class Board {
    //Must be smart pointers, i can explain.
    vector<unique_ptr<Square>> locations;
    vector<unique_ptr<Player>> players;
    int current_roll = 0;
    int current_player_id = 0;
    int current_roll_up_rims = 0;
    Dice dice;
    void initSquares();
    public:
        Response interact(Player& player);
        //Init sets up the board. Every time you start a game this should be called.
        //Should be called from within Controller.
        //Takes in a vector of std::pairs, one index for each player in the game
        //The string will be the name, char will be the token chosen.
        void init(vector<pair<string,char>> player_names);
        vector<unique_ptr<Square>>& get_locations();
        vector<unique_ptr<Player>> get_players();
        int getCurrentRoll();
        Player* getCurrentPlayer();
        void bankruptcy(unique_ptr<Player> giving, unique_ptr<Player> receiving);
        bool transferAsset(unique_ptr<Player> giving, unique_ptr<Player> receiving);
        Response moveCurrentPlayer();
        void nextTurn();
        Square* stringToProperty(string property);
};

#endif
