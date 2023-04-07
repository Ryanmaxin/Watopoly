#ifndef __ACADEMICBUILDING_H__
#define __ACADEMICBUILDING_H__

#include "ownableproperty.h"
#include "enumerations.h"

#include <string>
#include <vector>

using std::string;
using std::vector;

class AcademicBuilding: public OwnableProperty {
    Monopoly set;
    int num_improvements;
    int improvement_cost;
    vector<int> rent_vector;
    public:
        AcademicBuilding(string name, int p, Monopoly s, vector<int> rv, int ic);
        
        string specificContext(Player& p) override;

        int getTuition() override;
        int getImprovementCost();
        Monopoly getSet();
};
#endif

