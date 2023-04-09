#include "controller.h"

#include <vector>
#include <iostream>
#include <string>

using std::vector;
using std::cout;
using std::endl;
using std::string;
using std::cin;
using std::cerr;

Player& Controller::playMonopoly() {
    players.clear(); //<---- probably not necessary
    board.init("default.data"); //<---- filename containing data for all squares

    int num_players = 0; //Get from cin

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
    for (int i = 0; i < num_players; i++)
    {
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
            cout << "Enter token for " << player_name << ": ";
            cin >> token;
        } while (!validPlayer(player_name,token));

        players.push_back(Player(player_name, token, &board));
    }

    //--------------------------------------
    //Game starts being actually played here
    current_player_id = 0;
    while (true) {
        //Each loop is a players turn
        Player& p = players[current_player_id];
        cout << "Player " << p.getName() << "'s turn" << endl;

        do {
            while (true) {
                string cmd;
                cin >> cmd;
                if (command(cmd, p)) {
                    continue;
                }
                else if (cmd == "roll") {
                    game_over = move(p);
                    if (game_over) {
                        //Winner Winner Chicken Dinner
                        return players[current_player_id];
                    }
                    break;
                }
                else if (cmd == "next") {
                    cout << p.getName() << ": Can't end turn before rolling" << endl;
                }
                else {
                    cout << p.getName() << ": Invalid command" << endl;
                }

                if (dice.threeDoubles()) {
                    cout << p.goToTims() << endl;
                    break;
                }
            }
            if (dice.isDoubles()) cout << p.getName() << ": Rolled doubles initially, so must roll again" << endl;
        } while (dice.isDoubles());

        cout << endl;
        //Player has completely finished moving now.
        while (true) {
            string cmd;
            cin >> cmd;
            if (command(cmd, p)) {
                continue;
            }
            else if (cmd == "roll") {
                cout << p.getName() << ": Already moved this turn" << endl;
            }
            else if (cmd == "next") {
                nextTurn();
                break;
            }
            else {
                cout << p.getName() << ": Invalid command" << endl;
            }
            cout << endl;
        }
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
    if (cmd == "trade") {
        string name, give, receive;
        cin >> name;
        cin >> give;
        cin >> receive;
        Player* p_ptr = nullptr;
        for (auto player: players) {
            //Invariant, there will only be one
            if (player.getName() == name) {
                p_ptr = &player;
            }
        }
        if (p_ptr) {
            Trade cr = p.offerTrade(*p_ptr, give, receive);
            cout << cr.context << endl;
            if (cr.is_valid) {
                while (true) {
                    cout << name << ", would you like to accept the following offer: " << endl;
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
        if (theimprovement == "buy" || theimprovement == "sell") {
            string message = p.improve(theproperty, true);
            cout << message << endl;
        }
        else if (theimprovement == "sell") {
            string message = p.improve(theproperty, false);
            cout << message << endl;
        } else cout << p.getName() << ": Invalid improve, must use {buy}/{sell}" << endl;
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
    }
    else return false;
    return true;
}

bool Controller::move(Player& p, int roll) {
    if (roll == 0) {
        roll = dice.roll();
    }
    MoveResponse res = p.move(roll);
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
            cout << endl;
        }
    }
    else if (res.action == Action::CantPayTuition) {
        while (true) {
            string choice;
            cin >> choice;
            if (choice == "pay") {
                // MoveResponse res = p.getCurrentSquare()->actionOnLand(p);
                ChoiceResponse cr = p.settleDebts();
                cout << cr.context << endl;
                if (cr.is_valid) {
                    break;
                }
                else {
                    continue;
                }
            } else if (choice == "bankruptcy") {
                ChoiceResponse cr = p.declareBankruptcy();
                cout << cr.context << endl;
                if (cr.is_valid) {
                    for (auto property: p.getOwnedProperties()) {
                        commenceAuction(p, current_player_id, property);
                    }
                }
                players.erase(players.begin() + current_player_id);
                if (players.size() == 1) {
                    return true;
                }
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
            cout << endl;
        }
    }
    else if (res.action == Action::InJail) {
        while (true) {
            string choice;
            cin >> choice;
            if (choice == "roll") {
                int roll = dice.roll();
                if (dice.isDoubles()) {
                    bool was_winner = move(p, roll);
                    if (was_winner) return true;
                }
            } 
            else if (choice == "userollup") {
                ChoiceResponse cr = p.payOutOfJail(true);
                cout << cr.context << endl;
                if (cr.is_valid) {
                    bool was_winner = move(p);
                    if (was_winner) return true;
                }   
                else continue;
            } else if (choice == "pay") {
                ChoiceResponse cr = p.payOutOfJail(false);
                cout << cr.context << endl;
                if (cr.is_valid) {
                    bool was_winner = move(p);
                    if (was_winner) return true;
                }   
                else continue;
            }
            else if (command(choice,p)) {
                continue;
            }
            else if (choice == "next") {
                cout << p.getName() << ": Must resolve current action before ending turn (resolve with {pay}, {userollup}, or {roll} )" << endl;
            }
            else {
                cout << p.getName() << ": Invalid command" << endl;
            }
            cout << endl;
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
                    ChoiceResponse cr = p.declareBankruptcy();
                    cout << cr.context << endl;
                    if (cr.is_valid) {
                        for (auto property: p.getOwnedProperties()) {
                            commenceAuction(p, current_player_id, property);
                        }
                    }
                    players.erase(players.begin() + current_player_id);
                    if (players.size() == 1) {
                        return true;
                    }
                }
            }
            else {
                cout << p.getName() << ": Invalid command" << endl;
            }
            cout << endl;
        }
    }
    return false;
}

void Controller::commenceAuction(Player& p, int current_player_id, OwnableProperty* being_auctioned) {
    if (being_auctioned == nullptr) being_auctioned = dynamic_cast<OwnableProperty*>(p.getCurrentSquare());
    int turn = current_player_id+1;
    int current_price = 0;
    cout << "Auction started for " << being_auctioned->getName() << "(value $" << being_auctioned->getPrice() << ")" << endl; 
    cout << "Bidding starts at $0 with " << players[turn].getName() << endl;
    vector<bool> withdrawn(players.size(),false);
    int counter = players.size();
    for (int i = 0; i < counter; ++i) {
        int count = 0;
        for (auto player: withdrawn) {
            if (player == true) {
                ++count;
            }
        }
        if (count >= 2) {
            //Auction continues...
            if (!withdrawn[i]) {
                cout << players[i].getName() << ": Choices are {raise}/{withdraw}" << endl;
                while (true) {
                    string choice;
                    cin >> choice;
                    if (choice == "raise") {
                        int suggested_price = current_price+=20;
                        if (players[i].getBalance() < suggested_price) {
                            cout << players[i].getName() << ": Invalid. Current raise would bring price to $" << suggested_price << ", but you only have $" << players[i].getBalance() << endl;
                            continue;
                        }
                        else {
                            cout << players[i].getName() << ": Successfully raised to $" << suggested_price << endl;
                            current_price+= suggested_price;
                            break;
                        }
                    }
                    else if (choice == "withdraw") {
                        withdrawn[i] = true;
                        break;
                    }
                    else if (command(choice,players[i])) {
                        continue;
                    }
                    else {
                        cout << players[i].getName() << ": Invalid Command" << endl;
                    }
                }
            }
        }
        else {
            players[i].buy(being_auctioned);
        }
    }

}

bool Controller::validPlayer(string name, char token) {
    for (auto player: players) {
        if (player.getName() == name) return false;
        if (player.getToken() == token) return false;
        // if (player.getToken() != 'G' && player.getToken() != 'B' && player.getToken() != 'D' && player.getToken() != 'P' && player.getToken() != 'S'&& player.getToken() != '$'&& player.getToken() != 'L' && player.getToken() != 'T') {
        //     return false;
        // }
    }
    return true;
}
