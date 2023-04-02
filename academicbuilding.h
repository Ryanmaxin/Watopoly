#ifndef __ACADEMICBUILDING_H__
#define __ACADEMICBUILDING_H__
#include <string>
#include "ownableproperty.h"
#include "monopoly.h"

using std::string;

class AcademicBuilding: public OwnableProperty {
    Monopoly set;
    int num_improvements;
    public:
        AcademicBuilding(Monopoly s);
        int getRent() override;
        Monopoly getSet();
};
#endif

