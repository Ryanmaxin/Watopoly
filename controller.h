#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__

#include "board.h"

#include <string>

using std::string;

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
