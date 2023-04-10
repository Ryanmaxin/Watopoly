#ifndef _SUBJECT_H_
#define _SUBJECT_H_

#include <vector>

class Observer;

using namespace std;

class Subject {
public:
    void attach(Observer* obs);
    void detach();
    void notifyView();
    virtual ~Subject() = default;
private:
    Observer* view;
};

#endif

