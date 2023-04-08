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
    receiving->owned_properties.push_back(property);
    for (int i = 0; i < owned_properties.size(); ++i) {
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
        oss << name << ": " << property << " is not a valid ownable property";
    }
    return oss.str();
}
string Player::unMortgage(string property) {
    OwnableProperty* op = dynamic_cast<OwnableProperty*>(board.stringToProperty(property));
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
        oss << name << ": " << property << " is not a valid ownable property";
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

Trade Player::offerTrade(Player& send_to, string give, string receive) {
    //assert name, give, receive
    int g, r; // for give (g), receive (r)
    istringstream iss_g {give};
    istringstream iss_r {receive};
    ostringstream oss;
    iss_g >> g;
    iss_r >> r;

    int gm = 0;
    int rm = 0;
    OwnableProperty* gp = nullptr;
    OwnableProperty* rp = nullptr;
    int option = -1;

    bool success = false;
    if (iss_g && iss_r) { // means both give and receive are integers
        oss << name << ": Can't offer money in return for money";
    } else if (iss_g && !iss_r) { // means give is an int and receive is a string
        OwnableProperty* p = dynamic_cast<OwnableProperty*>(board.stringToProperty(receive));
        AcademicBuilding* academic = dynamic_cast<AcademicBuilding*>(p);
        if (p) {
            if (!send_to.ownsProperty(p)) {
                oss << name << ": Trying to ask for a property " << send_to.name << " doesn't own";
            }
            if (balance < g) {
                oss << name << ": Trying to give away more money then you have (have $" << balance << ")";
            }
            else {
                if (academic && academic->getNumberOfImprovements() > 0) {
                    oss << name << ": " << academic->getName() << " can't be traded because it has " << academic->getNumberOfImprovements() << " improvements";
                } 
                else {
                    oss << name << ": Successfully sent offer";
                    success = true;
                    rp = p;
                    gm = g;
                    option = 1;
                }
            }
        }
        else {
            oss << name << ": Trying to ask for an invalid property";
        }
        
    } else if (!iss_g && iss_r) { // means give is a string and receive is an int
        OwnableProperty* p = dynamic_cast<OwnableProperty*>(board.stringToProperty(give));
        AcademicBuilding* academic = dynamic_cast<AcademicBuilding*>(p);
        if (p) {
            if (!ownsProperty(p)) {
                oss << name << ": Trying to give away a property you don't own";
            }
            if (send_to.balance < r) {
                oss << name << ": Trying to ask for more money then " << send_to.name << " has (has $" << send_to.balance << ")";
            }
            else {
                if (academic && academic->getNumberOfImprovements() > 0) {
                    oss << name << ": " << academic->getName() << " can't be traded because it has " << academic->getNumberOfImprovements() << " improvements";
                } 
                else {
                    oss << name << ": Successfully sent offer";
                    success = true;
                    gp = p;
                    rm = r;
                    option = 2;
                }
            }
        }
        else {
            oss << name << ": Trying to give away invalid property";
        }
    } else { // means both give and receive are strings
        OwnableProperty* p = dynamic_cast<OwnableProperty*>(board.stringToProperty(give));
        OwnableProperty* p2 = dynamic_cast<OwnableProperty*>(board.stringToProperty(receive));
        AcademicBuilding* academic = dynamic_cast<AcademicBuilding*>(p);
        AcademicBuilding* academic2 = dynamic_cast<AcademicBuilding*>(p2);
        
        if (p && p2) {
            if (!ownsProperty(p)) {
                oss << name << ": Trying to give away a property you don't own";
            }
            if (!send_to.ownsProperty(p2)) {
                oss << name << ": Trying to ask for a property " << send_to.name << " doesn't own";
            }
            else {
                if (academic && academic->getNumberOfImprovements() > 0) {
                    oss << name << ": " << academic->getName() << " can't be traded because it has " << academic->getNumberOfImprovements() << " improvements";
                } 
                else if (academic && academic->getNumberOfImprovements() > 0) {
                    oss << name << ": " << academic2->getName() << " can't be traded because it has " << academic2->getNumberOfImprovements() << " improvements";
                }          
                else {
                    oss << name << ": Successfully sent offer";
                    success = true;
                    gp = p2;
                    rp = p;
                    option = 3;
                }
            }
        }
        else {
            oss << name << ": Trying to trade an invalid property";
        }
    }
    return {success,oss.str(),gm,rm,gp,rp,option};
}

string Player::acceptOffer(Player& from, Trade t) {
    ostringstream oss;
    if (t.option == 1) {
        OwnableProperty* give = t.receive_property;
        int receive = t.give_money;
        transferProperty(give,&from);
        from.balance -= receive;
        balance += receive;
        oss << from.name << ": Successfully traded " << give->getName() << " to " << name << " for " << receive;

    }
    else if (t.option == 2) {
        int give = t.receive_money;
        OwnableProperty* receive = t.give_property;
        from.transferProperty(receive,this);
        from.balance += give;
        balance -= give;
        oss << from.name << ": Successfully traded " << give << " to " << name << " for " << receive->getName();
    }
    else if (t.option) {
        OwnableProperty* give = t.receive_property;
        OwnableProperty* receive = t.give_property;
        from.transferProperty(receive,this);
        transferProperty(give,&from);
        oss << from.name << ": Successfully traded " << give->getName() << " to " << name << " for " << receive->getName();
    }
    else if (t.option == -1) {
        #ifdef DEBUG
            cout << "SOMEHOW AN INVALID TRADE WAS ACCEPTED!!" << endl;
        #endif
    }
    return oss.str();
}

string Player::improve(string property, bool buy) {
    // check for monopoly formed and enough balance to improve a property
    ostringstream oss;
    AcademicBuilding* academic = dynamic_cast<AcademicBuilding*>(board.stringToProperty(property));
    if (academic) {
        if (ownsProperty(academic)) {
            if (buy) {
                int imp_cost = academic->getImprovementCost();
                Monopoly set = academic->getSet();
                if (ownsMonopoly(set)) {
                    if (balance < imp_cost) {
                        oss << name << ": Can't afford $" << imp_cost << " to improve " << property << " (have $" << balance << ")";
                    }
                    else {
                        oss << name << ": Successfully bought an improvement on " << property << " for $" << imp_cost;
                    }
                }
                else {
                    oss << name << ": Can't improve " << property << " because it is not part of a monopoly";
                }

            }
            else {
                int num_improvements = academic->getNumberOfImprovements();
                if (num_improvements > 0) {
                    oss << name << ": " << academic->getName() << " has no improvements to sell";
                }
                else {
                    int sell_cost = academic->getImprovementCost() * 0.5;
                    oss << name << ": Successfully sold an improvement in " << academic->getName() << " for $" << sell_cost;
                    balance += sell_cost;
                }
            }
        }   
        else {
            oss << name << ": You do not own" << academic->getName();
        }
    }
    else {
        oss << name << ": " << property << " is not a valid ownable property";
    }
    
}
