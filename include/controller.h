#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__

#include "player.h"
#include "textdisplay.h"

#include <string>
#include <vector>
#include <fstream>

using std::string;
using std::vector;

class Controller {
    Board board;
    TextDisplay td;
    vector<Player> players;
    Dice dice;
    int current_player_id;
    bool testing_mode = false;
    bool is_loaded = false;
    string loaded_file;
    void commenceAuction(Player& p, int current_player_id, OwnableProperty* being_auctioned = nullptr);
    void nextTurn();
    bool command(string cmd, Player& p);
    bool move(Player& p, int roll = -1);
    void load(string filename);
    bool validPlayer(string name, char token);
    void bankruptcyOccurence(Player& p);

    void save(const string filename);
    public:
        Player& playMonopoly();
        // setter methods
        void setTestingMode(bool s);
        void setIsLoaded(bool b);
        void setLoadedFile(string file);
};

#endif
