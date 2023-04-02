#ifndef __RESPONSE_H__
#define __RESPONSE_H__
#include "action.h"
#include "square.h"
struct Response {
    Response(Action a, Player* p, Square s);
    Action action;
    Player* player;
    Square* square;
};

#endif
