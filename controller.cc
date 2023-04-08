#include "controller.h"
#include "player.h"
#include "enumerations.h"

#include <vector>
#include <iostream>
#include <string>

using std::vector;
using std::cout;
using std::endl;
using std::string;
using std::cin;

Player& Controller::playMonopoly() {
    players.clear(); //<---- probably not necessary
    board.init("default.data"); //<---- filename containing data for all squares

    int num_players; //Get from cin
    cout << "Enter the number of players: ";
    cin >> num_players;

    //Initialize players vector
    for (size_t i = 0; i < num_players; i++)
    {
        //Get these fields from cin. 
        string player_name;
        char token;

        int player_number = i + 1;
        cout << "Enter player " << player_number << " name: ";

        cin >> player_name;
        cout << "Enter token for " << player_name << ": ";
        cin >> token;

        players.push_back(Player(player_name, token, board));
    }

    //--------------------------------------
    //Game starts being actually played here
    current_player_id = 0;
    while (true) {
        //Each loop is a players turn
        Player& p = players[current_player_id];
        cout << "Player " << p.getName() << "'s turn" << endl;

        string cmd;
        cin >> cmd;
        //Calling commands before rolling
        //After player calls "roll"
        do {
            while (true) {
                if (command(cmd, p)) {
                    continue;
                }
                else if (cmd == "roll") {
                    game_over = move(p);
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
            cout << p.getName() << ": Rolled doubles initially, so must roll again" << endl;
        } while (dice.isDoubles());

        if (game_over) {
            //Winner Winner Chicken Dinner
            return players[current_player_id];
        }

        //Player has completely finished moving now.
        while (true) {
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
        }
    }
}


void Controller::nextTurn() {
    // when user inputs "next", this "nextTurn" function is called
    ++current_player_id;
    if (current_player_id >= players.size()) {
        current_player_id = 0;
    }
}

bool Controller::command(string cmd, Player& p) {
    bool isvalidtrade = false;
    string cmd;
    getline(cin, cmd);
    cin >> cmd;
    if (cmd == "trade") {
        string name, give, receive;
        cin >> name;
        cin >> give;
        cin >> receive;
        
        string message = p.offerTrade(name, give, receive);
        cout << message << endl;
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
        //else if (res.action == Action::ImproveProperty) {
        string theproperty, theimprovement;
        cin >> theproperty >> theimprovement;
        if (theimprovement == "buy" || theimprovement == "sell") {
            string message = p.improve(theproperty, theimprovement);
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
        int roll = dice.roll();
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
        }
    }
    else if (res.action == Action::CantPayTuition) {
        while (true) {
            string choice;
            cin >> choice;
            if (choice == "pay") {
                // MoveResponse res = p.getCurrentSquare()->actionOnLand(p);
                ChoiceResponse cr = p.payTuition();
                cout << cr.context << endl;
                if (cr.is_valid) {
                    break;
                }
                else {
                    continue;
                }
            } else if (choice == "bankruptcy") {
                cout << p.declareBankruptcy() << endl;
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
        }
    }
    else if (res.action == Action::TuitionChoice) {
        while (true) {
            string choice;
            cin >> choice;
            int net_worth = p.getNetWorth();
            int min_cost = std::min(300,net_worth/10);
            if (choice == "flat") {
                int net_worth = p.getNetWorth();
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
                    cout << p.declareBankruptcy() << endl;
                    players.erase(players.begin() + current_player_id);
                    if (players.size() == 1) {
                        return true;
                    }
                }
            }
            else {
                cout << p.getName() << ": Invalid command" << endl;
            }
        }
    }
    return false;
}

void Controller::commenceAuction(Player& p, int current_player_id, OwnableProperty* being_auctioned) {
    if (being_auctioned = nullptr) being_auctioned = dynamic_cast<OwnableProperty*>(p.getCurrentSquare());
    int turn = current_player_id+1;
    int current_price = 0;
    cout << "Auction started for " << being_auctioned->getName() << "(value $" << being_auctioned->getPrice() << ")" << endl; 
    cout << "Bidding starts at $0 with " << players[turn] << endl;
    vector<bool> withdrawn(players.size(),false);
    for (int i = 0; i < players.size(); ++i) {
        int count = 0;
        for (auto player: withdrawn) {
            if (player == true) {
                ++count;
            }
        }
        if (count >= 2) {
            //Auction continues...
            if (!withdrawn[i]) {
                cout << players[i].getName() << ": Options are {raise}/{withdraw}" << endl;
                while (true) {
                    string choice;
                    cin >> choice;
                    if (choice == "raise") {
                        int suggested_price = current_price+=20;
                        ChoiceResponse res = players[i].offerBid(suggested_price);
                        cout << res.context << endl;
                        if (res.is_valid) {
                            current_price+= suggested_price;
                            break;
                        }
                        else {
                            continue;
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



    //for (auto receiveproperty : current_player->getOwnedProperties()) {
      //  if (receiveproperty->getName() == give) {
       //     owns_property = true;
       //     break;
       // }
    //}


   // if (!owns_property) {
   //     cout << "Ivalid, you do not own the property " << give << "." << endl;
    //    continue;
   // }
    
    //for (auto receiveproperty : current_player->getOwnedProperties()) {
       // if (receiveproperty->getName() == give) {
        //    has_improvement = true;
        //    break;
        //}
    //}


