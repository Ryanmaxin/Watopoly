#ifndef VIEW_H
#define VIEW_H

#include <vector>
#include <iostream>

#include "observer.h"
#include "player.h"
#include "squaredisplay.h"

using namespace std;

class TextDisplay: public Observer  {
    vector<SquareDisplay> sd;
    public:
        void notify(Subject &whoNotified) override;
        void init(Board& b);

        // void display() const;
        // void update(Player& p);

        // Board& theboard;
        // vector<Player*> theplayers;

    friend std::ostream &operator<<(std::ostream &out, TextDisplay &b);
};

#endif
