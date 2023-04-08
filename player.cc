#include "player.h"
#include "response.h"
#include "academicbuilding.h"
#include "residence.h"

#include <sstream>
#include <iostream>

using std::ostringstream;
using std::istringstream;
using std::cout;
using std::endl;
using std::ostream;

Player::Player(string name, char token, Board& attached_to, int bal = 0, bool rur = false, int pos = 0, bool in_jail = false, int num_turns_in_jail = 0):
name{name},token{token},board{attached_to},balance{bal},owns_roll_up{rur},position{pos},in_tims_line{false},num_turns_in_tims_line{num_turns_in_tims_line} {
    current_square = attached_to.getSquare(position);
}

MoveResponse Player::move(int num_spaces) {
    if (!(in_tims_line)) {
        position = (position + num_spaces)%39;
        current_square = board.getSquare(position);
        MoveResponse res = current_square->actionOnLand(*this);
        return res;
    }
    else {
        //Player has 3 choices: pay $50, roll for doubles or use a roll up the rim
        ostringstream oss;
        oss << "In Tims line (" << num_turns_in_tims_line << "turn(s)";
        std::string context = oss.str();
        return {Action::InJail, context};
    }
}

void Player::teleport(int square_index) {
    if (square_index >= 40) {
        #ifdef DEBUG
            cout << "Invalid call to teleport with: " << square_index << endl; 
        #endif
    }
    position = square_index;
    current_square = board.getSquare(position);
}

void Player::transferProperty(OwnableProperty* property, Player* receiving) {
    property->setOwner(receiving);

    for (int i = 0; i < owned_properties.size(); ++i) {
        if (owned_properties[i] == property) {
            owned_properties.erase(owned_properties.begin() + i);
        }
    }
}

string Player::declareBankruptcy() {
    OwnableProperty* cp = dynamic_cast<OwnableProperty*>(current_square);
    Player* receiving;
    if (cp == nullptr) {
        //Declare bankruptcy to the bank
        receiving = nullptr;
    }
    else {
        //Declare bankruptcy to another player
        receiving = cp->getOwner();
        receiving->balance += balance;
    }
    for (auto property: owned_properties) {
            transferProperty(property,receiving);
    }
    balance = 0;
    teleport(0);
    return "";
}

MoveResponse Player::buy() {
    ostringstream oss;
    Action action;
    OwnableProperty* ownable = dynamic_cast<OwnableProperty*>(current_square);
    int price = ownable->getPrice();
    if (balance < price) {
        oss << name << ": Can't afford property price of " << price << " (Have " << balance << ")";
        action = Action::CantAfford;
    } else {
        owned_properties.push_back(ownable);
        balance = balance - price;
        AcademicBuilding* academic = dynamic_cast<AcademicBuilding*>(ownable);
        Monopoly set = academic->getSet();
        oss << name << ": Successfully purchased " << price << " (Have " << balance << ")";
        action = Action::NoAction;
    }
    std::string context = oss.str();
    return {action,context};

}

string Player::goToTims() {
    teleport(DC_TIMS_LINE);
    in_tims_line = true;
}

MoveResponse Player::payTuition(int amount) {
    ostringstream oss;
    Action action;
    if (balance < amount) {
        oss << name << ": Can't afford tuition price of " << amount << "(Have " << balance << ")";
        action = Action::CantPayTuition;
    }
    else {
        oss << name << ": Paid tuition of $300 ";
        balance - 300;
        action = Action::NoAction;
    }
    string context = oss.str();
    return {action,context};
}

int Player::getNetWorth() const {
    int running_sum = balance;
    for (auto property: owned_properties) {
        running_sum += property->getPrice();
        AcademicBuilding* academic = dynamic_cast<AcademicBuilding*>(property);
        if (academic) {
            running_sum += academic->getNumberOfImprovements() * academic->getImprovementCost();
        }
    }
    return running_sum;
}
int Player::getBalance() const {
    return balance;
}
void Player::setBalance(int new_balance) {
    balance = new_balance;
}
void Player::addBalance(int money) {
    balance += money;
}

string Player::getName() const {
    return name;
}

bool Player::ownsProperty(Square* property) const {
    for (auto owned_property: owned_properties) {
        if (property == owned_property) return true;
    }
    return false;
}
bool Player::ownsMonopoly(Monopoly set) const {
    int num_in_set = 3;
    int num_found = 0;
    if (set == Monopoly::Arts1 || set == Monopoly::Math) num_in_set = 2;
    for (int i = 0; i < num_in_set; ++i) {
        for (auto owned_property: owned_properties) {
            AcademicBuilding* academic = dynamic_cast<AcademicBuilding*>(owned_property);
            if (academic && academic->getSet() == set) {
                ++num_found;
            }
        }
    }
    if (num_found == num_in_set) return true;
    return false;
}
int Player::numberOfOwnedGyms() const {
    int num_found = 0;
    for (auto owned_property: owned_properties) {
        Gym* gym = dynamic_cast<Gym*>(owned_property);
        if (gym) {
            ++num_found;
        }
    }
    return num_found;
}
int Player::numberOfOwnedResidences() const {
    int num_found = 0;
    for (auto owned_property: owned_properties) {
        Residence* residence = dynamic_cast<Residence*>(owned_property);
        if (residence) {
            ++num_found;
        }
    }
    return num_found;
}

ostream& operator<<(ostream& out, const Player& player) {
    out << "-----[Assets of " << player.name << "]-----" << endl;
    out << "Balance: $" << player.balance << endl;
    out << std::boolalpha << "Owns roll up rim: " << player.owns_roll_up << endl;
    for (auto property: player.owned_properties) {
        AcademicBuilding* academic = dynamic_cast<AcademicBuilding*>(property);
        if (academic) {
            out << property->getName() << ": " << academic->getNumberOfImprovements() << " improvements" << endl;
        }
        else {
            out << property->getName();
        }
    }
    out << "Total net worth: " << player.getNetWorth() << endl;

}

// for the asset function, something like: 
//     void displayAssets() const {
       // cout << "Assets for player " << name << ":" << endl;
        //cout << "Cash: " << cash << endl;
        //cout << "Properties:" << endl;
        //for (const auto& prop : properties) {

string Player::offerTrade(string o_name, string give, string receive) {
    //assert name, give, receive
    int g, r;
    istrigstream iss_g {give};
    istrigstream iss_r {receive};
    iss_g >> g;
    iss_r >> r;
    if (iss_g && iss_r) { // means both give and receive are integers
        cout << "Invalid Input" << endl;
    } else if (iss_g && !iss_r) { // means give is an int and receive is a string
        balance -= give;
        transferProperty(receive, name);
    } else if (!iss_g && iss_r) { // means give is a string and receive is an int
        transferProperty(give, o_name);
        balance += receive;
    } else { // means both give and receive are strings
        transferProperty(give, o_name);
        transferProperty(receive, name);
    }
}

string Player::improve(string property, string buysell) {
    // check for monopoly formed and enough balance to improve a property
    
}
