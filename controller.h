#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__

#include "board.h"

#include <string>

using std::string;

//Note to Isha: Controller methods should purely deal with input/output
//For this reason, you should be able to call a Board function that completes all the logic,
//however you will have to be the one validating user input, IE if a trade is valid, etc
//For example, to validate if player can mortgage property, first convert the property (string) the user gives you
//into a property with Square* property = board.stringToProperty(). Then call board->getCurrentPlayer->doesOwnProperty()
//To check if the player requesting a mortgage truly owns this property.
//If there aren't any valid board methods for a controller method, please pretend on exists and add it to board.h,
//Add a comment above it of what you want it to do.
class Controller {
    Board& the_board;
    public:
        Controller(Board& b);
        void user_input();
        Response move();
        void purchase();
        void auction();
        bool improve();
        bool trade();
        bool mortgage();
        bool unmortgage();
        bool bankrupt();
        bool assets();
        void all();
        void save(string the_filename);
};

#endif
