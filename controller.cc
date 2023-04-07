#include "controller.h"
#include "player.h"
#include <vector>
#include <iostream>
#include <string>

using std::vector;
using std::cout;
using std::endl;
using std::string;
using std::cin;

void Controller::playMonopoly() {
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
        //int roll = rollDice();
        MoveResponse res = p.move(rollDice());

        if (res.action == Action::BuyProperty) {
            cout << "You landed on an unowned property, " << res.sq->getName() << ", that costs " << res.sq->getPrice() << "." << endl;
            cout << "Do you want to buy it? (yes/no): ";
            string choice;
            cin >> choice;
            if (choice == "yes") {
                p.buyProperty();
            }
        }
        else if (res.action == Action::GoToTims) {
            //cout << "You have been sent to DC Tims Line!" << endl;
            p.goToTims();
            //nextTurn();
        }
        else if (res.action == Action::DeclareBankruptcy) {
            cout << "You have declared bankruptcy!" << endl;
            string message = p.declareBankruptcy();
            cout << message << endl;
            // removing the bankrupt player from the game
            players.erase(players.begin() + current_player_id);
            if (players.size() == 1) {
                // this is when 1 player is left (when the game is over)
                break;
            }
            MoveResponse bankruptcyResponse{Action::DeclareBankruptcy, message};
            //nextTurn();
            continue;
        }

        cout << "Player " << p.getName() << "'s turn" << endl;
        while (true) {
            bool isvalidtrade = false;
            string cmd;
            getline(cin, cmd);
            cin >> cmd;
            if (cmd == "next") {
            nextTurn();
            break;
            }
            if (cmd == "trade") {
            string name, give, receive;
            cin >> name;
            cin >> give;
            cin >> receive;
            string message = p.offerTrade(name, give, receive);
            cout << message << endl;
            }
            if (cmd == "mortgage") {
            string property;
            cin >> property;
            string message = p.Mortgage(property);
            cout << message << endl;
            }
            if (cmd == "unmortgage") {
                string property;
                cin >> property;
                string res = current_player->unMortgage(property);
                cout << res << endl;
            }
        }

            }
            //This loop covers the cmd menu, such as trade, mortage, save.
            //Keep looping until 'next' command
            //At some point...
            if (cmd == "next") {
                nextTurn();
                break;
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



    for (auto receiveproperty : current_player->getOwnedProperties()) {
        if (receiveproperty->getName() == give) {
            owns_property = true;
            break;
        }
    }


    if (!owns_property) {
        cout << "Ivalid, you do not own the property " << give << "." << endl;
        continue;
    }
    
    for (auto receiveproperty : current_player->getOwnedProperties()) {
        if (receiveproperty->getName() == give) {
            has_improvement = true;
            break;
        }
    }

//receiveproperty->getNumImprovements() > 0