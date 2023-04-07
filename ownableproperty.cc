#include "ownableproperty.h"
#include "square.h"

#include <sstream>
#include <vector>
#include <string>

using std::vector;
using std::string;
using std::ostringstream;

OwnableProperty::OwnableProperty(string n, int p):
Square{n}, owner{nullptr},price{p} {}

Player* OwnableProperty::getOwner() {
    return owner;
}
void OwnableProperty::setOwner(Player* new_owner) {
    owner = new_owner;
}
int OwnableProperty::getPrice() {
    return price;
}

MoveResponse OwnableProperty::actionOnLand(Player& player) {
    ostringstream oss;
    Action action;
    int tuition = getTuition();
    oss << specificContext(player) << "\n";
    if (player.getBalance() < tuition) {
        action = Action::CantPayRent;
        oss << player.getName() << ": Can't afford $" << tuition << " owed to " << owner->getName() << " for landing on " << name << "(have $" << player.getBalance() << ")";
    }
    else {
        action = Action::NoAction;
        oss << player.getName() << ": Paid $" << tuition << " to " << owner->getName() << " for landing on " << name;
    }
    string context = oss.str();
    return {action, context};
}

