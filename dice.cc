#include "dice.h"

#include <iostream>
#include <string>
#include <stdexcept>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>

Dice::Dice() : doubles_rolled{0} {}

int Dice::rollInternal( std::vector<int> const & v ) {
	//for ( int i : v ) std::cout << i << ' ';
   return v[0];
}

// Rolls Die1 and sets the value of die1 field to the result
int Dice::rollDie1() {
    std::vector<int> v = { 1, 2, 3, 4, 5, 6 };
    // use a time-based seed for the default seed value
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine rng{seed};
    std::shuffle( v.begin(), v.end(), rng );
    die1 = rollInternal(v);
	return die1;
}

int Dice::rollDie2() {
    std::vector<int> v = { 1, 2, 3, 4, 5, 6 };
    // use a time-based seed for the default seed value
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine rng{seed};
    std::shuffle( v.begin(), v.end(), rng );
    die2 = rollInternal(v);
	return die2;
}

int Dice::roll() { return die1 + die2; }

bool Dice::isDoubles() {
    if (die1 == die2) {
        ++doubles_rolled;
        return true;
    }
    return false;
}

bool Dice::threeDoubles() {
    if (doubles_rolled == 3) return true;
    return false;
}

std::pair<int,int> getFaceValues() { return std::make_pair(die1, die2); }
