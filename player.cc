#include "player.h"
#include "response.h"
#include "academicbuilding.h"
#include "residence.h"

#include <sstream>
#include <iostream>

using std::ostringstream;
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
    receiving->owned_properties.push_back(property);
    for (int i; i < owned_properties.size(); ++i) {
        if (owned_properties[i] == property) {
            owned_properties.erase(owned_properties.begin() + i);
        }
    }
}

ChoiceResponse Player::declareBankruptcy() {
    ostringstream oss;
    OwnableProperty* cp = dynamic_cast<OwnableProperty*>(current_square);
    Player* receiving;
    bool action;
    int tab = 0;
    if (cp == nullptr) {
        receiving = nullptr;
        oss << name << ": Went bankrupt, all assets transferred to the bank. All properties will auctioned";
        removeRollUp();
        action = true;
    }
    else {
        //Declare bankruptcy to another player
        receiving = cp->getOwner();
        receiving->balance += balance;
        oss << name << ": Went bankrupt, all assets transferred to " << receiving->getName();
        if (owns_roll_up) {
            receiving->owns_roll_up = true;
            owns_roll_up = false;
        }
        action = false;
    }

    for (auto property: owned_properties) {
        AcademicBuilding* academic = dynamic_cast<AcademicBuilding*>(cp);
        if (academic && !cp) {
            tab+= academic->sellAllImprovements();
        }
        transferProperty(property,receiving);
    }
    balance = 0;
    teleport(0);
    string context = oss.str();
    return {action,context};
}

ChoiceResponse Player::buy(OwnableProperty* property) {
    if (property == nullptr) property = dynamic_cast<OwnableProperty*>(current_square);
    ostringstream oss;
    bool action;
    int price = property->getPrice();
    if (balance < price) {
        oss << name << ": Can't afford property price of " << price << " (Have " << balance << ")";
        action = false;
    } else {
        owned_properties.push_back(property);
        balance = balance - price;
        oss << name << ": Successfully purchased " << price << " (Have " << balance << ")";
        action = true;
    }
    std::string context = oss.str();
    return {action,context};

}

ChoiceResponse Player::settleDebts() {
    MoveResponse res = current_square->actionOnLand(*this, false);
    bool success;
    ostringstream oss;
    if (res.action == Action::CantPayTuition) {
        success = false;
    }
    else {
        success = true;
    }
    string context = oss.str();
    return {success,context};
}

string Player::goToTims() {
    teleport(DC_TIMS_LINE);
    in_tims_line = true;
}

ChoiceResponse Player::payTuition(int amount) {
    ostringstream oss;
    bool action = false;
    if (balance < amount) {
        oss << name << ": Can't afford tuition price of " << amount << "(Have " << balance << ")";
        action = false;
    }
    else {
        oss << name << ": Paid tuition of $" << amount << endl;
        balance - 300;
        action = true;
    }
    string context = oss.str();
    return {action,context};
}

string Player::Mortgage(string property) {
    OwnableProperty* op = dynamic_cast<OwnableProperty*>(board.stringToProperty(property));
    AcademicBuilding* academic = dynamic_cast<AcademicBuilding*>(op);
    ostringstream oss;
    if (op && ownsProperty(op)) {
        if (op->isMortgaged()) {
            oss << name << ": " << op->getName() << " already mortgaged";
        }
        else if (academic && academic->getNumberOfImprovements() > 0) {
            oss << name << ": " << op->getName() << " can't be mortgaged because it has " << academic->getNumberOfImprovements() << " improvements";
        }
        else {
            op->setMortgage(true);
            balance += op->getPrice() * 0.5;
            oss << name << ": " << op->getName() << " mortgaged, received $" << op->getPrice() * 0.5;
        }
    }
    else if (!ownsProperty(op)){
        oss << name << ": You do not own" << op->getName();
    }
    else {
        oss << name << ": " << op->getName() << " is not a valid ownable property";
    }
    return oss.str();
}
string Player::unMortgage(string property) {
    OwnableProperty* op = dynamic_cast<OwnableProperty*>(board.stringToProperty(property));
    AcademicBuilding* academic = dynamic_cast<AcademicBuilding*>(op);
    ostringstream oss;
    if (op && ownsProperty(op)) {
        if (!op->isMortgaged()) {
            oss << name << ": " << op->getName() << " is not mortgaged";
        }
        else {
            if (balance < op->getPrice() * 0.6) {
                oss << name << ": Can't afford the" << op->getPrice() * 0.6 << "to unmortgage " << op->getName() << " (have $" << balance << ")";
            }
            else {
                op->setMortgage(false);
                balance -= op->getPrice() * 0.6;
                oss << name << ": Successfully unmortgaged " << op->getName() << " for $" << op->getPrice() * 0.6;
            }
        }
    }
    else if (!ownsProperty(op)){
        oss << name << ": You do not own" << op->getName();
    }
    else {
        oss << name << ": " << op->getName() << " is not a valid ownable property";
    }
    return oss.str();
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
