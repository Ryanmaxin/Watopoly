#include "response.h"
#include "player.h"
#include "ownableproperty.h"

MoveResponse::MoveResponse(Action a, string c): action{a}, context{c} {};

ChoiceResponse::ChoiceResponse(bool v, string c): is_valid{v}, context{c} {};

BankruptcyResponse::BankruptcyResponse(Player* r, vector<OwnableProperty*> p, string c): receiving{r},properties{p},context{c} {};
