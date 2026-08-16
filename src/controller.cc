#include "controller.h"

#include <vector>
#include <iostream>
#include <string>
#include <sstream>

using std::vector;
using std::cout;
using std::endl;
using std::string;
using std::cin;
using std::cerr;
using std::ifstream;
using std::ofstream;
using std::ostringstream;
using std::istringstream;


Player& Controller::playMonopoly() {
    players.clear(); //<---- probably not necessary
    // board.init("default.data"); //<---- filename containing data for all squares
    board.init(&td,"data/default.data"); //<---- filename containing data for all squares
    td.init(board);
    
    int num_players = 0; //Get from cin

    if (is_loaded) {
        #ifdef DEBUG
        cout << "Inside is_loaded";
        #endif
        load(loaded_file);
    } else {
        while(num_players < 2 || num_players > 6) {
            cout << "Enter the number of players: ";
            cin >> num_players;
            if (!cin) {
                cin.clear();
                cin.ignore(1000000,'\n');
            }
            if(num_players < 2 || num_players > 6) cout << "Please enter the number of players between 2 to 6." << endl;
        }
        //Initialize players vector
        for (int i = 0; i < num_players; i++) {
            //Get these fields from cin. 
            string player_name;
            char token;
            bool first_try = true;
            do {
                if (first_try) {
                    first_try = false;
                }
                else {
                    cout << "This name or token is already in use by another player" << endl;
                }

                int player_number = i + 1;
                cout << "Enter player " << player_number << " name: ";

                cin >> player_name;
                while (true) {
                    cout << "Enter token for " << player_name << ": ";
                    cin >> token;
                    if (token != 'G' && token != 'B' && token != 'D' && token != 'P' && token != 'S'&& token != '$'&& token != 'L' && token != 'T') {
                        cout << "Invalid token, must be one of G, B, D, P, S, $, L, T" << endl;
                    }
                    else {
                        break;
                    }
                }
            } while (!validPlayer(player_name,token));
            players.push_back(Player(player_name, token, &board));
            players[i].attach(&td);
            td.indexToken(token,i);
            players[i].notifyView();
        }
    }
    cout << td << endl;
    //--------------------------------------
    //Game starts being actually played here
    current_player_id = 0;
    while (true) {
        //Each loop is a players turn
        Player& p = players[current_player_id];
        cout << "Player " << p.getName() << "'s turn" << endl;
        bool went_bankrupt = false;
        bool third = true;
        if (p.inLine()) {
            cout << p.getName() << ": In DC Tims Line (turn " << p.getNumTurnsInDCTims() << ")" << endl;
            cout << p.getName() << ": choices: {rollfordoubles}/{userollup}/{pay} " << endl;
        }
        do {
            while (true) {
                string cmd;
                cin >> cmd;
                // if (is_loaded) {
                //     went_bankrupt = move(p);
                // }
                if (command(cmd, p)) { // this takes in the commands after roll
                    continue;
                }
                else if (cmd == "roll") {
                    if (p.isInTimsLine()) {
                        cout << p.getName() << ": Can't roll while in DC Tims Line" << endl;
                        cout << p.getName() << ": choices: {rollfordoubles}/{userollup}/{pay} " << endl;
                        continue;
                    }
                    int d1,d2;
                    string d;
                    getline(cin,d);
                    if ((testing_mode) && d != "") {
                        istringstream iss {d};
                        do {
                            iss >> d1 >> d2;
                            dice.setDice(d1,d2);
                        } while (!iss);
                        went_bankrupt = move(p, d1+d2);
                    } // else if (is_loaded) {
                    //     went_bankrupt = move(p);
                    // }
                    else {
                        went_bankrupt = move(p);
                    }
                    break;
                }
                else if (cmd == "next") {
                    if (p.isInTimsLine()) {
                        cout << p.getName() << ": Must resolve current action before ending turn (resolve with {pay}, {userollup}, or {rollfordoubles} )" << endl;
                    }
                    else {
                        cout << p.getName() << ": Can't end turn before rolling" << endl;
                    }
                }
                else if ((p.isInTimsLine()) && (cmd == "pay" || cmd == "userollup" )) {
                    bool use_rollup = false;
                    if (cmd == "userollup") use_rollup = true;
                    ChoiceResponse cr = p.payOutOfDCLine(use_rollup);
                    cout << cr.context << endl;
                    if (cr.is_valid) {
                        if (p.getNumTurnsInDCTims() >= 3) {
                            went_bankrupt = move(p,dice.getFaceValues().first + dice.getFaceValues().second);
                        }
                        else {
                            went_bankrupt = move(p);
                        }
                        break;
                    }   
                }
                else if ((p.isInTimsLine()) && cmd == "rollfordoubles" && (p.getNumTurnsInDCTims() < 3 || third)) {
                    int roll = dice.roll();
                    if (dice.isDoubles()) {
                        cout << p.getName() << ": Successfully rolled doubles" << endl;
                        went_bankrupt = move(p, roll);
                    }
                    else if (p.getNumTurnsInDCTims() >= 3) {
                        cout << p.getName() << ": Failed to roll doubles for third turn, must pay to leave now" << endl;
                        third = false;
                        continue;
                    }
                    else {
                        cout << p.getName() << ": Failed to roll doubles"<< endl;
                        break;
                    }
                }
                else if (cmd == "bankruptcy") {
                    if (p.getBalance() >= 50) {
                        cout << p.getName() << ": Can't declare bankruptcy, have sufficent funds to pay $50 bail" << endl;
                    }
                    else {
                        bankruptcyOccurence(p);
                        went_bankrupt = true;
                        
                    }
                }
                else if (testing_mode && cmd == "teleport") {
                    int loc;
                    cin >> loc;
                    p.teleport(loc);
                    went_bankrupt = move(p,0);
                    break;
                }
                else {
                    cout << p.getName() << ": Invalid command" << endl;
                }
            }
            if (went_bankrupt) {
                if (players.size() == 1) {
                    Player& winner = players[current_player_id];
                    cout << winner.getName() << " won the game!" << endl;
                    return winner;
                }
                else {
                    goto bankrupt;
                }
            }
            if (dice.isDoubles() && !dice.threeDoubles() && !p.isInTimsLine()) cout << p.getName() << ": Rolled doubles, so must roll again" << endl;
        } while (dice.isDoubles() && !dice.threeDoubles() && !p.isInTimsLine());

        
        //Player has completely finished moving now.
        while (true) {
            string cmd;
            cin >> cmd;
            
            if (command(cmd, p)) {
                continue;
            }
            else if (cmd == "roll") {
                cout << p.getName() << ": Already rolled this turn" << endl;
            }
            else if (cmd == "next") {
                nextTurn();
                break;
            }
            else {
                cout << p.getName() << ": Invalid command" << endl;
            }
            
        }
        bankrupt:;
    }
}


void Controller::nextTurn() {
    // when user inputs "next", this "nextTurn" function is called
    ++current_player_id;
    size_t temp = current_player_id;
    if (temp >= players.size()) {
        current_player_id = 0;
    }
}

bool Controller::command(string cmd, Player& p) {
    p.notifyView();
    cout << td << endl;
    if (cmd == "trade") {
        string name, give, receive;
        cin >> name;
        cin >> give;
        cin >> receive;
        Player* p_ptr = nullptr;
        for (Player& player: players) {
            //Invariant, there will only be one
            if (player.getName() == name) {
                p_ptr = &player;
                break;
            }
        }
        if (p_ptr != nullptr) {
            if (p_ptr->getName() == p.getName()) {
                cout << name << ": Can't trade yourself!" << endl;
            }
            else {
                Trade cr = p.offerTrade(*p_ptr, give, receive);
                cout << cr.context << endl;
                if (cr.is_valid) {
                    while (true) {
                        cout << name << ", would you like to accept the following offer?" << endl;
                        cout << "GIVE: " << receive << endl;
                        cout << "RECEIVE: " << give << endl;
                        cout << "Choices are {accept}/{decline}" << endl;
                        string choice;
                        cin >> choice;
                        
                        if (choice == "accept") {
                            cout << p_ptr->acceptOffer(p,cr) << endl;
                            break;
                        }
                        else if (choice == "decline") {
                            cout << p.getName() << ": " << name << " declined the trade" << endl;
                            break;
                        }
                        else {
                            cout << name << ": Must resolve current trade(resolve with {accept}/{decline})" << endl;
                        }
                    }
                }
            }
            
        }
        else {
            cout << p.getName() << ": There is no player by the name of \"" << name << "\"" << endl;
        }

        
    }
    else if (cmd == "mortgage") {
        string property;
        cin >> property;
        
        string message = p.Mortgage(property);
        cout << message << endl;
    }
    else if (cmd == "unmortgage") {
        string property;
        cin >> property;

        string res = p.unMortgage(property); 
        cout << res << endl;
    }
    else if (cmd == "improve") {
        string theproperty, theimprovement;
        cin >> theproperty >> theimprovement;
        if (theimprovement == "buy") {
            string message = p.improve(theproperty, true);
            cout << message << endl;
        }
        else if (theimprovement == "sell") {
            string message = p.improve(theproperty, false);
            cout << message << endl;
        } else cout << p.getName() << ": Invalid improve, must use {buy}/{sell}" << endl;
        cout << td << endl;
    }
    else if (cmd == "assets") {
        cout << p << endl;
    }
    else if (cmd == "all") {
        for (auto player : players) {
            cout << player << endl;
        }
    }
    else if (cmd == "save") {
        //To implement
        string filename;
        cin >> filename;
        save(filename);
    }
    else if (testing_mode && cmd == "setdosh") {
        int loc;
        cin >> loc;
        p.setBalance(loc);
    }
    else return false;
    return true;
}

bool Controller::move(Player& p, int roll) {
    if (roll == -1) {
        roll = dice.roll();
    }
    cout << p.getName() << ": Rolled " << dice.getFaceValues().first << " and " << dice.getFaceValues().second << endl;
    if (dice.threeDoubles()) {
        p.goToTims();
        cout << p.getName() << ": Sent to DC Tims Line for rolling 3 doubles" << endl;
        return false;
    }
    MoveResponse res = p.move(roll);
    p.notifyView();
    cout << td << endl;
    cout << res.context << endl;
    if (res.action == Action::BuyOrAuction) {
        while (true) {
            string choice;
            cin >> choice;
            if (choice == "buy") {
                ChoiceResponse cr = p.buy();
                cout << cr.context << endl;
                if (cr.is_valid) break;
                else continue;
            } else if (choice == "auction") {
                commenceAuction(p, current_player_id);
                break;
            }
            else if (command(choice, p)) {
                continue;
            }
            else if (choice == "next") {
                cout << p.getName() << ": Must resolve current action before ending turn (resolve with {buy}/{auction})" << endl;
            }
            else {
                cout << p.getName() << ": Invalid command" << endl;
            }
            
        }
    }
    else if (res.action == Action::CantPayTuition) {
        while (true) {
            string choice;
            cin >> choice;
            if (choice == "pay") {
                ChoiceResponse cr = p.settleDebts();
                cout << cr.context << endl;
                if (cr.is_valid) break;
            } else if (choice == "bankruptcy") {
                bankruptcyOccurence(p);
                return true;
            }
            else if (command(choice, p)) {
                continue;
            }
            else if (choice == "next") {
                cout << p.getName() << ": Must resolve current action before ending turn (resolve with {pay}/{bankruptcy})" << endl;
            }
            else {
                cout << p.getName() << ": Invalid command" << endl;
            }
            
        }
    }
    else if (res.action == Action::TuitionChoice) {
        while (true) {
            string choice;
            cin >> choice;
            int net_worth = p.getNetWorth();
            int min_cost = std::min(300,net_worth/10);
            if (choice == "flat") {
                ChoiceResponse cr = p.payTuition(300);
                cout << cr.context << endl;
                if (cr.is_valid) break;
                else continue;
            } else if (choice == "percentage") {
                ChoiceResponse cr = p.payTuition(net_worth/10);
                cout << cr.context << endl;
                if (cr.is_valid) break;
                else continue;
            }
            else if (choice == "assets" || choice == "all") {
                cout << p.getName() << ": Can't check assets while paying tuition" << endl;
            }
            else if (command(choice, p)) {
                continue;
            }
            else if (choice == "next") {
                cout << p.getName() << ": Must resolve current action before ending turn (resolve with {flat}/{percentage}/{bankruptcy})" << endl;
            }
            else if (choice == "bankruptcy") {
                if (p.getBalance() >= min_cost) {
                    cout << p.getName() << ": Can't declare bankruptcy, have sufficent funds to pay minimum tuition of $" << min_cost << endl;
                }
                else {
                    bankruptcyOccurence(p);
                    return true;
                }
            }
            else {
                cout << p.getName() << ": Invalid command" << endl;
            }
            
        }
    }
    return false;
}

void Controller::load(string filename) {
    ifstream f {filename};
    string str;
    getline(f, str);
    istringstream iss_t {str};
    int n;
    iss_t >> n;
    // set them to players.size
    //players.size() = n;

    // run a for loop size times to get the player info
    for (int i = 0; i < n; ++i) {
        string s;
        getline(f, s);
        istringstream iss {s};
        string name;
        iss >> name;
        char token;
        iss >> token;
        int cups;
        iss >> cups;
        int money;
        iss >> money;
        int pos;
        iss >> pos;
        // Player p {na}
        int on_DCTL, num;
        iss >> on_DCTL;
        if (iss) {
            if (on_DCTL) {
                iss >> num;
            } 
            // else {
            //     // num = 0;
            // }
        } else {
            on_DCTL = 0;
            num = 0;
        }
        bool b = on_DCTL;
        players.push_back({name, token, &board, money, cups, pos, b, num});
        players[i].attach(&td);
        td.indexToken(token,i);
        players[i].notifyView();
    }
    // you loop through 40 times to update the status of the property
    // we will have all the properties set up by default
    for (int i = 0; i < 40; ++i) {
            Square* sq = board.getSquare(i);
            OwnableProperty* op = dynamic_cast<OwnableProperty*>(sq);
            if (op) {
                string s;
                getline(f, s);
                istringstream iss {s};
                string property, owner;
                iss >> property >> owner;
                for(auto & player: players) {
                    if (owner == player.getName()) {
                        op->setOwner(&player);
                        player.getOwnedProperties().push_back(op);
                    }
                }
                // if a owner is a person, set it to the name
                // so if owner is a bank, then set owner as a bank or do nothing
                // if (owner != "BANK") op->getOwner()->setName(owner);
            }
        //}
    }
    cout << "File loaded successfully, you may continue playing." << endl;
}

void Controller::commenceAuction(Player& p, int current_player_id, OwnableProperty* being_auctioned) {
    if (being_auctioned == nullptr) being_auctioned = dynamic_cast<OwnableProperty*>(p.getCurrentSquare());
    int turn = 0;
    int current_price = 0;
    cout << "Auction started for " << being_auctioned->getName() << " (value $" << being_auctioned->getPrice() << ")" << endl; 
    cout << "Bidding starts at $0 with " << players[turn].getName() << endl;
    vector<bool> withdrawn(players.size(),false);
    int counter = players.size();
    int count = players.size();
    while (true) {
        for (int i = 0; i < counter; ++i) {
            if (!withdrawn[i]) {
                //Auction continues...
                if (count >= 2) {
                    cout << players[i].getName() << ": Choices are {raise}/{withdraw}" << endl;
                    while (true) {
                        string choice;
                        cin >> choice;
                        if (choice == "raise") {
                            int suggested_price = current_price + 20;
                            if (players[i].getBalance() < suggested_price) {
                                cout << players[i].getName() << ": Invalid. Current raise would bring price to $" << suggested_price << ", but you only have $" << players[i].getBalance() << endl;
                                continue;
                            }
                            else {
                                cout << players[i].getName() << ": Successfully raised to $" << suggested_price << endl;
                                current_price = suggested_price;
                                break;
                            }
                        }
                        else if (choice == "withdraw") {
                            count = count - 1;
                            cout << players[i].getName() << ": Withdrew from auction, " << count << " bidders remain" << endl;
                            withdrawn[i] = true;
                            break;
                        }
                        else if (command(choice,players[i])) {
                            continue;
                        }
                        else {
                            cout << players[i].getName() << ": Invalid Command." << endl;
                        }
                    }
                }
                else {
                    cout << players[i].getName() << ": Won the auction for " << being_auctioned->getName() << " with a bid of $" << current_price << endl;
                    players[i].wonAuction(being_auctioned, current_price);
                return;
            }
            }
        }
    }
    

}

bool Controller::validPlayer(string name, char token) {
    for (auto player: players) {
        if (player.getName() == name) return false;
        if (player.getToken() == token) return false;
    }
    if (name == "BANK") return false;
    return true;
}

void Controller::save(string filename) {
    ofstream ofs (filename);
    if (!ofs) {
        cout << "Error: Cannot open the file " << filename << " for writing.\n";
        return;
    }
    if (ofs.is_open()) {
        ofs << players.size() << endl;
    }
    for (auto player: players) {
        ofs << player.getName() << ' ' << player.getToken() << ' ' << player.getCups() << ' '
            << player.getBalance() << ' ' << player.getPosition();
        if (player.getPosition() == DC_TIMS_LINE) {
            ofs << ' ' << player.isInTimsLine();
            if (player.isInTimsLine()) {
                ofs << ' ' << player.getNumTurnsInDCTims();
            }
        }
        ofs << endl;
    }
    for (int i = 0; i < 40; ++i) {
        Square* sq = board.getSquare(i);
        OwnableProperty* op = dynamic_cast<OwnableProperty *>(sq);
        if (op) {
            ofs << sq->getName() << ' ';
            if (op->getOwner()) ofs << op->getOwner()->getName() << ' ';
            else ofs << "BANK" << ' ';
            AcademicBuilding* ab = dynamic_cast<AcademicBuilding *>(sq);
            if (ab) {
                ofs << ab->getNumberOfImprovements() << endl;
            } else ofs << 0 << endl;
        }
    }
    cout << "File " << filename << " saved successfully." << endl;
}

void Controller::setTestingMode(bool s) {
    testing_mode = s;
}

void Controller::setIsLoaded(bool b) {
    is_loaded = b;
}

void Controller::setLoadedFile(string file) {
    loaded_file = file;
}
void Controller::bankruptcyOccurence(Player& p) {
    BankruptcyResponse br = p.declareBankruptcy();
    p.notifyView();
    cout << br.context << endl;
    players.erase(players.begin() + current_player_id);
    Player* r = br.receiving;
    if (r == nullptr) {
        for (auto property: br.properties) {
            commenceAuction(p, current_player_id, property);
        }
    }
    else {
        for (auto property: br.properties) {
            if (property->isMortgaged()) {
                cout << r->getName() << ": You received the mortgaged property " << property->getName() << ", you can unmortgage now for 60% cost or pay 10% and keep it mortgaged" << endl;
                cout << r->getName() << ": choices: {unmortgage}/{keep}" << endl;
                while (true) {
                    string choice;
                    cin >> choice;
                    if (choice == "unmortgage") {
                        ChoiceResponse cr = r->mortgageChoice(property,true);
                        cout << cr.context << endl;
                        if (cr.is_valid) break;
                        else continue;
                    }
                    else if (choice == "keep") {
                        ChoiceResponse cr = r->mortgageChoice(property,false);
                        cout << cr.context << endl;
                        if (cr.is_valid) break;
                        else continue;
                    }
                    else if (command(choice, *r)) { // this takes in the commands after roll
                        continue;
                    }
                    else if (choice == "next") {
                        cout << p.getName() << ": Must resolve current action before ending turn (resolve with {unmortgage}/{keep})" << endl;
                    }
                    else {
                        cout << r->getName() << ": Invalid command" << endl;
                    }
                }
            }
        }
    }
}
