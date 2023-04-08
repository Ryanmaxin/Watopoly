#include "gym.h"
#include "player.h"
#include <string>
#include <sstream>

using std::string;
using std::ostringstream;

Gym::Gym(string name, int p): 
OwnableProperty{name,p},dice{} {}

int Gym::getTuition() {
    int num_gyms = owner->numberOfOwnedGyms();
    if (num_gyms == 2) return (10*dice.roll());
    else return (4*dice.roll());
}

string Gym::specificContext(Player& player) {
    ostringstream oss;
    int num_gyms = owner->numberOfOwnedGyms();
    std::pair<int,int> face_values = dice.getFaceValues();
    int multiplier = 4;
    if (num_gyms == 2) multiplier = 10;
        oss << player.getName() << ": On " << name << " you rolled (" << face_values.first << "," << face_values.second << "). " << getOwner()->getName() << 
        "owns " << num_gyms << "gym(s), making total tuition " << face_values.first+face_values.second << " x " << multiplier << " = $" << getTuition();
    return oss.str();
}
