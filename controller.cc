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
    

    //players.erase(players.begin() + current_player_id); //<---- use this after bankruptcy to remove current player
    //Successful bankruptcy should immediately go to the next players turn

    //--------------------------------------
    //Game starts being actually played here
    current_player_id = 0;
    while (true) {
        //Each loop is a players turn
        Player& p = players[current_player_id];
        cout << "Player " << p.getName() << "'s turn" << endl;
        player_bankrupted = false;

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
                    move(p);
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
        } while (dice.isDoubles());
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
        } else cout << p.getName() << ": Invalid improvement type. Enter buy or sell" << endl;
    }
    // else if (cmd == "bankrupt") {
    //     string message = players[current_player_id].declareBankruptcy();
    //     cout << message << endl;
    //     break; 
    // }
    else if (command == "all") {
        if (p.checkinTuition()) {
            cout << "You cannot use the 'all' command while deciding how to pay tuition." << endl;
        } else {
            for (int i = 0; i < numPlayers; ++i) {
                cout << "Player " << i + 1 << ":" << endl;
                players[i].displayAssets();
                cout << endl;
            }
        }
    }
}

bool Controller::move(Player& p) {
    int roll = dice.roll();
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
                //Figure out auction later
                p.auctionProperty();
            }
            else if (command(choice)) {
                continue;
            }
            else if (choice == "next") {
                cout << p.getName() << ": Must resolve current action before ending turn (resolve with {buy} or {auction})" << endl;
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
                ChoiceResponse cr = p.payDebts();
                cout << cr.context << endl;
                if (cr.is_valid) {
                    break;
                }
                else {
                    continue;
                }
            } else if (choice == "bankruptcy") {
                p.declareBankruptcy();
                players.erase(players.begin() + current_player_id);
                player_bankrupted = true; 
                if (players.size() == 1) {
                    return true;
                }
            }
            else if (command(choice, p)) {
                continue;
            }
            else if (choice == "next") {
                cout << p.getName() << ": Must resolve current action before ending turn (resolve with {pay} or {bankruptcy})" << endl;
            }
            else {
                cout << p.getName() << ": Invalid command" << endl;
            }
        }
    }
    else if (res.action == Action::InJail) {
        // while (true) {
        //     string choice;
        //     cin >> choice;
        //     if (choice == "roll") {
        //         ChoiceResponse cr = p.payDebts();
        //         cout << cr.context << endl;
        //         if (cr.is_valid) break;
        //         else continue;
        //     } else if (choice == "rollup") {
        //         p.declareBankruptcy();
        //         players.erase(players.begin() + current_player_id);
        //         if (players.size() == 1) {
        //             return p;
        //         }
        //         player_bankrupted = true; 
        //     } else if (choice == "pay") {
        //         p.declareBankruptcy();
        //         players.erase(players.begin() + current_player_id);
        //         player_bankrupted = true; 
        //         if (players.size() == 1) {
        //             return true;
        //         }
        //     }
        //     else if (command(choice,p)) {
        //         continue;
        //     }
        //     else if (choice == "next") {
        //         cout << p.getName() << ": Must resolve current action before ending turn (resolve with {pay}, {rollup}, or {roll} )" << endl;
        //     }
        //     else {
        //         cout << p.getName() << ": Invalid command" << endl;
        //     }
        // }
    }
    else if (res.action == Action::TuitionChoice) {

    }
    return false;
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


