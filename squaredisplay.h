#ifndef __SQUAREDISPLAY_H__
#define __SQUAREDISPLAY_H__

#include "observer.h"
#include "square.h"
#include "enumerations.h"
#include "controller.h"

#include <string>

using std::string;

class SquareDisplay: public Observer {
    SquareType type;

    string name1;
    string name2;

    Square* underlying;

    int num_improvements;

    string improvements;
    string player_row;
    public:
        SquareDisplay(Square* s, int pos);
        
        ostream& printRow(ostream& out ,int row,bool is_last);
};

#endif
