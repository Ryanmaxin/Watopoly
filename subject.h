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
    virtual ~Subject() = default;
    SubjectType virtual getType() = 0;
private:
    Observer* view;
};

#endif

