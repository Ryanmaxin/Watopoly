#include "unownableproperty.h"
#include <random>
#include <iostream>

using std::cout;
using std::endl;

UnownableProperty::UnownableProperty(string n): Square {n} {};

Action UnownableProperty::goToTims(Player* player) {
    player->teleport(DC_TIMS_LINE);
    player->setIsInJail(true);
    #ifdef VISUALISATION
        cout << curr_player->getName() << "Was sent to DC TIMS LINE " << endl;
    #endif
    return Action::NoAction;
}
Action UnownableProperty::actionOnLand(Player* player) {
    if (name == "CollectOSAP") {
        player->addBalance(200);
        return Action::NoAction;
    }
    else if (name == "DCTimsLine") {
        //Do nothing
        return Action::NoAction;
    }
    else if (name == "GoToTims") {
        return goToTims(player);
    }
    else if (name == "GooseNesting") {
        //Do nothing
        return Action::NoAction;
    }
    else if (name == "Tuition") {
        return Action::TuitionChoice;
    }
    else if (name == "CoopFee") {
        if (player->getBalance() < 150) {
            return Action::CantAfford;
        }
        else {
            player->addBalance(-150);
            return Action::NoAction;
        }
    }
    else if (name == "SLC") {
        std::random_device dev;
        std::mt19937 rng(dev());
        std::uniform_int_distribution<std::mt19937::result_type> SLCRoll(1,24); // distribution in range [1, 24]
        int spaces = 0;
        if (SLCRoll(rng) <= 3) {
            spaces = -3;
        }
        else if (SLCRoll(rng) <= 7) {
            spaces = -2;
        }
        else if (SLCRoll(rng) <= 11) {
            spaces = -1;
        }
        else if (SLCRoll(rng) <= 14) {
            spaces = 1;
        }
        else if (SLCRoll(rng) <= 18) {
            spaces = 2;
        }
        else if (SLCRoll(rng) >= 22) {
            spaces = 3;
        }
        else if (SLCRoll(rng) <= 23) {
            return goToTims(player);
        }
        else if (SLCRoll(rng) <= 24) {
            player->teleport(COLLECT_OSAP);
            player->addBalance(200);
            return Action::NoAction;
        }
        player->move(spaces);
        return Action::ChainMove;
    }
    else if (name == "NeedlesHall") {
        std::random_device dev;
        std::mt19937 rng(dev());
        std::uniform_int_distribution<std::mt19937::result_type> SLCRoll(1,18); // distribution in range [1, 18]
        int change = 0;
        if (SLCRoll(rng) == 1) {
            change = -200;
        }
        else if (SLCRoll(rng) <= 3) {
            change = -100;
        }
        else if (SLCRoll(rng) <= 6) {
            change = -50;
        }
        else if (SLCRoll(rng) <= 12) {
            change = 25;
        }
        else if (SLCRoll(rng) <= 15) {
            change = 50;
        }
        else if (SLCRoll(rng) <= 17) {
            change = 100;
        }
        else if (SLCRoll(rng) <= 18) {
            change = 200;
        }
        if (player->getBalance() < (change * -1)) {
            return Action::CantAfford;
        }
        else {
            player->addBalance(change);
            return Action::NoAction;
        }
    }

}
