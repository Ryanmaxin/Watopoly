#include "academicbuilding.h"
#include "player.h"

#include <string>
#include <sstream>

using std::ostringstream;
using std::string;

AcademicBuilding::AcademicBuilding(string name, int p, Monopoly s, vector<int> rv, int ic): 
OwnableProperty{name,p},set{s},num_improvements{0},improvement_cost{ic},rent_vector{rv} {};

Monopoly AcademicBuilding::getSet() {return set;}

int AcademicBuilding::getTuition() {return rent_vector[num_improvements];}

int AcademicBuilding::getImprovementCost() const {return improvement_cost;}
int AcademicBuilding::getNumberOfImprovements() const {return num_improvements;}

int AcademicBuilding::sellAllImprovements() {
    int value = num_improvements * improvement_cost * 0.5;
    num_improvements = 0;
    return value;
}

void AcademicBuilding::sellImprovement() {
    num_improvements -= 1;
}

void AcademicBuilding::buyImprovement() {
    num_improvements += 1;
}

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
