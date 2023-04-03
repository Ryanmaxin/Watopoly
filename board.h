#ifndef __BOARD_H__
#define __BOARD_H__
#include <vector>
#include "square.h"
#include "player.h"
#include "dice.h"
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
        //Init sets up the board. Every time you start a game this should be called.
        //Should be called from within Controller.
        //Takes in a vector of std::pairs, one index for each player in the game
        //The string will be the name, char will be the token chosen.
        void init(vector<pair<string,char>> player_names);
        vector<unique_ptr<Square>>& getLocations();
        vector<unique_ptr<Player>> getPlayers();
        Player* getCurrentPlayer();
        //Return the square the current player is standing on
        Square* getCurrentSquare();
        //Invariant: a player can only go bankrupt when it is their turn
        void bankruptcy();
        bool transferAsset(unique_ptr<Player> giving, unique_ptr<Player> receiving);
        Action moveCurrentPlayer();
        void nextTurn();
        //Returns a pointer to the property, if it exists
        Square* stringToProperty(string property);
        //You will have to do validation checking if player has enough money, etc
        void purchaseCurrentProperty();
        //If bankruptcy just occured, do not call nextTurn, as current_player_id will now refer to the next player automatically.
        void nextTurn();
        //Says if the player needs to move again. For use by Controller
        //Doesn't actually move the player
        bool moveAgain();
        void goToJail();
};

#endif
