#ifndef BOARD_H
#define BOARD_H
#include <vector>

using std::vector;

class Board {
    vector<Squares&> locations;
    vector<Player&> players;
    int current_roll:
    int current_player;
    Die dice;
    public:
        Response interact(Player& player);
        void init();
        vector<Squares&> get_locations();
        vector<Players&> get_players();
        int get_current_roll();
        vector<Players&> get_current_players();
};

#endif
