#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <vector>
#include <map>
#include "enumerations.h"
#include "square.h"

using std::map;

class Player {
    int cur_pos;
    int balance;
    vector<Square*> owned_properties;
    map<Monopoly, bool> owned_monopolies;
    public:
        int getCurrentPosition();
        bool ownsMonopoly(Monopoly monopoly);
        //Add num_spaces to cur_pos
        void move(int num_spaces);
        //Set cur_pos to square_index
        void teleport(int square_index);
        //Remove all owned_properties. No need to delete them
        void clearProperties();
        //Append property to end of owned_properties. Change owner or property to this player! (VERY IMPORTANT)
        //Invariant: this will only be called on an unowned (but ownable) property. IE property.owner = nullptr
        void addProperty(Square*);
        //Transfer ownership of this property. Must change both Square.owner and player.owned_properties
        void transferProperty(Square* property, Player* receiver);
        //Just return owned_properties
        vector<Square*> getProperties();
        //Replace balance with new_balance
        void setBalance(int new_balance);
        //Add (+=) increment to balance. May be negative OR positive increase
        void addBalance(int increment);
        //Return balance
        int getBalance();
        void SetOwnedMonopoly(Monopoly m, bool does_own);
        map<Monopoly, bool> getOwnedMonopolies();
        bool doesOwnProperty(Square*);

};
#endif
