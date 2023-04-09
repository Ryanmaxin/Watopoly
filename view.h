#ifndef VIEW_H
#define VIEW_H

#include <vector>
#include <iostream>

#include "observer.h"
#include "player.h"

using namespace std; 

class View: public Observer  {
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
