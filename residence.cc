#include "residence.h"
#include "player.h"

#include <string>
#include <sstream>

using std::string;
using std::ostringstream;

Residence::Residence(string name, int p): 
OwnableProperty{name,p} {};

int Residence::getTuition() {
    int num_residences = getOwner()->numberOfOwnedResidences();
    if (num_residences == 4) return 200;
    else if (num_residences == 3) return 100;
    else if (num_residences == 2) return 50;
    else return 25; //if (num_residences == 1)
}

string Residence::specificContext(Player& player) {
    ostringstream oss;
    int num_residences = getOwner()->numberOfOwnedResidences();
    oss << player.getName() << ": " << name << " is owned by " << getOwner()->getName() << " who has " << num_residences << ", making total tuition $" << getTuition();
    return oss.str();
}
