#ifndef __SUBJECT_H__
#define __SUBJECT_H__

#include <vector>
#include "observer.h"

void Subject::attach(Observer* obs) {
  observers.push_back(obs);
}

void Subject::detach(Observer* obs) {
  for (auto i = observers.begin(); i != observers.end(); ++i) {
    if (*i == obs) {
      observers.erase(i);
      return;
    }
  }
}

void Subject::notifyObservers() {
  for (auto obs : observers) {
    obs->notify(*this);
  }
}
#endif
