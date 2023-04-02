#ifndef __RESPONSE_H__
#define __RESPONSE_H__
#include "enumerations.h"
#include "square.h"
struct Response {
    Response(Action a, Player* p, Square* s, bool ma);
    Action action;
    Player* player;
    Square* square;
    bool move_again;
};

#endif
