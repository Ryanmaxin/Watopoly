#ifndef _OBSERVER_H_
#define _OBSERVER_H_

#include <vector>

#include "subject.h"

class Observer {
public:
    virtual void notify(Subject &who_from) = 0;
    virtual ~Observer() = default;
};

#endif
