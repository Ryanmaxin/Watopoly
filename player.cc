#include "player.h"

int Player::getCurrentPosition() { return curr_pos; }

bool Player::ownsMonopoly(Monopoly monopoly) { return owned_monopolies[monopoly]; }
