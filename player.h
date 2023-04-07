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

        string declareBankruptcy();
        string buy();
        string auction();
        string goToTims();
        string offerTrade(string name, string give, string receive);
        string improve(string property, string buysell);
        string Mortgage(string property);
        string unMortgage(string property);
        string payTuition(bool pay300);
        string useRollUp();
        string payFifty();
        string raiseFunds();



        int getBalance();
        void setBalance(int new_balance);
        void addBalance(int money);

        int getNetWorth();

        string getName();

        bool doesOwnProperty(Square* property);

        //Stateless functions
        bool ownsMonopoly(Monopoly set);
        int numberOfOwnedGyms();
        int numberOfOwnedResidences();
        //Value of all assets (balance, printed price of buildings, and improvements)

};

#endif
