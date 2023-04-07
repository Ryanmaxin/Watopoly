#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <vector>
#include <map>
#include <string>

#include "enumerations.h"
#include "square.h"
#include "board.h"
#include "response.h"

using std::map;
using std::string;
using std::vector;

class Player {
    string name;
    char token;

    int position;
    int balance;
    int num_roll_up_rims;

    bool in_tims_line;
    int num_turns_in_tims_line;

    Board& board;
    Square* current_square;
    vector<OwnableProperty*> owned_properties;
    
    void transferProperty(OwnableProperty* property, Player* receiving);
    
    bool ownsMonopoly(Monopoly monopoly);
    int getNetWorth();
    public:
        Player(string name, char token, Board& attached_to, int bal = 1500, int rur = 0, int pos = 0, bool in_jail = false, int num_turns_in_jail = 0);

        MoveResponse move(int num_spaces);
        void teleport(int square_index);

        //Choices for Action::CantPayTuition
        string declareBankruptcy();
        string raiseFunds();

        //Choices for Action::BuyOrAuction
        string buy();
        string auction();

        //Choices for Action::TuitionChoice
        string payFlatTuition();
        string payPercentageTuition();

        //Choices for Action::InJail
        string useRollUp();
        string payFifty();
        string rollForDoubles();

        //Called by SLC and Go To Tims properties. Also called when player rolls doubles 3 times.
        string goToTims();

        //Regular commands
        string offerTrade(string name, string give, string receive);
        string improve(string property, string buysell);
        string Mortgage(string property);
        string unMortgage(string property);

        //Getter-Setter methods
        int getBalance();
        void setBalance(int new_balance);
        void addBalance(int money);
        //The sum of current balance + price of all owned properties + price of all owned improvements
        int getNetWorth();

        string getName();

        // buyProperty would deal with deducting the cost of the 
        // property from the player's balance, set the property's owner to the player, 
        // and add the property to the player's list of owned properties
        
        void buyProperty(Square* sq);

        // auctionProperty deals with the auction and setting it, called in controller.cc when
        // player/user decides to auction a property instead of saying "yes"
        // for buying
        void auctionProperty(Square* sq, std::vector<Player*> players);

        // this function should print like the 
        // Value of all assets (balance, printed price of buildings, and improvements)
        void displayAssets() const;

        // checkinTuition
        bool checkinTuition() const;
        bool doesOwnProperty(Square* property);

        //Stateless functions
        bool ownsProperty(Square* property);
        bool ownsMonopoly(Monopoly set);
        int numberOfOwnedGyms();
        int numberOfOwnedResidences();
        //Value of all assets (balance, printed price of buildings, and improvements)

};

#endif
