#ifndef __TEXTDISPLAY_H__
#define __TEXTDISPLAY_H__

#include <vector>
#include <iostream>

#include "view.h"

using namespace std; 

class TextDisplay: public View  {
    public:
        void notify(Subject &whoNotified) override;
        // void display() const;
        // void update(Player& p);

    private:
        // Board& theboard;
        // vector<Player*> theplayers;

    friend std::ostream &operator<<(std::ostream &out, const Board &b);
};

#endif
