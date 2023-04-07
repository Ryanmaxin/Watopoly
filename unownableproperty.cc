#include "unownableproperty.h"
#include <random>
#include <iostream>
#include <sstream>

using std::ostringstream;
using std::cout;
using std::endl;

UnownableProperty::UnownableProperty(string n): Square {n} {};

MoveResponse UnownableProperty::actionOnLand(Player& player) {
    ostringstream oss;
    Action action;

    if (name == "CollectOSAP") {
        player.addBalance(200);
        action = Action::NoAction;
        oss << player.getName() << ": Collected $200 from OSAP";
    }
    else if (name == "DCTimsLine") {
        //Do nothing
        action = Action::NoAction;
        oss << player.getName() << ": Just visiting the DC Tims Line";
    }
    else if (name == "GoToTims") {
        player.goToTims();
        action = Action::NoAction;
        oss << player.getName() << ": Sent to DC Tims Line!";
    }
    else if (name == "GooseNesting") {
        //Do nothing
        action = Action::NoAction;
        oss << player.getName() << ": Stumbled on a goose nesting!";
    }
    else if (name == "Tuition") {
        action = Action::TuitionChoice;
        oss << player.getName() << ": Landed on tuition. Pay either $300 or 10\% of net worth ($" << player.getNetWorth() << ")";
    }
    else if (name == "CoopFee") {
        if (player.getBalance() < 150) {
            action = Action::CantAfford;
            oss << player.getName() << ": Can't afford coop fee of $150 (have " << player.getBalance() << ")";
        }
        else {
            player.addBalance(-150);
            action = Action::NoAction;
            oss << player.getName() << ": Payed coop fee of $150";
        }
    }
    else if (name == "SLC") {
        std::random_device dev;
        std::mt19937 rng(dev());
        std::uniform_int_distribution<std::mt19937::result_type> SLCRoll(1,24); // distribution in range [1, 24]
        int spaces = 0;
        if (SLCRoll(rng) <=22) {
            if (SLCRoll(rng) <= 3) spaces = -3;
            else if (SLCRoll(rng) <= 7) spaces = -2;
            else if (SLCRoll(rng) <= 11) spaces = -1;
            else if (SLCRoll(rng) <= 14) spaces = 1;
            else if (SLCRoll(rng) <= 18) spaces = 2;
            else if (SLCRoll(rng) <= 22) spaces = 3;
            MoveResponse res = player.move(spaces);
            action = res.action;
            if (spaces > 0) {
                oss << player.getName() << ": Sent forwards " << spaces << "space(s) by SLC" << "\n" << res.context;
            }
            else {
                oss << player.getName() << ": Sent backwards " << spaces*-1 << "space(s) by SLC" << "\n" << res.context;
            }
        }
        else if (SLCRoll(rng) <= 23) {
            string res = player.goToTims();
            oss << player.getName() << ": Sent to DC Tims Line by SLC" << "\n" << res;
            action = Action::NoAction;
        }
        else if (SLCRoll(rng) <= 24) {
            player.teleport(COLLECT_OSAP);
            player.addBalance(200);
            oss << player.getName() << ": Sent to Collect OSAP by SLC" << "\n" << player.getName() << ": Collected $200 from OSAP";
            action = Action::NoAction;
        }
    }
    else if (name == "NeedlesHall") {
        std::random_device dev;
        std::mt19937 rng(dev());
        std::uniform_int_distribution<std::mt19937::result_type> SLCRoll(1,18); // distribution in range [1, 18]
        int change = 0;
        if (SLCRoll(rng) == 1) change = -200;
        else if (SLCRoll(rng) <= 3) change = -100;
        else if (SLCRoll(rng) <= 6) change = -50;
        else if (SLCRoll(rng) <= 12) change = 25;
        else if (SLCRoll(rng) <= 15) change = 50;
        else if (SLCRoll(rng) <= 17) change = 100;
        else if (SLCRoll(rng) <= 18) change = 200;
        if (player.getBalance() < (change * -1)) {
            action = Action::CantAfford;
            oss << player.getName() << ": Can't afford Needles Hall fee of " << change * -1 << "(have $" << player.getBalance() << ")";
        }
        else {
            player.addBalance(change);
            oss << player.getName() << ": Paid Needles Hall fee of " << change * -1;
            action = Action::NoAction;
        }
    }
    string context = oss.str();
    return {action, context};

}
