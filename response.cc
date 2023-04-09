#include "response.h"

MoveResponse::MoveResponse(Action a, string c): action{a}, context{c} {};

ChoiceResponse::ChoiceResponse(bool v, string c): is_valid{v}, context{c} {};
