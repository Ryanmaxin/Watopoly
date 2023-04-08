#ifndef __ENUMERATIONS_H__
#define __ENUMERATIONS_H__

#include <iostream>

enum class Action { NoAction, BuyOrAuction, CantPayTuition, TuitionChoice, InJail };

//Add more here as needed.

enum class Monopoly { Arts1, Arts2, Eng, Health, Env, Sci1, Sci2, Math };

const int DC_TIMS_LINE = 10;
const int COLLECT_OSAP = 0;
const int MAX_ROLL_UPS = 4;
const int MAX_IMPROVEMENTS = 5;
#endif
