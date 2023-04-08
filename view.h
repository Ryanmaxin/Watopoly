#ifndef VIEW_H
#define VIEW_H

#include <vector>
#include <iostream>

using namespace std; 

class View {
public:
    View(Board& b);
    void display() const;
    void update(Player& p);

private:
    Board& theboard;
    vector<Player*> theplayers;
};

#endif
