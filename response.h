#ifndef __RESPONSE_H__
#define __RESPONSE_H__

#include <string>

#include "enumerations.h"

class Player;

using std::string;

struct MoveResponse {
    Action action;
    string context;
    MoveResponse(Action a, string c);
};

struct ChoiceResponse {
    bool is_valid;
    string context;
    ChoiceResponse(bool v, string c);
};

struct BankruptcyResponse {
    Player* receiving;
    vector<OwnableProperty*> properties;
    string context;
    BankruptcyResponse(Player* r, vector<OwnableProperty*> p, string c);
};

#endif
