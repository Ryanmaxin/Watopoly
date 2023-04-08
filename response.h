#ifndef __RESPONSE_H__
#define __RESPONSE_H__

#include <string>

#include "enumerations.h"

using std::string;

struct MoveResponse {
    Action action;
    string context;
    MoveResponse(Action a, string c): action{a},context{c} {};
};

struct ChoiceResponse {
    bool is_valid;
    string context;
    ChoiceResponse(bool v, string c): is_valid{v},context{c} {};
};

#endif
