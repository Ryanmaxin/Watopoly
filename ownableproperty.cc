#include "ownableproperty.h"
#include "player.h"
#include <sstream>
#include <vector>
#include <string>
#include <iostream>

using std::vector;
using std::string;
using std::ostringstream;
using std::endl;

OwnableProperty::OwnableProperty(string n, int p):
Square{n}, owner{nullptr},price{p}, is_mortaged{false} {}

Player* OwnableProperty::getOwner() {
    return owner;
}
void OwnableProperty::setOwner(Player* new_owner) {
    owner = new_owner;
}
int OwnableProperty::getPrice() {
    return price;
}

void OwnableProperty::setMortgage(bool val) {
    is_mortaged = val;
}

bool OwnableProperty::isMortgaged() {
    return is_mortaged;
}

MoveResponse OwnableProperty::actionOnLand(Player& player, bool regenerate) {
    ostringstream oss;
    Action action;
    if (owner) {
        if (owner == &player) {
            action = Action::NoAction;
            oss << player.getName() << ": Landed on your own property";
        }
        else if (is_mortaged) {
            oss << player.getName() << ": No tuition due because the property is mortgaged";
        }
        else {
            int tuition = getTuition();
            oss << specificContext(player) << "\n";
            if (player.getBalance() < tuition) {
                action = Action::CantPayTuition;
                oss << player.getName() << ": Can't afford $" << tuition << " owed to " << owner->getName() << " for landing on " << name << "(have $" << player.getBalance() << ")";
                oss << endl << player.getName() << "choices: {raisefunds} {bankruptcy} ";
            }
            else {
                action = Action::NoAction;
                oss << player.getName() << ": Paid $" << tuition << " to " << owner->getName() << " for landing on " << name;
                player.addBalance(-1 * tuition);
                owner->addBalance(tuition);
            }
        }
    } 
    else {

        
        int price = getPrice();
        // if (player.getBalance() < price) {
        //     action = Action::CantAfford;
        //     oss << player.getName() << ": Can't afford $" << price << " to buy " << name << "(have $" << player.getBalance() << ")";
        //     oss << endl << player.getName() << "choices: {raisefunds} {auction} ";
        // }
        action = Action::BuyOrAuction;
        oss << player.getName() << ": " << name << " available for purchase for " << price << "(have $" << player.getBalance() << ")";
        oss << endl << player.getName() << "choices: {buy} {auction} ";
    }
    
    string context = oss.str();
    return {action, context};
}

