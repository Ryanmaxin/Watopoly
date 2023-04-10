#ifndef __SQUAREDISPLAY_H__
#define __SQUAREDISPLAY_H__

#include "observer.h"
#include "square.h"
#include "enumerations.h"

#include <string>

using std::string;

class SquareDisplay: public Observer {
    SquareType type;

    string name1;
    string name2;

    string improvements;
    string player_row;
    public:
        SquareDisplay(int pos, string name, SquareType st);

        void add(char token, int i);
        void remove(int i);

        void notify(Subject *whoNotified) override;
        
        ostream& printRow(ostream& out ,int row,bool is_last);
};

#endif
