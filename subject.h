#ifndef _SUBJECT_H_
#define _SUBJECT_H_

#include <vector>

#include "observer.h"

using namespace std;

class Subject {
public:
    void attach(Observer* obs);
    void detach();
    void notifyView();
private:
    Observer* view;
};

#endif

