#ifndef __RESPONSE_H__
#define __RESPONSE_H__
#include "enumerations.h"
#include "square.h"
#include <string>

using std::string;

struct MoveResponse {
    Action action;
    Square* landed_on;
    MoveResponse(Action a, Square* l): action{a},landed_on{l} {};
};

struct CommandResponse {
    bool is_valid;
    InvalidReason reason;
    CommandResponse(bool v, InvalidReason r): is_valid{v},reason{r} {};
};



#endif
