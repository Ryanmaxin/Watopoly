#ifndef __BOARD_H__
#define __BOARD_H__

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <memory>

#include "academicbuilding.h"
#include "gym.h"
#include "residence.h"
#include "unownableproperty.h"

using std::vector;
using std::unique_ptr;
using std::pair;
using std::string;

class Board {
    vector<unique_ptr<Square>> squares;
    // vector<unique_ptr<Player>> players;
    int current_roll_up_rims = 0;
    void initSquares(string square_data);
    public:
        //Init sets up the board. Every time you start a game this should be called.
        //Should be called from within Controller.
        void init(string square_data = "default.data");
        Square* getSquare(int index);

        //Returns a pointer to the property, if it exists
        Square* stringToProperty(string property);
        //You will have to do validation checking if player has enough money, etc
        Monopoly stringToMonopoly(string monopoly);

        void removeRollUp();
        void addRollUp();

        bool validRollUp();
};

#endif
