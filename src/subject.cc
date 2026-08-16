#include <vector>

#include "subject.h"
#include "observer.h"

void Subject::attach(Observer* obs) {
    view = obs;
}

void Subject::detach() {
    view = nullptr;
}

void Subject::notifyView() {
    view->notify(this);
}
