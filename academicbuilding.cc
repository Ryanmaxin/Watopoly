#include "academicbuilding.h"

#include <string>
#include <sstream>

using std::ostringstream;
using std::string;

AcademicBuilding::AcademicBuilding(string name, int p, Monopoly s, vector<int> rv, int ic): 
OwnableProperty{name,p},set{s},rent_vector{rv},num_improvements{0}, improvement_cost{ic} {};

Monopoly AcademicBuilding::getSet() {return set;}

int AcademicBuilding::getTuition() {return rent_vector[num_improvements];}

int AcademicBuilding::getImprovementCost() const {return improvement_cost;}
int AcademicBuilding::getNumberOfImprovements() const {return num_improvements;}

string AcademicBuilding::specificContext(Player& player) {
    ostringstream oss;
    bool hasMonopoly = player.ownsMonopoly(set);
    if (hasMonopoly) {
        oss << player.getName() << ": " << name << " is part of a monopoly and has " << num_improvements << ", making total tuition $" << getTuition();
    }
    else {
        oss << player.getName() << ": " << name << " is not part of a monopoly, making total tuition $" << getTuition();
    }
    return oss.str();
}
