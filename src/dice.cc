#include "dice.h"

#include <iostream>
#include <string>
#include <stdexcept>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <utility>

Dice::Dice() : doubles_rolled{0} {}

int Dice::random1to6() {
    std::vector<int> v = { 1, 2, 3, 4, 5, 6 };
    // use a time-based seed for the default seed value
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine rng{seed};
    std::shuffle( v.begin(), v.end(), rng );
    int die = v[0];;
	return die;
}

int Dice::roll() {
    die1 = random1to6();
    die2 = random1to6(); 
    if (die1 == die2) {
        doubles_rolled += 1;
    }
    else {
        doubles_rolled = 0;
    }
    return die1 + die2;
 }

int Dice::setDice(int d1, int d2) {
    die1 = d1;
    die2 = d2;
    if (d1 == d2) {
        doubles_rolled += 1;
    }
    else {
        doubles_rolled = 0;
    }
    return die1 + die2;
}

bool Dice::isDoubles() {
    if (die1 == die2) return true;
    return false;
}

bool Dice::threeDoubles() {
    if (doubles_rolled == 3) return true;
    return false;
}

std::pair<int,int> Dice::getFaceValues() { return std::make_pair(die1, die2); }
