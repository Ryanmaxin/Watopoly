#include <vector>
#include "observer.h"

#include "subject.h"

void Subject::attach(Observer* obs) {
  the_observers.push_back(obs);
}

void Subject::detach(Observer* obs) {
  for (auto i = the_observers.begin(); i != the_observers.end(); ++i) {
    if (*i == obs) {
      the_observers.erase(i);
      return;
    }
  }
}

void Subject::notifyObservers(Player &p) {
  for (auto obs : the_observers) {
    obs->notify(p);
  }
}
