#ifndef __RESPONSE_H__
#define __RESPONSE_H__
#include "enumerations.h"
#include "square.h"
#include <string>

using std::string;

struct MoveResponse {
    Action action;
    string context;
    MoveResponse(Action a, string c): action{a},context{c} {};
};

#endif
