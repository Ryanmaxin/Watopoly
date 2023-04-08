#ifndef _SUBJECT_H_
#define _SUBJECT_H_

#include <vector>

using namespace std;

class Subject {
public:
    void attach(Observer* obs);
    void detach(Observer* obs);
    void notifyObservers(Player &p);
private:
    vector<Observer*> the_observers;
};

#endif

