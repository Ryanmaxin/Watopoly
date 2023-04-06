#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <vector>
#include <map>

#include "enumerations.h"
#include "square.h"
#include "board.h"
#include "response.h"

#include <vector>
#include <map>
#include <string>

using std::map;
using std::string;

using std::vector;
using std::map;

class Player {
    string name;
    char token;

    int position;
    int balance;
    int num_roll_up_rims;

    bool in_jail;
    int num_turns_in_jail;

    Board& board;
    Square* current_square;
    vector<OwnableProperty*> owned_properties;
    map<Monopoly, bool> owned_monopolies;
    
    void teleport(int square_index);
    void transferProperty(OwnableProperty* property, Player* receiving);
    
    bool ownsMonopoly(Monopoly monopoly);
    public:
        Player(string name, char token, Board& attached_to, int bal = 1500, int rur = 0, int pos = 0, bool in_jail = false, int num_turns_in_jail = 0);

        MoveResponse move(int num_spaces);

        CommandResponse declareBankruptcy();
        CommandResponse buyProperty();
        CommandResponse goToJail();

        void SetOwnedMonopoly(Monopoly m, bool does_own);
        map<Monopoly, bool> getOwnedMonopolies();
        bool doesOwnProperty(Square*);
        //Value of all assets (balance, printed price of buildings, and improvements)
        int getNetWorth();

};
#endif
