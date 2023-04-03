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
vector<unique_ptr<Square>>& Board::getLocations() {
    return locations;
}
vector<unique_ptr<Player>> Board::getPlayers() {
    return players;
}
Player* Board::getCurrentPlayer() {
    return players[current_player_id].get();
}
Square* Board::getCurrentSquare() {
    return locations[getCurrentPlayer()->getCurrentPosition()].get();
}

Square* Board::stringToProperty(string property) {
    for (size_t i; i < 40; ++i) {
        if (locations[i]->getName() == property) {
            return locations[i].get();
        }
    }
    //If no property found
    return nullptr;
}
bool Board::moveAgain() {
    return (dice.isDoubles());
}

void Board::bankruptcy() {
    Player* giving = getCurrentPlayer();
    OwnableProperty* curr_prop = dynamic_cast<OwnableProperty*>(getCurrentSquare());
    Player* receiving = curr_prop->getOwner();
    for (auto property: giving->getProperties()) {
        //Note: receiver may be nullptr. In this case, property is going back to bank.
        giving->transferProperty(property,receiving);
    }
    if (receiving != nullptr) {
        //Additional logic needed when owing assets to another player.
        receiving->addBalance(giving->getBalance());
        for (auto mon: giving->getOwnedMonopolies()) {
            if (mon.second == true) {
                receiving->SetOwnedMonopoly(mon.first,true);
            }
        }
    }
    //Cleanup, 
    for (auto mon: giving->getOwnedMonopolies()) {
        if (mon.second == true) {
            giving->SetOwnedMonopoly(mon.first, false);
        }
    }
    giving->setBalance(0);
    giving->teleport(0);
    //Remove the player
    players.erase(players.begin() + current_player_id);
    #ifdef VISUALISATION
        cout << curr_player->getName() << "Went Bankrupt to " << ((receiving==nullptr)?"Bank": receiving->getName()) << endl;
    #endif
}

void Board::goToJail() {
    Player* player = getCurrentPlayer();
    player->teleport(DC_TIMS_LINE);
    player->setIsInJail(true);
    #ifdef VISUALISATION
        cout << curr_player->getName() << "Was sent to DC TIMS LINE " << endl;
    #endif
}

void Board::nextTurn() {
    current_player_id += 1;
}

void Board::purchaseCurrentProperty() {
    Player* player = getCurrentPlayer();
    Square* property = getCurrentSquare();

    OwnableProperty* ownable = dynamic_cast<OwnableProperty*>(property);
    int price = ownable->getPrice();
    player->addProperty(property);
    player->addBalance(-1*price);
}

Action Board::moveCurrentPlayer() {
    Player* player = getCurrentPlayer();
    if (!(player->isInJail())) {
        int roll = dice.rollDice();
        player->move(roll);
        Square* curr_square = getCurrentSquare();
        #ifdef VISUALISATION
            cout << curr_player->getName() << "Moved to " << curr_square->getName() << endl; 
        #endif
        Action res = curr_square->actionOnLand(player);
        if (res == Action::ChainMove) {
            res = curr_square->actionOnLand(player);
        }
        return res;
    }
    else {
        //Player has 3 choices: pay $50, roll for doubles or use a roll up the rim
        return Action::InJail;
    }
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
