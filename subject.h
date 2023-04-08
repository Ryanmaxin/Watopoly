#ifndef _SUBJECT_H_
#define _SUBJECT_H_

#include <vector>
#include "observer.h"

class Subject {
public:
    void attach(Observer* ob);
    void detach(Observer* ob);
    void notifyObservers(Player &p);
private:
    std::vector<Observer*> the_observers;
};

#endif

