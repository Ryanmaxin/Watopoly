#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <vector>
#include <map>
#include <string>
#include <iostream>

#include "board.h"
#include "response.h"
#include "trade.h"

#include "subject.h"

using std::map;
using std::string;
using std::vector;
using std::ostream;

class Player: public Subject {
    string name;
    char token;

    int position;
    int balance;
    int num_roll_ups;

    bool in_tims_line;
    int num_turns_in_tims_line;

    Board* board;
    Square* current_square;
    vector<OwnableProperty*> owned_properties;
    
    void transferProperty(OwnableProperty* property, Player* receiving);
    
    public:
        Player(string name, char token, Board* attached_to, int bal = 1500, int rur = 0, int pos = 0, bool in_jail = false, int num_turns_in_jail = 0);

        MoveResponse move(int num_spaces);
        void teleport(int square_index);

        //Choices for Action::CantPayTuition
        ChoiceResponse declareBankruptcy();
        ChoiceResponse settleDebts();

        //Choices for Action::BuyOrAuction
        ChoiceResponse buy();
        void wonAuction(OwnableProperty* property, int price);

        //Choices for Action::TuitionChoice
        ChoiceResponse payTuition(int amount);

        //Choices for Action::InJail
        ChoiceResponse payOutOfDCLine(bool use_roll_up);
        bool isInTimsLine();
        bool inLine();

        //Called by SLC and Go To Tims properties. Also called when player rolls doubles 3 times.
        string goToTims();

        //Regular commands (implement)
        Trade offerTrade(Player& send_to, string give, string receive);
        string acceptOffer(Player& from, Trade t);
        string improve(string property, bool buy);
        string Mortgage(string property); // assume property checker in board
        string unMortgage(string property);

         
        // ChoiceResponse offerBid(int amount);

        //Getter-Setter methods
        int getNumTurnsInDCTims() const;
        int isInTimsLine() const;
        int getBalance() const;
        int getCups() const;
        void setBalance(int new_balance);
        void addBalance(int money);
        //The sum of current balance + price of all owned properties + price of all owned improvements
        int getNetWorth() const;
        int getPosition() const;
        string getName() const;
        char getToken() const;
        Square* getCurrentSquare() const;
        vector<OwnableProperty*>& getOwnedProperties();
        void removeRollUp();
        void addRollUp();
        Board* getBoard();

        //Stateless functions
        bool ownsProperty(Square* property) const;
        bool ownsMonopoly(Monopoly set) const;
        int numberOfOwnedGyms() const;
        int numberOfOwnedResidences() const;
        
        //Print all assets (balance, printed price of buildings, and improvements)
        friend ostream& operator<<(ostream& out, const Player& player);
};

#endif
