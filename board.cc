#include "board.h"
#include <vector>
#include <string>
#include "player.h"
#include "memory"
#include "unownableproperty.h"
#include "ownableproperty.h"
#include "gym.h"
#include "residence.h"
#include "academicbuilding.h"
#include "enumerations.h"
#include <iostream>

using std::vector;
using std::string;
using std::unique_ptr;
using std::make_unique;
using std::pair;
using std::cout;
using std::endl;

Response Board::interact(Player& player) {

}
void Board::init(vector<pair<string,char>> player_names) {
    //Clear previous state.
    locations.clear();
    players.clear();
    current_player_id = 0;
    current_roll = 0;

    //Initialize players vector
    for (auto name: player_names) {
        players.push_back(make_unique<Player>(name.first,name.second));
    }
    //Initialize squares
    initSquares();

}
vector<unique_ptr<Square>>& Board::get_locations() {
    return locations;
}
vector<unique_ptr<Player>> Board::get_players() {
    return players;
}

void Board::bankruptcy(unique_ptr<Player> giving, unique_ptr<Player> receiving) {
    if (receiving != nullptr) {
        //Owes money to another player
        for (auto property: giving->getProperties()) {
            // transferAsset(giving, receiving, g_prop, g_money, r_prop, r_money)
            receiving->addProperty(property);
        }
        receiving->addBalance(giving->getBalance());
        for (auto mon: giving->getOwnedMonopolies()) {
            if (mon.second == true) {
                receiving->SetOwnedMonopoly(mon.first,true);
            }
        }
    }
    if (receiving == nullptr) {
        //Owes monet to the bank
    }
    //Cleanup, 
    for (auto mon: giving->getOwnedMonopolies()) {
        if (mon.second == true) {
            giving->SetOwnedMonopoly(mon.first, false);
        }
    }
    giving->clearProperties(bool no_owner);
    giving->setBalance(0);
    giving->teleport(0);

}

Response Board::moveCurrentPlayer() {
    int roll = dice.rollDice();
    unique_ptr<Player>& curr_player = players[current_player_id];
    curr_player->move(roll);
    int curr_position = curr_player->getCurrentPosition();
    #ifdef VISUALISATION
        cout << curr_player->getName() << "Moved to " << locations[curr_position]->getName() << endl; 
    #endif
    Response res = locations[curr_position]->actionOnLand();
    return res;
}

void Board::initSquares() {
    //Please implement this!! @Nandish

    
    // locations.push_back(make_unique<UnownableProperty>("COLLECT OSAP"));
    // locations.push_back(make_unique<AcademicBuilding>("AL",Monopoly::Arts1));
    // locations.push_back(make_unique<UnownableProperty>("SLC"));
    // locations.push_back(make_unique<AcademicBuilding>("ML",Monopoly::Arts1));
    // locations.push_back(make_unique<UnownableProperty>(""));
    // locations.push_back(make_unique<UnownableProperty>("COLLECT OSAP"));
    // locations.push_back(make_unique<UnownableProperty>("COLLECT OSAP"));
    // locations.push_back(make_unique<UnownableProperty>("COLLECT OSAP"));
    // locations.push_back(make_unique<UnownableProperty>("COLLECT OSAP"));
    // locations.push_back(make_unique<UnownableProperty>("COLLECT OSAP"));
    // locations.push_back(make_unique<UnownableProperty>("COLLECT OSAP"));
    // locations.push_back(make_unique<UnownableProperty>("COLLECT OSAP"));
    // locations.push_back(make_unique<UnownableProperty>("COLLECT OSAP"));
    // locations.push_back(make_unique<UnownableProperty>("COLLECT OSAP"));
    // locations.push_back(make_unique<UnownableProperty>("COLLECT OSAP"));
    // locations.push_back(make_unique<UnownableProperty>("COLLECT OSAP"));
    // locations.push_back(make_unique<UnownableProperty>("COLLECT OSAP"));
    // locations.push_back(make_unique<UnownableProperty>("COLLECT OSAP"));
    // locations.push_back(make_unique<UnownableProperty>("COLLECT OSAP"));
    // locations.push_back(make_unique<UnownableProperty>("COLLECT OSAP"));
    // locations.push_back(make_unique<UnownableProperty>("COLLECT OSAP"));
    // locations.push_back(make_unique<UnownableProperty>("COLLECT OSAP"));
    // locations.push_back(make_unique<UnownableProperty>("COLLECT OSAP"));
    // locations.push_back(make_unique<UnownableProperty>("COLLECT OSAP"));
    // locations.push_back(make_unique<UnownableProperty>("COLLECT OSAP"));
    // locations.push_back(make_unique<UnownableProperty>("COLLECT OSAP"));
    // locations.push_back(make_unique<UnownableProperty>("COLLECT OSAP"));
    // locations.push_back(make_unique<UnownableProperty>("COLLECT OSAP"));
    // locations.push_back(make_unique<UnownableProperty>("COLLECT OSAP"));
    // locations.push_back(make_unique<UnownableProperty>("COLLECT OSAP"));
    // locations.push_back(make_unique<UnownableProperty>("COLLECT OSAP"));
    // locations.push_back(make_unique<UnownableProperty>("COLLECT OSAP"));
    // locations.push_back(make_unique<UnownableProperty>("COLLECT OSAP"));
    // locations.push_back(make_unique<UnownableProperty>("COLLECT OSAP"));
    // locations.push_back(make_unique<UnownableProperty>("COLLECT OSAP"));
    // locations.push_back(make_unique<UnownableProperty>("COLLECT OSAP"));
    // locations.push_back(make_unique<UnownableProperty>("COLLECT OSAP"));
    // locations.push_back(make_unique<UnownableProperty>("COLLECT OSAP"));
    // locations.push_back(make_unique<UnownableProperty>("COLLECT OSAP"));
    // locations.push_back(make_unique<UnownableProperty>("COLLECT OSAP"));
}
