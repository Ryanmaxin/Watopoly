#ifndef _OBSERVER_H_
#define _OBSERVER_H_

#include <vector>

class Player;

class Observer {
public:
    virtual void notify(Player &p) = 0;
    virtual ~Observer() = default;
};

#endif
