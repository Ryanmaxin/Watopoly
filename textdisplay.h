#ifndef VIEW_H
#define VIEW_H

#include <vector>
#include <iostream>

#include "observer.h"
#include "player.h"

using namespace std; 

class TextDisplay: public Observer  {

    public:
        void notify(Subject &whoNotified) override;
        void init();

        // void display() const;
        // void update(Player& p);

        // Board& theboard;
        // vector<Player*> theplayers;

    friend std::ostream &operator<<(std::ostream &out, const Board &b);
};

#endif
