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

struct ChoiceResponse {
    bool is_valid;
    string context;
    ChoiceResponse(bool v, string c): is_valid{v},context{c} {};
};

struct Trade {
    bool is_valid;
    string context;
    int give_money;
    int receive_money;
    OwnableProperty* give_property;
    OwnableProperty* receive_property;
    int option;

    Trade(bool v, string c, int gm, int rm, OwnableProperty* gp, OwnableProperty* rp, int o): 
    is_valid{v},context{c}, give_money{gm}, receive_money{rm}, give_property{gp}, receive_property{rp}, option{o} {};
};

#endif
