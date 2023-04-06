#include "player.h"
#include "response.h"
#include "academicbuilding.h"
#include <sstream>

using std::ostringstream;

Player::Player(string name, char token, Board& attached_to, int bal = 0, int rur = 0, int pos = 0, bool in_jail = false, int num_turns_in_jail = 0):
name{name},token{token},board{attached_to},balance{bal},num_roll_up_rims{rur},position{pos},in_jail{false},num_turns_in_jail{num_turns_in_jail} {
    current_square = attached_to.getSquare(position);
}

MoveResponse Player::move(int num_spaces) {
    if (!(in_jail)) {
        position = (position + num_spaces)%39;
        current_square = board.getSquare(position);
        MoveResponse res = current_square->actionOnLand(*this);
        return res;
    }
    else {
        //Player has 3 choices: pay $50, roll for doubles or use a roll up the rim
        ostringstream oss;
        oss << "In Tims line (" << num_turns_in_jail << "turn(s)";
        std::string context = oss.str();
        return {Action::InJail, context};
    }
}

void Player::teleport(int square_index) {
    #ifdef DEBUG
        cout << "Invalid call to teleport with: " << square_index << endl; 
    #endif
    position = square_index;
    current_square = board.getSquare(position);
}

void Player::transferProperty(OwnableProperty* property, Player* receiving) {
    property->setOwner(receiving);

    for (int i; i < owned_properties.size(); ++i) {
        if (owned_properties[i] == property) {
            owned_properties.erase(owned_properties.begin() + i);
        }
    }
}

CommandResponse Player::declareBankruptcy() {
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
        for (auto mon: owned_monopolies) {
            if (mon.second == true) {
                receiving->owned_monopolies[mon.first] = true;
            }
        }
    }
    for (auto property: owned_properties) {
            transferProperty(property,receiving);
    }
    
    //Cleanup, 
    for (auto mon: owned_monopolies) {
        if (mon.second == true) {
            owned_monopolies[mon.first] = false;
        }
    }
    balance = 0;
    teleport(0);
    return {true, InvalidReason::NotInvalid};
}

CommandResponse Player::buyProperty() {
    OwnableProperty* ownable = dynamic_cast<OwnableProperty*>(current_square);
    int price = ownable->getPrice();
    if (balance < price) {
        return {false, InvalidReason::NotEnoughMoney};
    }
    else {
        owned_properties.push_back(ownable);
        balance = balance - price;
        AcademicBuilding* academic = dynamic_cast<AcademicBuilding*>(ownable);
        Monopoly set = academic->getSet();
        if (academic != nullptr && ownsMonopoly(set)) {
            //Not worth it? We should discuss
            owned_monopolies[set] = true;
        }
        return {true, InvalidReason::NotInvalid};
    }
}

CommandResponse Player::goToTims() {
    teleport(DC_TIMS_LINE);
    in_jail = true;
}

int Player::getBalance() {
    return balance;
}
void Player::setBalance(int new_balance) {
    balance = new_balance;
}
void Player::addBalance(int money) {
    balance += money;
}

//Can't check like this, the purpose of this function is to find the monopolies in owned_properties
bool Player::ownsMonopoly(Monopoly monopoly) { return owned_monopolies[monopoly]; }
