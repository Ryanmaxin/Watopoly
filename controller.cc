#include "controller.h"

#include <vector>
#include <iostream>
#include <string>

using std::vector;
using std::cout;
using std::endl;
using std::string;

void Controller::playMonopoly() {
    players.clear(); //<---- probably not necessary
    board.init("default.data"); //<---- filename containing data for all squares

    int num_players; //Get from cin

    //Initialize players vector
    for (size_t i = 0; i < num_players; i++)
    {
        //Get these fields from cin. 
        string player_name;
        char token;

        players.push_back({player_name,token,board});
    }
    

    //players.erase(players.begin() + current_player_id); //<---- use this after bankruptcy to remove current player
    //Successful bankruptcy should immediately go to the next players turn

    //--------------------------------------
    //Game starts being actually played here
    while (true) {
        //Each loop is a players turn
        Player& p = players[current_player_id];


        while (true) {
            string cmd;
            //This loop covers the cmd menu, such as trade, mortage, save.
            //Keep looping until 'next' command
            //At some point...
            if (cmd == "next") {
                nextTurn();
                break;
            }
        }
    }
}
